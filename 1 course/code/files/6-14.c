#include <stdio.h>

#define BYTE 8
#define MASK 0xFF

int main(void) {
	FILE *f = fopen("matrix.in", "rb");

	unsigned char byte_1;
	fread(&byte_1, sizeof(char), 1, f);

	unsigned char byte_2;
	fread(&byte_2, sizeof(char), 1, f);

	int matrix_size = byte_1 << BYTE | byte_2;

	int step = matrix_size * 4;

	unsigned char b_1;
	unsigned char b_2;
	unsigned char b_3;
	unsigned char b_4;

	long long sum = 0;
	int cur;

	for (int i = 0; i < matrix_size; ++i) {
		fread(&b_1, sizeof(char), 1, f);
		fread(&b_2, sizeof(char), 1, f);
		fread(&b_3, sizeof(char), 1, f);
		fread(&b_4, sizeof(char), 1, f);

		cur = (int)b_1 << BYTE | b_2;
		cur = cur << BYTE | b_3;
		cur = cur << BYTE | b_4;

		sum += cur;

		if (i != matrix_size - 1) {
			fseek(f, step, 1);
		}
	}

	fclose(f);

	FILE *f1 = fopen("trace.out", "wb");

	for (int i = 0; i < BYTE; ++i) {
		char byte = (sum >> (7 * BYTE)) & MASK;
		fwrite(&byte, sizeof(char), 1, f1);
		sum <<= BYTE;
	}

	fclose(f1);

	return 0;
}