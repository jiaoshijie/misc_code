import os
import random
import torch
from torchvision import transforms
from PIL import Image
from tqdm import tqdm
import numpy as np


def randomShuffle(x, seed=1):
    random.seed(seed)
    random.shuffle(x)


def genDataDict(inputdir, way=5, shot=1, train=True):
    all_dir = [os.path.join(inputdir, i, j)
               for i in os.listdir(inputdir)
               for j in os.listdir(os.path.join(inputdir, i))]
    randomShuffle(all_dir, 1)
    if train:
        all_dir = all_dir[:1200]
        num_total_batches = 200000
    else:
        all_dir = all_dir[1200:]
        num_total_batches = 600

    datadict = []
    print("generating the training datainfo...")
    for _ in tqdm(range(num_total_batches)):
        sampled_character_dir = random.sample(all_dir, way)
        random.shuffle(sampled_character_dir)
        support, query, support_l, query_l = [], [], [], []
        for i in range(way):
            images_list = [os.path.join(sampled_character_dir[i], j)
                           for j in os.listdir(sampled_character_dir[i])]
            random.shuffle(images_list)
            support.extend(images_list[:shot])
            query.extend(images_list[shot:shot*2])
            support_l.extend([i] * shot)
            query_l.extend([i] * shot)  # (len(images_list) - shot))
        seed = random.randint(0, 1000)
        randomShuffle(support, seed)
        randomShuffle(support_l, seed)
        seed = random.randint(0, 1000)
        randomShuffle(query, seed)
        randomShuffle(query_l, seed)
        datadict.append({"s": support, "sl": support_l,
                        "q": query, "ql": query_l})

    return datadict


class LoadDataset:
    def __init__(self, inputdir, way, shot, size=(28, 28), is_train=True):
        self.resize = transforms.Resize(size)
        self.datadict = genDataDict(inputdir, way, shot, is_train)
        self.totensor = transforms.ToTensor()
        self.way = way

    def __len__(self):
        return len(self.datadict)

    def __getitem__(self, idx):
        sl, ql = torch.LongTensor(self.datadict[idx]['sl']), torch.LongTensor(
            self.datadict[idx]['ql'])
        si, qi = self.pathToImg(self.datadict[idx]['s']), self.pathToImg(
            self.datadict[idx]['q'])
        si = torch.stack(si)
        qi = torch.stack(qi)
        # support set, support labels, query set, query labels
        return si, sl, qi, ql

    def genlabels(self, labels):
        res = np.zeros((len(labels), self.way))
        for i in range(res.shape[0]):
            res[i][labels[i]] = 1
        return torch.FloatTensor(res)

    def pathToImg(self, imgPath):
        res = []
        for i in imgPath:
            img = Image.open(i)
            img = self.resize(img)
            img = self.totensor(img)
            res.append(img)
        return res


if __name__ == "__main__":
    data = LoadDataset('./omniglot/', 5, 1, is_train=False)
    si, sl, qi, ql = data.__getitem__(1)
