#include <iostream>
#include <iomanip>

#include <algorithm>
#include <map>
#include <string>
#include <cstring>
#include <set>

#include <iomanip>
#include <iostream>
#include <cstdio>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <set>
#include <functional>

#include "cmc_complex.h"
#include "cmc_complex_stack.h"
#include "cmc_complex_eval.h"

using numbers::complex;
using numbers::complex_stack;
using std::string;
using std::vector;
using std::map;
using std::function;
using std::cout;
using std::cin;
using std::endl;
using std::stod;
using std::stoi;

int main(int argc, char** argv) {
	complex c(argv[1]);
	double r = stod(argv[2]);
	int n = stoi(argv[3]);
	vector<string> args;
	for (int i = 4; i < argc; i++) {
		args.push_back(argv[i]);
	}

///////

	double delta = 2 * M_PI / n;
	complex c_delta(2 * M_PI / n, 0.0);
	complex sum(0.0, 0.0);

	double a = 0;
	double b = delta;
	double t = delta / 2;


	while (b <= 2 * M_PI) {
		complex z(r * cos(t) + c.re(), r * sin(t) + c.im());
		complex dt(-r * sin(t), r * cos(t));

		sum += (c_delta * eval(args, z) * dt);

		a += delta;
		b += delta;
		t += delta;
	}

	cout << sum.to_string() << endl;
}