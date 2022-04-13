import torch
import torch.nn as nn
import torch.nn.functional as F
from collections import OrderedDict
import re

class Conv2d(nn.Conv2d):
    def __init__(self, in_channels, out_channels, kernel_size, stride=1, padding=["same"], bias=True):
        super(Conv2d, self).__init__(in_channels, out_channels, kernel_size, stride, padding, bias=bias)
        self.padding = padding
        self.stride = stride

    def forward(self, x, params=None):
        if params is None:
            x = super(Conv2d, self).forward(x)
        else:
            weight, bias = params.get('weight'), params.get('bias')
            if weight is None:
                weight = self.weight
            if bias is None:
                bias = self.bias

            x = F.conv2d(x, weight, bias, self.stride, 1)
        return x


class Linear(nn.Linear):
    def __init__(self, in_features, out_classes, bias=True):
        super(Linear, self).__init__(in_features, out_classes, bias=True)

    def forward(self, x, params=None):
        if params is None:
            x = super(Linear, self).forward(x)
        else:
            weight, bias = params.get('weight'), params.get('bias')
            if weight is None:
                weight = self.weight
            if bias is None:
                bias = self.bias
            x = F.linear(x, weight, bias)

        return x


class BatchNorm2d(nn.BatchNorm2d):
    def __init__(self, num_features):
        super(BatchNorm2d, self).__init__(num_features)

    def forward(self, x, params=None):
        if params is None:
            x = super(BatchNorm2d, self).forward(x)
        else:
            weight, bias = params.get('weight'), params.get('bias')
            if weight is None:
                weight = self.weight
            if bias is None:
                bias = self.bias
            if self.training:
                x = F.batch_norm(x, self.running_mean, self.running_var, weight, bias, training=True)
            else:
                x = F.batch_norm(x, self.running_mean, self.running_var, weight, bias, training=False)
        return x


class Sequential(nn.Sequential):
    def __init__(self, *args):
        super(Sequential, self).__init__(*args)

    def forward(self, x, params=None):
        if params is None:
            for module in self:
                x = module(x, None)
        else:
            for name, module in self._modules.items():
                x = module(x, get_child_dict(params, name))
        return x


def get_child_dict(params, name):
    if params is None:
        return None
    key_re = re.compile(r'(.*\.)?{0}\.(.+)'.format(re.escape(name)))  # TODO: maybe use `r'^{0}\.(.+)'`
    child_dict = OrderedDict(
            (key_re.sub(r'\2', k), value) for (k, value)
            in params.items() if key_re.match(k) is not None)

    return child_dict
