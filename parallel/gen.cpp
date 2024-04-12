#include <iostream>
#include <fstream>

int main() {
	/*	std::ofstream file("a.bin", std::ios::binary);

		int32_t *data = (int32_t *)calloc(9000 * 9000 + 2, sizeof(*data));
		data[0] = 9000;
		data[1] = 9000;
		for (int i = 2; i <= 9000 * 9000 + 1; i++) {
			data[i] = 1;
		}

		file.write(reinterpret_cast<const char*>(data), sizeof(data));
		file.close();





		std::ofstream file_2("b.bin", std::ios::binary);

		int32_t *data1 = (int32_t *)calloc(9000+1, sizeof(*data1));
		data1[0] = 9000;

		for (int i = 1; i <= 9000; i++) {
			data1[i] = 1;
		}

		file_2.write(reinterpret_cast<const char*>(data1), sizeof(data1));
		file_2.close();*/
	int n = 1536;
	int n_1 = 3072;
	std::ofstream file("a.bin", std::ios::binary);
	int32_t *data = (int32_t *)calloc(n * n + 1, sizeof(int32_t));
	data[0] = n;

	for (int i = 1; i <= n * n; i++) {
		data[i] = 1;
	}
	file.write(reinterpret_cast<const char*>(data), (n * n + 1) * sizeof(int32_t));
	file.close();


	std::ofstream file_1("b.bin", std::ios::binary);
	int32_t *data1 = (int32_t *)calloc(n*n + 1, sizeof(int32_t));
	data1[0] = n;
	for (int i = 1; i <= n*n; i++) {
		data1[i] = 1;
	}
	file_1.write(reinterpret_cast<const char*>(data1), (n*n + 1) * sizeof(int32_t));
	file_1.close();



	std::ofstream file_2("a_1.bin", std::ios::binary);
	int32_t *data2 = (int32_t *)calloc(n_1 * n_1 + 1, sizeof(int32_t));
	data2[0] = n_1;
	for (int i = 1; i <= n_1 * n_1; i++) {
		data2[i] = 1;
	}
	file_2.write(reinterpret_cast<const char*>(data2), (n_1 * n_1 + 1) * sizeof(int32_t));
	file_2.close();

	std::ofstream file_3("b_1.bin", std::ios::binary);
	int32_t *data3 = (int32_t *)calloc(n_1 * n_1 + 1, sizeof(int32_t));
	data3[0] = n_1;
	for (int i = 1; i <= n_1 * n_1; i++) {
		data3[i] = 1;
	}
	file_3.write(reinterpret_cast<const char*>(data3), (n_1 * n_1 + 1) * sizeof(int32_t));
	file_3.close();
	return 0;
}