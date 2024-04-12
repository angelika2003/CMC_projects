#include "IL/il.h"
#include <stdlib.h>
#include <IL/devil_cpp_wrapper.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cuda_runtime.h>
#include <string>
#include <chrono>
#include <fstream>
using namespace std;

bool compareImages(const std::string& imageFile1, const std::string& imageFile2) {
    // Открываем файлы с изображениями в двоичном режиме
    std::ifstream file1(imageFile1, std::binary);
    std::ifstream file2(imageFile2, std::binary);

    file1.seekg(0, std::ios::end);
    file2.seekg(0, std::ios::end);
    std::streamsize size1 = file1.tellg();
    std::streamsize size2 = file2.tellg();

    if (size1 != size2) {
        std::cout << "Размеры изображений не совпадают." << std::endl;
        return false;
    }

    // Возвращаем указатель чтения в начальное положение
    file1.seekg(0, std::beg);
    file2.seekg(0, std::beg);

    // Сравниваем пиксели изображений по байтам
    if (size1 > 0) {
        // Выделяем память для буферов
        char* buffer1 = new char[size1];
        char* buffer2 = new char[size1];

        // Читаем содержимое файлов в буферы
        file1.read(buffer1, size1);
        file2.read(buffer2, size1);

        // Сравниваем содержимое буферов
        bool result = (std::memcmp(buffer1, buffer2, size1) == 0);

        // Освобождаем выделенную память
        delete[] buffer1;
        delete[] buffer2;

        // Возвращаем результат сравнения
        return result;
    }

__device__ __host__ void func(int *arr, int size, ILubyte *Data_1, ILubyte*res, int h, int w, int n_str, int x, int y) {
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

			newValue += Data_1[(offsetY * w + offsetX) * 3 + n_str] * arr[i * size + j];
		}
	}
	// Ограничение значений от 0 до 255
	newValue = min(max(newValue, 0), 255);

	// Сохранение нового значения
	res[(y * w + x) * 3 + n_str] = static_cast<ILubyte>(newValue);
	
}

#define SAFE_CALL(err) do { if (err != 0) { printf("ERROR [%s] in line %d: %s\n", __FILE__, __LINE__, cudaGetErrorString(err)); exit(1); } } while(0)

__global__ void Kernel(int *arr, int size, ILubyte *Data_1, ILubyte*res, int h, int w, int n_str) {
	int x = blockIdx.x;
	int y = threadIdx.x;

	func(arr, size, Data_1, res, h, w, n_str, x, y);
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
				func(matrix, size, originalData, data, h, w, c, x, y);
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
	ILboolean saved = ilSaveImage("res_cpu_5.bmp");
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


	cudaEvent_t start_1, stop_1;
	float time_gpu;
	SAFE_CALL(cudaEventCreate(&start_1));
	SAFE_CALL(cudaEventCreate(&stop_1));
	SAFE_CALL(cudaEventRecord(start_1, 0));

////
	cudaStream_t streams[3];
	for (int i = 0; i < 3; ++i) {
        SAFE_CALL(cudaStreamCreate(&streams[i]));
    }
////

	//copy data from host to device
	SAFE_CALL(cudaMemcpy(arr, matrix, n * n * sizeof(int) , cudaMemcpyHostToDevice));

	SAFE_CALL(cudaMemcpy(Data_1, originalData, w * h * 3 * sizeof(unsigned char), cudaMemcpyHostToDevice));


	Kernel <<< h, w, 0, streams[0] >>>(arr, size, Data_1, res, h, w, 0);
	Kernel <<< h, w, 0, streams[1] >>>(arr, size, Data_1, res, h, w, 1);
	Kernel <<< h, w, 0, streams[2] >>>(arr, size, Data_1, res, h, w, 2);

///////////

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
	ILboolean saved_2 = ilSaveImage("res_gpu_5.bmp");
	if (saved_2 == IL_FALSE)
	{
		printf("%s\n", iluErrorString(ilGetError()));
		return -1; /* error encountered during loading */
	}

//ident
	if (compareImages("res_cpu_5.bmp", "res_cpu_5.bmp")) {
        std::cout << "Изображения идентичны." << std::endl;
    } else {
        std::cout << "Изображения различаются." << std::endl;
    }	

	// Finally, clean the mess! 
	ilDeleteImages(1, & handle);

////
	for (int i = 0; i < 3; ++i) {
        SAFE_CALL(cudaStreamDestroy(streams[i]));
    }
/////

	SAFE_CALL(cudaFree(Data_1));
	SAFE_CALL(cudaFree(arr));
	SAFE_CALL(cudaFree(res));

	free(data); data = NULL;
	free(originalData);
	free(data_gpu);

	return 0;
}
