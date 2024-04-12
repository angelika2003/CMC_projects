#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EPS 0.001   // точность конечного результата
#define EPS1 0.0001 // точность нахождения корня
#define EPS2 0.0001 // точность нахождения интеграла

#define NUMBER_OF_KEYS 6 // число ключей
//массив с ключами
const char* keys[NUMBER_OF_KEYS] = {"-help",
                                    "-points",
                                    "-iterations",
                                    "-area",
                                    "-test_integral",
                                    "-test_root",
                                   };
int key_flag[NUMBER_OF_KEYS] = {0};

extern double f1 (double x);
extern double f2 (double x);
extern double f3 (double x);

extern double df1 (double x);
extern double df2 (double x);
extern double df3 (double x);

double (*func[])(double x) = {f1, f2, f3, df1, df2, df3};

double root(double f(double), double g(double), double df(double), double dg(double), double a, double b, double eps) {
	static int i = 0;

	if (((fabs(f(a) - g(a)) < eps) || (fabs(f(b) - g(b)) < eps)) && key_flag[2]) {
		int f1_int;
		int f2_int;

		for (int j = 0; j < 3; j++) {
			if (f == func[j]) {
				f1_int = j;
			}

			if (f == func[j]) {
				f2_int = j;
			}
		}

		printf("Iterations for find f%d and f%d intersection: %d\n", f1_int, f2_int, i);

	}

	if (fabs(f(a) - g(a)) < eps)  {
		return a;
	}

	if (fabs(f(b) - g(b)) < eps)  {
		return b;
	}

	double y_a = f(a) - g(a);
	double y_b = f(b) - g(b);

	double new_x = a - y_a * (b - a) / (y_b - y_a);

	if ((f(new_x) - g(new_x)) * (df(new_x) - dg(new_x)) <= 0) {
		a = new_x;
	} else {
		b = new_x;
	}

	i++;
	return root(f, g, df, dg, a, b, eps);
}

double integral(double f(double), double a, double b, double eps) {
	double integral_1 = 0;
	double integral_2 = 0;
	double width = fabs(a - b) / 1000;
	double x = a;

	x += (width / 2);
	do {
		integral_2 += f(x) * width;
		x += width;
	} while (x < b);

	while (fabs(integral_2 - integral_1) > 3*eps) {
		integral_1 = integral_2;
		integral_2 = 0;
		x = a;
		width /= 2;

		x += (width / 2);
		do {
			integral_2 += f(x) * width;
			x += width;
		} while (x < b);
	}

	return integral_2;

}

void test_integral() {
	double intg_1 = integral(f1, 7, 10, 0.0001);
	printf("1) integral(f1, 7, 10, 0.0001) = %.4f\n", intg_1);
	double intg_2 = integral(f2, 5, 7, 0.001);
	printf("2) integral(f2, 5, 7, 0.001) = %.3f\n", intg_2);
	double intg_3 = integral(f3, 4, 10, 0.01);
	printf("3) integral(f3, 4, 10, 0.01) = %.2f\n", intg_3);		
}

void test_root() {
	double x_12 = root(f1, f2, df1, df2, 5, 10, 0.001);
	printf("1) root(f1, f2, 5, 10, 0.001) = %.3f\n", x_12);	
	double x_23 = root(f2, f3, df2, df3, 3, 11, 0.001);
	printf("2) root(f2, f3, 3, 11, 0.001) = %.3f\n", x_23);	
	double x_13 = root(f1, f3, df1, df3, 2.01, 4, 0.001);
	printf("3) root(f1, f3, 2.01, 4, 0.001) = %.3f\n", x_13);
}


int main(int argc, char *argv[]) {

//обработка ключей командной строки
	for (int i = 1; i < argc; i++) {   //введённых ключей argc-1 шт
		for (int j = 0; j < NUMBER_OF_KEYS; j++) {
			if (strcmp(argv[i], keys[j]) == 0) {
				key_flag[j] = 1;
			}
		}
	}

//-help
	if (key_flag[0]) {
		for (int i = 0; i < NUMBER_OF_KEYS; i++) {
			printf("%s\n", keys[i]);
		}
	}

	double x_12 = root(f1, f2, df1, df2, 1, 30, EPS1);
	double x_23 = root(f2, f3, df2, df3, 5, 20, EPS1);
	double x_13 = root(f1, f3, df1, df3, 2.1, 3, EPS1);

//-points
	if (key_flag[1]) {
		printf("f1 and f2: %.4f\n", x_12);
		printf("f2 and f3: %.4f\n", x_23);
		printf("f1 and f3: %.4f\n", x_13);
	}

//-area
	if (key_flag[3]) {
		double area_1 = integral(f1, x_13, x_12, EPS);
		double area_2 = integral(f2, x_23, x_12, EPS);
		double area_3 = integral(f3, x_13, x_23, EPS);

		double res_area = area_3 + area_2 - area_1;
		printf("area: %f %f %f %f",area_3, area_2, area_1,res_area);
	}

//-test_integral
	if (key_flag[4]) {
		test_integral();
	}

//-test_root
	if (key_flag[5]) {
		test_root();
	}

	return 0;
}