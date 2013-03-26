#include <sstream>

#include "Point.h"

using std::stringstream;

Point::Point()
{
	X = Y = 0;
}

Point::Point(const Point& p)
{
	X = p.X;
	Y = p.Y;
}

Point::Point(int x, int y)
{
	X = x;
	Y = y;
}

bool Point::operator==(const Point& pt) const
{
	return X == pt.X && Y == pt.Y;
}

Point& Point::operator=(const Point& p)
{
	X = p.X;
	Y = p.Y;
	return *this;
}

string Point::toStr() const
{
	stringstream out;
	out << "[" << X << "," << Y << "]";
	return out.str();
}