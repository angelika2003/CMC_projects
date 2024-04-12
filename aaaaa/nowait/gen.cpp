#include <iostream>
#include <fstream>

int main() {
	int n = 1000;
	std::ofstream file("a.bin", std::ios::binary);
	int32_t *data = (int32_t *)calloc(n * n + 1, sizeof(int32_t));
	data[0] = n;

	for (int i = 1; i <= (n * n) / 2; i++) {
		data[i] = 1000;
	}

	file.write(reinterpret_cast<const char*>(data), (n * n + 1) * sizeof(int32_t));
	file.close();






	std::ofstream file_1("b.bin", std::ios::binary);
	int32_t *data1 = (int32_t *)calloc(n * n + 1, sizeof(int32_t));
	data1[0] = n;
	for (int i = (n * n) / 2; i <= n * n + 1; i++) {
		data1[i] = 1000;
	}

	file_1.write(reinterpret_cast<const char*>(data1), (n * n + 1) * sizeof(int32_t));
	file_1.close();

	return 0;
}