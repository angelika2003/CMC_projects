#include <iostream>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <string>
#include <chrono>
#include <vector>

using namespace std;

__global__ void sum_kernel(double *A, double *B, double *C, int n, double a, double b) { 
	int treadLinearIdx = blockIdx.x * blockDim.x + threadIdx.x;

	if (treadLinearIdx < n) {
		double elemA = A[treadLinearIdx];
		double elemB = B[treadLinearIdx];
		C[treadLinearIdx] = elemA * a + elemB * b;
	}
}

#define SAFE_CALL(err) do { if (err != 0) { printf("ERROR [%s] in line %d: %s\n", __FILE__, __LINE__, cudaGetErrorString(err)); exit(1); } } while(0)

int main(int argc, char **argv) {
	double a = stod(argv[1]);
	double b = stod(argv[2]);

	int n = stoi(argv[3]);
	int nb = n * sizeof(double);

	//only cpu code:////////////////
	//memory on host
	double* host_a, *host_b, *host_c, *host_c_gpu;
	SAFE_CALL(cudaMallocHost((void**)&host_a, nb));
	SAFE_CALL(cudaMallocHost((void**)&host_b, nb));
	SAFE_CALL(cudaMallocHost((void**)&host_c, nb));
	SAFE_CALL(cudaMallocHost((void**)&host_c_gpu, nb));

	random_device rd;
	mt19937 gen(rd());

	//fill host_a, host_b
	for (int i = 0; i < n; i++) {
		uniform_real_distribution<double> dis(0.0, 10000.0);

		host_a[i] = dis(gen);
		host_b[i] = dis(gen);
	}

	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		host_c[i] = host_a[i] * a + host_b[i] * b;
	}

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	float time_cpu = duration.count();
	cout << "CPU time: " << time_cpu << "s" << endl;
	////////////////////////////////////////////////



	//memory on device:
	double* device_a, *device_b, *device_c;
	SAFE_CALL(cudaMalloc((void**)&device_a, nb));
	SAFE_CALL(cudaMalloc((void**)&device_b, nb));
	SAFE_CALL(cudaMalloc((void**)&device_c, nb));

	cudaEvent_t start_1, stop_1, start_2, stop_2;
	float time_gpu;
	float time_gpu_cp;

	SAFE_CALL(cudaEventCreate(&start_2));
	SAFE_CALL(cudaEventCreate(&stop_2));
	SAFE_CALL(cudaEventRecord(start_2, 0));

	//copy data from host to device
	SAFE_CALL(cudaMemcpy(device_a, host_a, nb, cudaMemcpyHostToDevice));
	SAFE_CALL(cudaMemcpy(device_b, host_b, nb, cudaMemcpyHostToDevice));


	SAFE_CALL(cudaEventCreate(&start_1));
	SAFE_CALL(cudaEventCreate(&stop_1));
	SAFE_CALL(cudaEventRecord(start_1, 0));

	int threadsPerBlock = 512;
	int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;
	sum_kernel <<< blocksPerGrid, threadsPerBlock>>>(device_a, device_b, device_c, n, a, b);

	SAFE_CALL(cudaDeviceSynchronize());
	SAFE_CALL(cudaEventRecord(stop_1, 0));
	SAFE_CALL(cudaEventElapsedTime(&time_gpu, start_1, stop_1));
	time_gpu /= 1000;

	SAFE_CALL(cudaMemcpy(host_c_gpu, device_c, nb, cudaMemcpyDeviceToHost));
	SAFE_CALL(cudaDeviceSynchronize());

	SAFE_CALL(cudaEventRecord(stop_2, 0));
	SAFE_CALL(cudaDeviceSynchronize());
	SAFE_CALL(cudaEventElapsedTime(&time_gpu_cp, start_2, stop_2));
	time_gpu_cp /= 1000;

		
	SAFE_CALL(cudaEventDestroy(start_1));
	SAFE_CALL(cudaEventDestroy(stop_1));
	SAFE_CALL(cudaEventDestroy(start_2));
	SAFE_CALL(cudaEventDestroy(stop_2));

	cout << "GPU time: " << time_gpu << "s" << endl;
	cout << "GPU time with copy: " << time_gpu_cp << "s" << endl;

	cout << "acceleration: " << time_cpu / time_gpu << endl;
	cout << "acceleration with copy: " << time_cpu / time_gpu_cp << endl;




	int flag = 1;
	for (int i = 0; i < n; i++){
		if (host_c[i] - host_c_gpu[i] > 1e-5){
			flag = 0;
			break;
		}
	}

	if(flag){
		cout << "matrices are equivalent";
	} else {
		cout << "matrices are not equivalent";

	}

	SAFE_CALL(cudaFree(device_a));
	SAFE_CALL(cudaFree(device_b));
	SAFE_CALL(cudaFree(device_c));

	SAFE_CALL(cudaFreeHost(host_a));
	SAFE_CALL(cudaFreeHost(host_b));
	SAFE_CALL(cudaFreeHost(host_c));
	SAFE_CALL(cudaFreeHost(host_c_gpu));


	return 0;
}
