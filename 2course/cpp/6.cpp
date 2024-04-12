#include <iomanip>
#include <iostream>

using namespace std;

class point {
	double x;
	double y;
public:
	double get_x() const {
		return x;
	}

	double get_y() const {
		return y;
	}

	void print() const {
		cout << setprecision(6) << x << ' ' << y;
	}

	point(double a, double b) {
		x = a;
		y = b;
	}

	point &operator =(const point &p) {
		if (this == &p) {
			return *this;
		}
		x = p.x;
		y = p.y;

		return *this;
	}
};

class line {
	double k;
	double b;
	double c;
public:

	double get_k() const {
		return k;
	}

	double get_b() const {
		return b;
	}

	double get_c() const {
		return c;
	}

	line (point p1, point p2) {
		if (p1.get_x() == p2.get_x()) {
			b = 0;
			k = 1;
			c = -p1.get_x();
		} else {
			b = 1;
			k = -(p1.get_y() - p2.get_y()) / (p1.get_x() - p2.get_x());
			c = -p1.get_y() - k * p1.get_x();
		}
	}

	void cross(const line l) {
		if ((b == 0) && (l.get_b() == 0)) {
			if ((k == l.get_k()) && (c == l.get_c())) {
				cout << '2';
				return;
			}
			cout << '0';
			return;
		}

		if (b == 0) {
			cout << "1 ";
			point ans = point(-c / k, l.get_k() * (c / k) - l.get_c());
			ans.print();
			return;
		}

		if (l.get_b() == 0) {
			cout << "1 ";
			double x_c = -l.get_c() / l.get_k();

			point ans = point(x_c, -k * x_c - c);
			ans.print();
			return;
		}

		//b==1 and l.get_b()==1

		if (k == l.get_k()) {
			if (c == l.get_c()) {
				cout << '2';
				return;
			}
			cout << '0';
			return;
		}
		cout << "1 ";

		double x_cr = (l.get_c() - c) / (k - l.get_k());

		point ans = point(x_cr, -k * x_cr - c);
		ans.print();
		return;
	}
};


int main() {
	int x_1, y_1, x_2, y_2;
	cin >> x_1 >> y_1 >> x_2 >> y_2;
	int x_3, y_3, x_4, y_4;
	cin >> x_3 >> y_3 >> x_4 >> y_4;

	point p_1(x_1, y_1);
	point p_2(x_2, y_2);
	line l_1(p_1, p_2);

	point p_3(x_3, y_3);
	point p_4(x_4, y_4);
	line l_2(p_3, p_4);

	l_1.cross(l_2);

	return 0;
}

