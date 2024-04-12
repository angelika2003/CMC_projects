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

namespace Game {
template <typename T>//T - тип координат
class Coord {
public:
	typedef T value_type;

	T row;
	T col;

	Coord(T x = value_type(), T y = value_type()): row(x), col(y) {}
};

template <typename T>//T - Coord
typename T::value_type dist(const T& size, const T& start, const T& end) {
	typename T::value_type dif_x = start.col  - end.col;
	typename T::value_type dif_y= start.col / 2 - end.col / 2 + start.row - end.row;


	if (((dif_x >= 0) && (dif_y >= 0)) || ((dif_x < 0) && (dif_y < 0))) {
		return max(abs(dif_x), abs(dif_y));
	}

	return abs(dif_x)  + abs(dif_y);

}

}
