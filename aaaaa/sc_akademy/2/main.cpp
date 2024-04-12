#include "IL/il.h"
#include <stdlib.h>
#include <IL/devil_cpp_wrapper.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
#define SAFE_CALL(err) do { if (err != 0) { printf("ERROR [%s] in line %d: %s\n", __FILE__, __LINE__, cudaGetErrorString(err)); exit(1); } } while(0)

__global__ void Kernel(int *matrix, int size, unsigned char*Data_1, unsigned_char*arr, unsigned_char*res, int h, int w) {
	int y = blockIdx.x;
	int x = threadIdx.x;
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
	ILboolean loaded = ilLoadImage("original_file.bmp");
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
	ilCopyPixels(0, 0, 0, w, h, 1, IL_RGB, IL_UNSIGNED_BYTE, data);
	ILubyte * data_2 = (ILubyte *)malloc(memory_needed);
	ilCopyPixels(0, 0, 0, w, h, 1, IL_RGB, IL_UNSIGNED_BYTE, data);


	int *matrix = (int **)malloc(n * n * sizeof(int));
	for (int i = 0; i < n * n; i++) {
		matrix[i] = -1;
	}

	matrix[size(n / 2) + n / 2] = n * n;

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
	ILboolean saved = ilSaveImage("our_result.bmp");
	if (saved == IL_FALSE)
	{
		printf("%s\n", iluErrorString(ilGetError()));
		return -1; /* error encountered during loading */
	}

	/* Finally, clean the mess! */
	ilDeleteImages(1, & handle);
	free(data); data = NULL;
	free(originalData);

	//memory on device:
	int* device_a, *device_b, *device_c;
	SAFE_CALL(cudaMalloc((void**)&Data_1, w * h * 3 * sizeof(unsigned char)));
	SAFE_CALL(cudaMalloc((void**)&arr, n * n * sizeof(int)));
	SAFE_CALL(cudaMalloc((void**)&res, w * h * 3 * sizeof(unsigned char)));

	//copy data from host to device
	SAFE_CALL(cudaMemcpy(Data_1, host_a, w * h * 3 * sizeof(unsigned char), cudaMemcpyHostToDevice));
	SAFE_CALL(cudaMemcpy(arr, matrix, n * n * sizeof(int) , cudaMemcpyHostToDevice));


	sum_kernel <<< h, w >>>(matrix, size, Data_1, arr, res, h, w);
	SAFE_CALL(cudaDeviceSynchronize());
	SAFE_CALL(cudaMemcpy(res, data_2 , nb, cudaMemcpyDeviceToHost));

	SAFE_CALL(cudaFree(Data_1));
	SAFE_CALL(cudaFree(arr));
	SAFE_CALL(cudaFree(res));

	return 0;
}
