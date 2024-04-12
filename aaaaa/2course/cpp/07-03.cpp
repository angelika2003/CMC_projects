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
#include <map>

using namespace std;


/*class Rectangle: public Figure {
	double a;
	double b;
public:
	double get_square()const {
		return a * b;
	}

	static Rectangle* make(const string& str) {
		Rectangle* ans = new Rectangle;


		stringstream stream;
		stream << str;
		double x, y;
		stream >> x >> y;

		ans->a = x;
		ans->b = y;

		return ans;
	}

	string to_string() const override {
		ostringstream a_str;
		a_str << a;
		ostringstream b_str;
		b_str << b;

		return "R " + a_str.str() +  " " + b_str.str();
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

	string to_string() const override {
		ostringstream a_str;
		a_str << a;
		return "S " + a_str.str();
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

	string to_string() const override {
		ostringstream r_str;
		r_str << r;
		return "C " + r_str.str();
	}
};*/


//класс-фабрика, синглтон
class Factory {
public:
	static Figure* factory_instance(string str) {
		stringstream stream;
		string type, x, y;

		stream << str;
		stream >> type;

		if (type == "R" ) {
			stream >> x >> y;
			return Rectangle::make(x + " " + y);
		} else if (type == "S") {
			stream >> x;
			return Square::make(x);
		} else if (type == "C") {
			stream >> x;
			return Circle::make(x);
		} else {
			return nullptr;
		}
	}
};

bool my_cmp(const Figure* f_1, const Figure* f_2) {
	return ((f_1->get_square()) < (f_2->get_square()));
}

int main() {
	vector<Figure*> v;
	string str;

	while (getline(cin, str)) {
		v.push_back(Factory::factory_instance(str));
	}

	stable_sort(v.begin(), v.end(), my_cmp);

	for (auto it = v.begin(); it != v.end(); it++) {
		cout << (*it)->to_string() << endl;
		delete *it;
	}
}