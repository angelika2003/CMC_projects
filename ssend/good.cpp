#include <iostream>
#include <mpi.h>
#include <vector>

// Функция, для которой вычисляется интеграл
double f(double x) {
	return x * x;
}

using namespace std;

int main(int argc, char** argv) {
		clock_t start_time, end_time;
	double cpu_time_used;

	start_time = clock();
// Инициализация MPI
	MPI_Init(&argc, &argv);

// Получение идентификатора MPI-процесса
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);


// Определение параметров
	const double a = 0.0;
	const double b = 5000.0;
	const int n = 100000000;

// Вычисление локального интеграла
	double local_integral = 0.0;
	for (int i = rank; i < n; i += size) {
		double h = (b - a) / n;
		double x_i = a + i * h;
		double x_i_next = a + (i + 1) * h;
		local_integral += (f(x_i) + f(x_i_next)) * h / 2.0;
	}

// Сбор локальных интегралов в буфере
	vector<double> local_integrals(size);
	MPI_Gather(&local_integral, 1, MPI_DOUBLE, local_integrals.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

// Вычисление общего интеграла в главном процессе
	double total_integral = 0.0;
	if (rank == 0) {
		for (double integral : local_integrals) {
			total_integral += integral;
		}
		cout << "Total integral: " << total_integral << endl;
		end_time = clock();
		cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
		printf("Время выполнения: %f секунд\n", cpu_time_used);
	}

// Завершение MPI
	MPI_Finalize();
	return 0;
}