import torch.nn as nn


class MLP(nn.Module):
    def __init__(self, input_n, output_n, layer_list, num_layer=2):
        super(MLP, self).__init__()
        self.input_n = input_n
        self.output_n = output_n
        self.num_layer = num_layer
        self.layer_list = layer_list
        self.linear_1 = nn.Linear(input_n, layer_list[0])
        self.relu = nn.ReLU()
        self.linear_2 = nn.Linear(layer_list[1], output_n)

    def forward(self, x):
        x = self.linear_1(x)
        x = self.relu(x)
        x = self.linear_2(x)
        return x


if __name__ == '__main__':
    None
