import torchvision
import torchvision.transforms as transforms

trainset = torchvision.datasets.CIFAR10(root='/home/admin/kozintseva_323', train=True, download=True, transform=transform)

# Получение изображений и меток
images = []
for i in range(3000):  
    image, label = trainset[i]
    images.append(image)

# Сохранение изображений на диск
for i, image in enumerate(images):
    torchvision.utils.save_image(image, f'image_{i}.jpg')
