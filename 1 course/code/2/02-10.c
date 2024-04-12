#include <stdio.h>
#include <math.h>

int main(void) {
	int n;
	scanf("%d", &n);

	double s[n];
	for (int i = 0; i < n; i++) {
		scanf("%lf", &s[i]);
	}

	double a[n];
	for (int i = 0; i < n; i++) {
		scanf("%lf", &a[i]);
	}

	double f_speed[n];
	f_speed[0] = sqrt(s[0] * 2.0 * a[0]);
	for (int i = 1; i < n; i++) {
		f_speed[i] = sqrt(pow(f_speed[i - 1], 2.0) + 2.0 * s[i] * a[i]);
	}

	double t = sqrt(2.0 * s[0] / a[0]);
	for (int i = 1; i < n; i++) {
		t += (2.0 * s[i]) / (f_speed[i] + f_speed[i - 1]);
	}

	printf("%.4lf", t);

	return 0;
}