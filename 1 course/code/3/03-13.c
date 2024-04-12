#include <stdio.h>

void print_array(int arr[], int arr_size) {
	for (int i = 0; i < arr_size; printf("%d ", arr[i++]));
	printf("\n");
}

void sequence(int max_number, int len, int len_sbstr, int arr[]) {
	if (len_sbstr == 0) {
		print_array(arr, len);
	} else {
		int index = len - len_sbstr;
		int j = index > 0 ? arr[index - 1] + 1 : 0;
		for (int i = j; i <= max_number - len_sbstr; i++) {
			arr[index] = i;
			sequence(max_number, len, len_sbstr - 1, arr);
		}
	}
}

int main(void) {
	int N, len;
	scanf("%d %d", &N, &len);

	int arr[len];
	sequence(N, len, len, arr);

	return 0;
}