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
#include <cassert>


using namespace std;

//двухмерная фигура
class Figure {
public:
	/*Класс должен определять метод equals для перекрытия в производных классах.
	Метод будет принимать указатель на фигуру и возвращать true, если фигуры равны.*/
	virtual bool equals(const Figure* f)const = 0;

	virtual ~Figure() {
	}
};

class Rectangle: public Figure {
	int a;
	int b;
public:


	Rectangle(int x = 0, int y = 0) : a(x), b(y) {};

	bool equals(const Figure* f)const {

		const Rectangle* r2 = dynamic_cast<const Rectangle*>(f);
		
		if ((r2) && (this->a == r2->a) && (this->b == r2->b)) {
			return true;
		}

		return false;
	}

};

class Triangle: public Figure {
	int a;
	int b;
	int c;
public:

	Triangle(int x = 0, int y = 0, int z = 0) : a(x), b(y), c(z) {};

	bool equals(const Figure* f)const  {

		
		const Triangle* r2 = dynamic_cast<const Triangle*>(f);
		if ((r2) && (this->a == r2->a) && (this->b == r2->b) && (this->c == r2->c)) {
			return true;
		}
		return false;
	}

};

/*int main() {
	Rectangle r1(10, 5), r2(10, 2), r3(10, 5), r4(5, 10);
	Triangle t1(1, 2, 3);
	Figure *f = &r1;

	cout << f->equals(&r1);
}*/

