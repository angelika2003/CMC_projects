#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EPS 0.001 // точность конечного результата
#define EPS1 0.0001 // точность нахождения корня
#define EPS2 0.0001 // точность нахождения интеграла
#define K 10 // параметр для облегчения оценки общей точности

#define NUMBER_OF_KEYS 4 // число ключей
// сами ключи
const char* keys[NUMBER_OF_KEYS] = {"-help",
									"-abscissas",
									"-iterations", 
									"-test"};
int key_value[NUMBER_OF_KEYS] = {0}; // введены ли соответствующие ключи

// функции f1, f2, f3
extern double f1 (double x);
extern double f2 (double x);
extern double f3 (double x);

// производные функций f1, f2, f3
extern double t1 (double x);
extern double t2 (double x);
extern double t3 (double x);

// массив для удобства вызова нужных функций с -test
double (*func[])(double x) = {f1, f2, f3, t1, t2, t3};

// функция вычисления корня выражения f(x) - g(x) на отрезке от a до b с точночтью eps1
double root(double f(double), double g(double),
			double tan_f(double), double tan_g(double),
			double a, double b, double eps1) {
	double y_a = f(a) - g(a);
	double y_b = f(b) - g(b);
	
	int i = 0;
	
	while ((fabs(b - a) >= 2 * eps1) || (fabs(y_a - y_b) >= K * eps1)) {
		i++;
		
		double tan_y_b = tan_f(b) - tan_g(b);
		
		a = a - y_a * (b - a) / (y_b - y_a);
		b = b - y_b / tan_y_b;
		
		y_a = f(a) - g(a);
		y_b = f(b) - g(b);
	}
	
	if (key_value[1]) {
		int digits = 0;
		while (eps1 < 1) {
			eps1 *=10;
			digits++;
		}
		
		printf("Корень: %.*lf\n", digits, (a + b) / 2);
	}
	
	if (key_value[2]) {
		printf("Число итераций: %d\n", i);
	}
	
	return (a + b) / 2;
}

// функция вычисления корня выражения f(x) - g(x) на отрезке от a до b с точностью eps1
double integral(double f(double), double a, double b, double eps2) {
	int n = 10000;
	double h = (b - a) / n;
	double res_n;
	double res_2n = 0;
	double x = a + h / 2;
	
	for (int i = 0; i < n; i++) {
		res_2n += f(x) * h;
		x += h;
	}
	
	do {
		res_n = res_2n;
		res_2n = 0;
		n *= 2;
		h /= 2;
		x = a + h / 2;
		
		for (int i = 0; i < n; i++) {
			res_2n += f(x) * h;
			x += h;
		}
		
	} while (fabs(res_2n - res_n) / 3 >= eps2);
	
	return res_2n;
}

int main(int argc, char* argv[]) {
	// обработка ключей командной строки
	int i = 1;
	while (i < argc) {
		for (int j = 0; j < NUMBER_OF_KEYS; j++) {
			if (strcmp(argv[i], keys[j]) == 0) {
				key_value[j] = 1;
				break;
			}
		}
		
		i++;
		
		// -help
		if (key_value[0]) {
			for (int j = 0; j < NUMBER_OF_KEYS; j++) {
				printf("%s\n", keys[j]);
			}
		
			return 0;
		}
		
		// -test
		if (key_value[3]) {
			char* func_name = argv[i];
			
			if (strcmp(func_name, "root\0") == 0) {
				// -test root f g a b eps
				int f = argv[i + 1][0] - '0';
				int g = argv[i + 2][0] - '0';
				double a = strtod(argv[i + 3], 0);
				double b = strtod(argv[i + 4], 0);
				double eps1 = strtod(argv[i + 5], 0);
				
				double res = root(func[f - 1], func[g - 1], func[f + 2], func[g + 2], a, b, eps1);
				int digits = 0;
				while (eps1 < 1) {
					eps1 *=10;
					digits++;
				}
				printf("%.*lf\n", digits, res);
			} else if (strcmp(func_name, "integral\0") == 0) {
				// -test integral f a b eps
				int f = argv[i + 1][0] - '0';
				double a = strtod(argv[i + 2], 0);
				double b = strtod(argv[i + 3], 0);
				double eps2 = strtod(argv[i + 4], 0);
				
				double res = integral(func[f - 1], a, b, eps2);
				int digits = 0;
				while (eps2 < 1) {
					eps2 *=10;
					digits++;
				}
				printf("%.*lf\n", digits, res);
			}
			
			return 0;
		}
	}
	
	// поиск корней
	
	char print_msg = (key_value[1] || key_value[2]);
	
	if (print_msg) {
		printf("Поиск пересечения f1 и f2\n");
	}

	double root12 = root(f1, f2, t1, t2, -0.5, -0.2, EPS1);
	
	if (print_msg) {
		printf("Поиск пересечения f1 и f3\n");
	}
	
	double root13 = root(f3, f1, t3, t1, -6, -3, EPS1);
	
	if (print_msg) {
		printf("Поиск пересечения f2 и f3\n");
	}
	
	double root23 = root(f2, f3, t2, t3, -2, -1.5, EPS1);
	
	// поиск площади под графиком
	
	double i_1 = integral(f1, root13, root12, EPS2);
	double i_2 = integral(f2, root23, root12, EPS2);
	double i_3 = integral(f3, root13, root23, EPS2);
	
	double res = i_1 - i_2 - i_3;
	
	int digits = 0;
	double eps = EPS;
	while (eps < 1) {
		eps *=10;
		digits++;
	}
	
	printf("Результат = %.*lf\n", digits, res);
	
	return 0;
}