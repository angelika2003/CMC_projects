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

/*Виртуальная функция — это функция-член, 
которую предполагается переопределить в производных классах. 
При ссылке на объект производного класса с помощью указателя 
или ссылки на базовый класс можно вызвать виртуальную функцию для этого объекта 
и выполнить версию функции производного класса.*/

using namespace std;

class Figure{
public:
	virtual double get_square()const{
		return 0;
	}

	virtual ~Figure() {
	}
};
