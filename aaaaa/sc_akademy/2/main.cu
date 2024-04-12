#include "IL/il.h"
#include <stdlib.h>
#include <IL/devil_cpp_wrapper.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cuda_runtime.h>
#include <string>
#include <chrono>

using namespace std;
#define SAFE_CALL(err) do { if (err != 0) { printf("ERROR [%s] in line %d: %s\n", __FILE__, __LINE__, cudaGetErrorString(err)); exit(1); } } while(0)

__global__ void Kernel(int *arr, int size, ILubyte *Data_1, ILubyte*res, int h, int w) {
	int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
	for (int c = 0; c < 3; ++c) {
		int newValue = 0;
		int offset = size / 2;

		for (int i = 0; i < size; ++i) {
			int offsetY = y + i - offset;
			if (offsetY < 0) {
				offsetY = -offsetY;
			}
			if (offsetY >= h) {
				offsetY = 2 * h - offsetY - 1;
			}

			for (int j = 0; j < size; ++j) {
				int offsetX = x + j - offset;
				if (offsetX < 0) {
					offsetX = -offsetX;
				}
				if (offsetX >= w) {
					offsetX = 2 * w - offsetX - 1;
				}

				newValue += Data_1[(offsetY * w + offsetX) * 3 + c] * arr[i * size + j];
			}
		}
		// Ограничение значений от 0 до 255
		newValue = min(max(newValue, 0), 255);

		// Сохранение нового значения
		res[(y * w + x) * 3 + c] = static_cast<ILubyte>(newValue);
	}
}

int main(int argc, const char * argv[]) {
	int n = atoi(argv[1]);

	ILuint handle, w, h;

	/* First we initialize the library. */
	ilInit();

	/* We want all images to be loaded in a consistent manner */
	ilEnable(IL_ORIGIN_SET);

	/* In the next section, we load one image */
	ilGenImages(1, & handle);
	ilBindImage(handle);
	ILboolean loaded = ilLoadImage("pic.bmp");
	if (loaded == IL_FALSE)
	{
		printf("%s\n", iluErrorString(ilGetError()));
		return -1; /* error encountered during loading */
	}

	/* Let's spy on it a little bit */
	w = ilGetInteger(IL_IMAGE_WIDTH); // getting image width
	h = ilGetInteger(IL_IMAGE_HEIGHT); // and height
	printf("Our image resolution: %dx%d\n", w, h);

	/* how much memory will we need? */
	int memory_needed = w * h * 3 * sizeof(unsigned char);
	ILubyte * originalData = (ILubyte *)malloc(memory_needed);
	ilCopyPixels(0, 0, 0, w, h, 1, IL_RGB, IL_UNSIGNED_BYTE, originalData);
	ILubyte * data = (ILubyte *)malloc(memory_needed);
	//ilCopyPixels(0, 0, 0, w, h, 1, IL_RGB, IL_UNSIGNED_BYTE, data);
	ILubyte * data_gpu = (ILubyte *)malloc(memory_needed);
	//ilCopyPixels(0, 0, 0, w, h, 1, IL_RGB, IL_UNSIGNED_BYTE, data_gpu);


	int *matrix = (int *)malloc(n * n * sizeof(int));
	for (int i = 0; i < n * n; i++) {
		matrix[i] = -1;
	}

	matrix[n * (n / 2) + n / 2] = n * n;

	int size = n;

	auto start = chrono::high_resolution_clock::now();
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			for (int c = 0; c < 3; ++c) {
				int newValue = 0;
				int offset = size / 2;

				// Проход по окрестности пикселя с учетом матрицы фильтра
				for (int i = 0; i < size; ++i) {
					int offsetY = y + i - offset;
					if (offsetY < 0) {
						offsetY = -offsetY;
					}
					if (offsetY >= h) {
						offsetY = 2 * h - offsetY - 1;
					}

					for (int j = 0; j < size; ++j) {
						int offsetX = x + j - offset;
						if (offsetX < 0) {
							offsetX = -offsetX;
						}
						if (offsetX >= w) {
							offsetX = 2 * w - offsetX - 1;
						}

						newValue += originalData[(offsetY * w + offsetX) * 3 + c] * matrix[i * size + j];
					}
				}
				// Ограничение значений от 0 до 255
				newValue = min(max(newValue, 0), 255);

				// Сохранение нового значения
				data[(y * w + x) * 3 + c] = static_cast<ILubyte>(newValue);
			}
		}
	}

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	float time_cpu = duration.count();
	cout << "CPU : " << w*h / time_cpu / 1000000.0 << "mp/s" << endl;

	/* And maybe we want to save that all... */
	ilSetPixels(0, 0, 0, w, h, 1, IL_RGB, IL_UNSIGNED_BYTE, data);
	/* and dump them to the disc... */
	ILboolean saved = ilSaveImage("result_cpu_5.bmp");
	if (saved == IL_FALSE)
	{
		printf("%s\n", iluErrorString(ilGetError()));
		return -1; /* error encountered during loading */
	}

	//memory on device:
	ILubyte * Data_1, *res;
	int* arr;
	SAFE_CALL(cudaMalloc((void**)&Data_1, w * h * 3 * sizeof(unsigned char)));
	SAFE_CALL(cudaMalloc((void**)&arr, n * n * sizeof(int)));
	SAFE_CALL(cudaMalloc((void**)&res, w * h * 3 * sizeof(unsigned char)));

	//copy data from host to device
	SAFE_CALL(cudaMemcpy(arr, matrix, n * n * sizeof(int) , cudaMemcpyHostToDevice));

	SAFE_CALL(cudaMemcpy(Data_1, originalData, w * h * 3 * sizeof(unsigned char), cudaMemcpyHostToDevice));
	//SAFE_CALL(cudaMemcpy(arr, matrix, n * n * sizeof(int) , cudaMemcpyHostToDevice));

	cudaEvent_t start_1, stop_1;
	float time_gpu;
	SAFE_CALL(cudaEventCreate(&start_1));
	SAFE_CALL(cudaEventCreate(&stop_1));
	SAFE_CALL(cudaEventRecord(start_1, 0));


	dim3 blockDims(16, 16);
    dim3 gridDims((w + blockDims.x - 1) / blockDims.x, (h + blockDims.y - 1) / blockDims.y);
	Kernel <<< gridDims, blockDims >>>(arr, size, Data_1, res, h, w);
	SAFE_CALL(cudaDeviceSynchronize());
	SAFE_CALL(cudaEventRecord(stop_1, 0));
	SAFE_CALL(cudaEventElapsedTime(&time_gpu, start_1, stop_1));
	time_gpu /= 1000;

	SAFE_CALL(cudaEventDestroy(start_1));	
	SAFE_CALL(cudaEventDestroy(stop_1));
	cout << "GPU : " << w*h / time_gpu / 1000000.0 << "mp/s" << endl;

	SAFE_CALL(cudaMemcpy(data_gpu, res, w * h * 3 * sizeof(unsigned char), cudaMemcpyDeviceToHost));



	/* And maybe we want to save that all... */
	ilSetPixels(0, 0, 0, w, h, 1, IL_RGB, IL_UNSIGNED_BYTE, data_gpu);
	/* and dump them to the disc... */
	ILboolean saved_2 = ilSaveImage("result_gpu_5.bmp");
	if (saved_2 == IL_FALSE)
	{
		printf("%s\n", iluErrorString(ilGetError()));
		return -1; /* error encountered during loading */
	}

	// Finally, clean the mess! 
	ilDeleteImages(1, & handle);

	SAFE_CALL(cudaFree(Data_1));
	SAFE_CALL(cudaFree(arr));
	SAFE_CALL(cudaFree(res));

	free(data); data = NULL;
	free(originalData);
	free(data_gpu);

	return 0;
}
