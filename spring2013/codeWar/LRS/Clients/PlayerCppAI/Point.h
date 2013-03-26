#ifndef POINT_MOCK_H
#define POINT_MOCK_H

#include <string>
#include "pugixml.hpp"

using pugi::xml_node;
using std::string;

class Point
{
public:
	Point();
	Point(const Point& p);
	Point(int x, int y);

	bool operator==(const Point& pt) const;

	Point& operator=(const Point& p);
	
	string toStr() const;

	int X;
	int Y;
};

#endif