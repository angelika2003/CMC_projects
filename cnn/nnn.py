import torch
import torchvision.transforms as transforms
from torchvision.models import alexnet
import time

def preprocess_images(image_paths, batch_size):
    preprocess = transforms.Compose([
    transforms.Resize((224, 224)),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
    ])

    dataset = torch.utils.data.Dataset(image_paths, transform=preprocess)
    loader = torch.utils.data.DataLoader(dataset, batch_size=batch_size, shuffle=False) # Avoid shuffling for consistent timing

    return loader # Return the data loader for iterating over batches

def measure_inference_time(model, data_loader, num_gpus):
    device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
    model.to(device)

    if num_gpus > 1 and torch.cuda.device_count() >= num_gpus:
        model = nn.DataParallel(model, device_ids=list(range(num_gpus)))
    model.eval()

    with torch.no_grad():
        num_iterations = 100
        total_time = 0
        for images, _ in data_loader: # Iterate over batches in the data loader
            start_time = time.time()
            output = model(images.to(device))
            end_time = time.time()
            total_time += end_time - start_time

    return total_time / num_iterations

model = alexnet(pretrained=True)
batch_sizes = [32, 64, 128, 256, 512, 1024, 2048]
num_gpus_list = [1, 2, 4, 8]
image_paths = []
for i in range(1, 3000):
    image_paths.append(f"image_{i}.jpg")


# Assuming you have loaded image paths (e.g., from CIFAR-10) into `image_paths` list
for batch_size in batch_sizes:
    for num_gpus in num_gpus_list:
        print(f"Batch Size: {batch_size}, Number of GPUs: {num_gpus}")
        data_loader = preprocess_images(image_paths[:batch_size], batch_size)
        inference_time = measure_inference_time(model, data_loader, num_gpus)
        print(f"Inference Time (average over {num_iterations} iterations): {inference_time:.4f} seconds")
        print("=" * 50)