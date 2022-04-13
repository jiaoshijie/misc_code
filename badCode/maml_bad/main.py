from data_loader import LoadDataset
from maml import MAML
import torch
from torch.utils.data import DataLoader
import torch.optim as optimizer
from tqdm import tqdm
import torch.autograd as autograd
from collections import OrderedDict


def train(model, train_dataset, test_dataset, device):
    optim = optimizer.SGD(model.parameters(), lr=0.1, momentum=0.9)
    for epoch in range(32):
        print("running is {}".format(epoch))
        acc = 0
        model.train(True)
        for data in tqdm(train_dataset):
            s, sl, q, ql = data
            s, q = s.to(device), q.to(device)
            sl, ql = sl.to(device), ql.to(device)
            losses, acc = model(s, sl, q, ql, num_updates=1, is_train=True)
            losses = torch.mean(losses)
            optim.zero_grad()
            losses.backward()
            optim.step()
        print("train_acc: ", acc)
        print("loss: ", losses)

        # best_acc = 0
        # model.eval()
        # for test_data in tqdm(test_dataset):
        #     s, sl, q, ql = data
        #     s, q = s.to(device), q.to(device)
        #     sl, ql = sl.to(device), ql.to(device)
        #     _, test_acc = model(s, sl, q, ql, num_updates=3, is_train=False)
        #     if best_acc < test_acc:
        #         best_acc = test_acc
        #         torch.save(model.state_dict(), './best.pt')
        # print("test_acc: ", best_acc)


def main():
    device = torch.device('cuda')

    way, shot = 20, 5

    train_data = DataLoader(
        LoadDataset('./omniglot/', way, shot, is_train=False),
        batch_size=32, num_workers=4, shuffle=False, pin_memory=True
    )
    test_data = DataLoader(
        LoadDataset('./omniglot/', way, shot, is_train=False),
        batch_size=32, num_workers=4, shuffle=False, pin_memory=True
    )
    # test_data = None
    model = MAML(way, shot, lr=0.4)
    model = model.to(device)
    train(model, train_data, test_data, device)


if __name__ == "__main__":
    main()
