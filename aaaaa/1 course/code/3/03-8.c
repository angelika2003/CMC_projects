 #include <stdio.h>

void swap(int *arr, int *arr_new) {
	int tmp = *arr;
	*arr = *arr_new;
	*arr_new = tmp;
}

int median(int a, int b, int c) {
	if (a > b) {
		swap(&a, &b);
	}
	
	if (b > c) {
		swap(&b, &c);
	}

	if (a > b) {
		swap(&a, &b);
	}

	return b;
}

int new_array(int arr[], int N) {
	if (N == 1) {
		return arr[0];
	}

	int arr_new[N - 2];
	for (int i = 0; i < N - 2; i++) {
		arr_new[i] = median(arr[i], arr[i + 1], arr[i + 2]);
	}

	return new_array(arr_new, N - 2);
}

int main(void) {
	int N;
	scanf("%d", &N);

	int arr[N];
	for (int i = 0; i < N; scanf("%d", &arr[i++]));

	printf("%d", new_array(arr, N));

	return 0;
}