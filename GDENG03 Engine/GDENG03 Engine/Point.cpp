#include"Point.h"

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(int abscissa, int ordinate) {
	x = abscissa;
	y = ordinate;
}

Point::Point(const Point* point) {
	x = point->x;
	y = point->y;
}

int Point::getX() const {
	return x;
}

int Point::getY() const {
	return y;
}