#include <stdio.h>
#include <stdlib.h>

void print_array(int *a, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

	return;
}

int* new_sorted_array(int n) {   //массив, упорядоченный по возрастанию
	int* array = (int*)malloc(n * sizeof(int));

	for (int i = 1; i <= n; i++) {
		array[i - 1] = i;
	}

	//print_array(array, n);

	return array;
}

int* new_worst_array(int n) {   //массив, упорядоченный по невозврастанию
	int* array = (int*)malloc(n * sizeof(int));

	for (int i = n - 1; i >= 0; i--) {
		array[i] = n - i;
	}

	//print_array(array, n);

	return array;
}

int* new_random_array(int n) {  //случайный массив
	int* array = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		array[i] = rand() * rand();
	}

	//print_array(array, n);

	return array;
}

int *array_copy(int *a, int n) {
	int *b = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		b[i] = a[i];
	}

	return b;
}

void bubble_sort(int *a, int n) {
	int comparisons = 0; //кол-во сравнений
	int exchanges = 0; // кол-во обменов

	for (int i = 0 ; i < n - 1; i++) {         // сравниваем два соседних элемента.
		for (int j = 0 ; j < n - i - 1 ; j++) {
			comparisons++;
			if (a[j] > a[j + 1]) {  		// если они идут в неправильном порядке, то
				int tmp = a[j];              // меняем их местами.
				a[j] = a[j + 1] ;
				a[j + 1] = tmp;
				exchanges++;
			}
		}
	}
	printf("сортировка пузырьком:\n");
	//print_array(a, n);
	printf("%d сравнений, %d обменов\n", comparisons, exchanges);

	return;
}

void shell_sort(int *a, int n) {
	int comparisons = 0; //кол-во сравнений
	int exchanges = 0; // кол-во обменов

	for (int s = n / 2; s > 0; s /= 2) {     //шаг для разделения на наборы.
		for (int i = s; i < n; ++i) {        //последний элемент набора.
			int j;
			for (j = i - s; j >= 0 && a[j] > a[j + s]; j -= s, comparisons++) {  //сортировка вставками для набора.
				int tmp = a[j];
				a[j] = a[j + s];
				a[j + s] = tmp;
				exchanges++;
			}
			if (j >= 0) {
				comparisons++;
			}
		}
	}

	printf("сортировка методом Шелла:\n");
	//print_array(a, n);
	printf("%d сравнений, %d обменов\n", comparisons, exchanges);

	return;
}

void test(int n) {
	int *a1 = new_sorted_array(n);
	int *a2 = array_copy(a1, n);
	bubble_sort(a1, n);
	shell_sort(a2, n);
	printf("\n");
	free(a1);
	free(a2);

	a1 = new_worst_array(n);
	a2 = array_copy(a1, n);
	bubble_sort(a1, n);
	shell_sort(a2, n);
	printf("\n");
	free(a1);
	free(a2);

	a1 = new_random_array(n);
	a2 = array_copy(a1, n);
	bubble_sort(a1, n);
	shell_sort(a2, n);
	printf("\n");
	free(a1);
	free(a2);

	a1 = new_random_array(n);
	a2 = array_copy(a1, n);
	bubble_sort(a1, n);
	shell_sort(a2, n);
	free(a1);
	free(a2);
}


int main(void) {
	int n;
	scanf("%d", &n);

	test(n);

	return 0;
}
