import torch
import time

# Задаем параметры
batch_sizes = [32, 64, 128]  # Размеры мини-батча
num_gpus = [1, 2, 4]  # Количество используемых GPU

# Создаем сверточную нейронную сеть для тестирования
class ConvNet(torch.nn.Module):
    def __init__(self):
        super(ConvNet, self).__init__()
        self.conv1 = torch.nn.Conv2d(3, 10, kernel_size=3)
        self.pool = torch.nn.MaxPool2d(2, 2)

    def forward(self, x):
        x = self.pool(torch.relu(self.conv1(x)))
        return x

# Функция для измерения времени вывода
def benchmark(batch_size, num_gpu):
    model = ConvNet()
    device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
    model.to(device)

    dummy_input = torch.randn(batch_size, 3, 32, 32).to(device)

    if num_gpu > 1 and torch.cuda.is_available():
        model = torch.nn.DataParallel(model, device_ids=[i for i in range(num_gpu)])

    start_time = time.time()
    output = model(dummy_input)
    end_time = time.time()

    return end_time - start_time

# Выполняем эксперименты
for batch_size in batch_sizes:
    for num_gpu in num_gpus:
        time_taken = benchmark(batch_size, num_gpu)
        print(f"Time taken for batch size {batch_size} and {num_gpu} GPU(s): {time_taken} seconds")
