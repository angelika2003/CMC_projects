#include <cstdio>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <list>
#include <cmath>
#include <string>

/*Ключевое слово override можно использовать для обозначения функций-членов, 
которые переопределяют виртуальную функцию в базовом классе.
*/

using namespace std;

class Rectangle: public Figure {
	double a;
	double b;
public:
	double get_square()const {
		return a * b;
	}

	static Rectangle* make(const string& str) {
		Rectangle* ans = new Rectangle;

/*		int i = 0;
		while (str[i] != ' ') {
			i++;
		}

		string str1 = str.substr(0, i);
		string str2 = str.substr(i + 1, 30);

		double x = stod(str1);
		double y = stod(str2);*/

        stringstream stream;
        stream << str;
        double x, y;
        stream >> x >> y;

		ans->a = x;
		ans->b = y;

		return ans;
	}
};

class Square: public Figure {
	double a;
public:
	double get_square()const {
		return a * a;
	}

	static Square* make(const string& str) {
		Square* ans = new Square;
		double x = stod(str);
		ans->a = x;

		return ans;
	}

};

class Circle: public Figure {
	double r;
public:
	double get_square()const {
		return r * r * M_PI;
	}

	static Circle* make(const string& str) {
		Circle* ans = new Circle;
		double x = stod(str);
		ans->r = x;

		return ans;
	}

};