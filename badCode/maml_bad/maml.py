import torch
import torch.nn as nn
import torch.nn.functional as F
from collections import OrderedDict
import torch.autograd as autograd
import numpy as np


class hostConvBlock(nn.Module):
    def __init__(self, in_channels, out_channels, k_s):
        super(hostConvBlock, self).__init__()
        self.conv2d = nn.Conv2d(
            in_channels, out_channels, k_s, stride=2, bias=True)
        self.bn = nn.BatchNorm2d(out_channels)
        self.relu = nn.ReLU(inplace=True)

    def forward(self, x):
        out = self.conv2d(x)
        out = self.bn = (out)
        return self.relu(out)


class ConvBlock():
    def __init__(self):
        self.relu = nn.ReLU(inplace=True)

    def __call__(self, x, c_pw, c_pb, b_pw, b_pb):
        return self.forward(x, c_pw, c_pb, b_pw, b_pb)

    def forward(self, x, c_pw, c_pb, b_pw, b_pb):
        out = F.conv2d(x, c_pw, c_pb, 2, 1)
        running_mean = torch.zeros(np.prod(np.array(out.data.size()[1]))).cuda()
        running_var = torch.ones(np.prod(np.array(out.data.size()[1]))).cuda()
        out = F.batch_norm(
            out, running_mean, running_var, weight=b_pw, bias=b_pb, momentum=1)
        return self.relu(out)


class MAML(nn.Module):
    def __init__(self, way=5, shot=1, lr=1e-3):
        super(MAML, self).__init__()
        self.way = way
        self.shot = shot
        self.lr = lr
        self.features = nn.Sequential(OrderedDict([
            ('conv1', hostConvBlock(1, 64, 3)),
            ('conv2', hostConvBlock(64, 64, 3)),
            ('conv3', hostConvBlock(64, 64, 3)),
            ('conv4', hostConvBlock(64, 64, 3)),
        ]))
        self.fc = nn.Linear(64, way, bias=True)
        self.softmax = nn.Softmax(dim=1)

    def clone_params(self):
        ip = OrderedDict()
        for name, param in self.named_parameters():
            ip[name] = param.clone()
        return ip

    def inner_forward(self, x, ip):
        convblock = ConvBlock()
        iw = "features.conv{}.{}.weight"
        ib = "features.conv{}.{}.bias"
        out = convblock(x, ip[iw.format(1, "conv2d")],
                        ip[ib.format(1, "conv2d")],
                        ip[iw.format(1, "bn")],
                        ip[ib.format(1, "bn")])
        out = convblock(out, ip[iw.format(2, "conv2d")],
                        ip[ib.format(2, "conv2d")],
                        ip[iw.format(2, "bn")],
                        ip[ib.format(2, "bn")])
        out = convblock(out, ip[iw.format(3, "conv2d")],
                        ip[ib.format(3, "conv2d")],
                        ip[iw.format(3, "bn")],
                        ip[ib.format(3, "bn")])
        out = convblock(out, ip[iw.format(4, "conv2d")],
                        ip[ib.format(4, "conv2d")],
                        ip[iw.format(4, "bn")],
                        ip[ib.format(4, "bn")])
        out = torch.mean(out, [2, 3])
        out = F.linear(
            out, weight=ip["fc.weight"], bias=ip["fc.bias"])
        return self.softmax(out)

    def inner_iterator(self, x, y, ip):
        updated_ips = OrderedDict()
        with torch.enable_grad():
            pred = self.inner_forward(x, ip)
            loss = F.cross_entropy(pred, y)
            grads = autograd.grad(loss, ip.values())
            for (name, param), grad in zip(ip.items(), grads):
                if grad is not None:
                    updated_ip = param - self.lr * grad
                updated_ips[name] = updated_ip
        return updated_ips

    def inner_adapt(self, x, y, x_query, ip, num_updates=1):
        for step in range(num_updates + 1):
            ip = self.inner_iterator(x, y, ip)

        pred = self.inner_forward(x, ip)

        return ip, pred

    def forward(self, x, y, x_query, y_query, num_updates=1, is_train=True):
        ip = self.clone_params()
        losses, train_right, train_sum = [], 0, 0
        for ep in range(x.size(0)):
            self.train(True)
            ip, pred = self.inner_adapt(
                x[ep], y[ep], x_query[ep], ip, num_updates)
            losses.append(F.cross_entropy(pred, y_query[ep]))
            train_right += pred.max(1)[1].eq(y_query[ep]).float().sum()
            train_sum += len(y_query[ep])

        self.train(is_train)
        losses = torch.stack(losses)
        return losses, train_right / train_sum


if __name__ == "__main__":
    model = MAML()
    weight = OrderedDict()
    for i, j in model.named_parameters():
        weight[i] = j.clone()
    iw = "features.conv{}.{}.weight"
    ib = "features.conv{}.{}.bias"
    print(weight[iw.format(1, "bn")].shape)
