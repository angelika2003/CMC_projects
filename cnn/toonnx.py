import torch.onnx
import torch

# Определяем модель и передаем ее в режим eval перед экспортом
model = ConvNet()
model.eval()

batch_size = 1
dummy_input = torch.randn(batch_size, 3, 32, 32)  # Создаем такой же dummy_input, как и ранее

# Сохраняем модель в формате ONNX
onnx_path = "conv_net.onnx"
torch.onnx.export(model, dummy_input, onnx_path)

print(f"Модель успешно сохранена в формате ONNX по пути: {onnx_path}")