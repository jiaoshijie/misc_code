import torch
import torch.nn as nn
import torch.nn.functional as F
from collections import OrderedDict
import torch.autograd as autograd

import utils

class ConvBlock(nn.Module):
    def __init__(self, in_channels, out_channels, kernel_size, maxpool=False):
        super(ConvBlock, self).__init__()
        if maxpool:
            self.conv2d = utils.Conv2d(in_channels, out_channels, kernel_size, 1)
        else:
            self.conv2d = utils.Conv2d(in_channels, out_channels, kernel_size, 2)
        self.bn = utils.BatchNorm2d(out_channels)
        self.relu = nn.ReLU(inplace=True)
        self.maxpool = maxpool
        if maxpool:
            self.pool = nn.MaxPool2d(2)

    def forward(self, x, params=None):
        out = self.conv2d(x, utils.get_child_dict(params, 'conv2d'))
        out = self.bn(out, utils.get_child_dict(params, 'bn'))
        out = self.relu(out)
        if self.maxpool:
            out = self.pool(out)
        return out


class MAML(nn.Module):
    def __init__(self, in_channels, out_hidden, kernel_size, way = 5, maxpool=False, lr=0.4):
        super(MAML, self).__init__()
        self.conv_seq = utils.Sequential(OrderedDict([
            ('conv1', ConvBlock(in_channels, out_hidden, kernel_size, maxpool=False)),
            ('conv2', ConvBlock(out_hidden, out_hidden, kernel_size, maxpool=False)),
            ('conv3', ConvBlock(out_hidden, out_hidden, kernel_size, maxpool=False)),
            ('conv4', ConvBlock(out_hidden, out_hidden, kernel_size, maxpool=False)),
            ]))
        self.fc = utils.Linear(out_hidden, way, True)
        self.softmax = nn.Softmax(dim=1)
        self.lr = lr
        self.way = way

    def _inner_forward(self, x, params=None):
        out = self.conv_seq(x, utils.get_child_dict(params, 'conv_seq'))
        out = torch.mean(out, [2, 3])
        out = self.fc(out, utils.get_child_dict(params, 'fc'))
        return self.softmax(out)

    def _inner_iterator(self, x, y, params=None):
        updated_params = OrderedDict()
        with torch.enable_grad():
            # forward
            pred = self._inner_forward(x, params)
            loss = F.cross_entropy(pred, y)
            # backward
            grads = autograd.grad(loss, params.values())  # TODO
            for (name, param), grad in zip(params.items(), grads):
                if grad is None:
                    updated_param = param
                else:
                    updated_param = param - self.lr * grad
                updated_params[name] = updated_param

        return updated_params

    def _adapt(self, x, y, x_query, params=None, num_updates=1):
        for step in range(num_updates + 1):
            params = self._inner_iterator(x, y, params)

            if step != 0:
                train_right = 0
                train_sum = 0
                with torch.set_grad_enabled(False):
                    self.eval()
                    pred = self._inner_forward(x_query, params)
        return params, pred

    def forward(self, x, y, x_query, y_query, num_updates=1, is_train=True):
        params = OrderedDict(self.named_parameters())
        for name in params.keys():
            if not params[name].requires_grad:
                params.pop(name)
        losses = []
        train_right, train_sum = 0, 0
        for ep in range(x.size(0)):
            self.train(True)
            params, pred = self._adapt(x[ep], y[ep], x_query[ep], params, num_updates)
            losses.append(F.cross_entropy(pred, y_query[ep]))
            train_right += pred.max(1)[1].eq(y_query[ep]).float().sum()
            train_sum += len(y_query[ep])


        self.train(is_train)
        losses = torch.stack(losses)
        if is_train:
            losses.requires_grad_()
        return losses, train_right / train_sum

    def _clone_weight(self):
        for name, value in 
        return params

if __name__ == "__main__":
    model = MAML(3, 64, 3, 5, lr=0.4)
    print(OrderedDict(model.named_parameters()).keys())
