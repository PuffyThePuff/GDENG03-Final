#pragma once

class Point
{
public:
	Point();
	Point(int abscissa, int ordinate);
	Point(const Point* point);
	~Point() {}

	int getX() const;
	int getY() const;

private:
	int x;
	int y;
};