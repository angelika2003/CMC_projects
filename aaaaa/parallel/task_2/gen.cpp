#include <iostream>
#include <fstream>

int main() {
	std::ofstream file("a.bin", std::ios::binary);

	int32_t data[100 * 100 + 1];
	data[0] = 100;
	for (int i = 1; i <= 100*100; i++) {
		data[i] = i;
	}

	file.write(reinterpret_cast<const char*>(data), sizeof(data));
	file.close();





	std::ofstream file_2("b.bin", std::ios::binary);

	int32_t data0[100 * 100 + 1]; // Пример данных для записи
	data0[0] = 100;

	for (int i = 1; i <= 100 * 100; i++) {
		data0[i] = i;
	}


	// Записываем данные в файл
	file_2.write(reinterpret_cast<const char*>(data0), sizeof(data0));
	file_2.close();

	return 0;
}