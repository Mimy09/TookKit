#include "Biped/bpd/Maths.h"
BPD_BEGIN
Point::Point() : x(0), y(0){}
Point::Point(const Point& Other){ x = Other.x; y = Other.y; }
Point::Point(float px, float py) : x(px), y(py){}

Point Point::sub(Point Other){ return Point(x - Other.x, y - Other.y); }
Point Point::add(Point Other){ return Point(x + Other.x, y + Other.y); }
Point Point::scale(float s){ return Point(x*s, y*s); }

Point Point::operator-(Point Other){ return sub(Other); }
Point Point::operator+(Point Other){ return add(Other); }
Point Point::operator*(float Scale){ return scale(Scale); }
bool Point::operator==(Point Other){ return x == Other.x ? y == Other.y ? true : false : false; }

float Point::distance(Point Other){ return sqrt((x - Other.x)*(x - Other.x) + (y - Other.y)*(y - Other.y)); }
Point Point::normal(){ return Point(x / sqrt(x*x + y*y), y / sqrt(x*x + y*y)); }


Segment::Segment() : x(0), y(0), vecX(0), vecY(0){}
Segment::Segment(float px, float py, float pvecX, float pvecY)
	: x(px), y(py), vecX(pvecX), vecY(pvecY){
}
Segment::Segment(const Segment& Other){
	x = Other.x; y = Other.y;
	vecX = Other.vecX; vecY = Other.vecY;
	int_x = int_y = 0;
}
Segment::~Segment(){}
float Segment::length(){ return sqrt(vecX * vecX + vecY * vecY); }
Segment Segment::normal(){ return Segment(y, x + vecX, (y + vecY) - y, x - (x + vecX)); }
Point Segment::center(){
	float _x = x + x + vecX, _y = y + y + vecY;
	_x /= 2; _y /= 2;
	return Point(_x, _y);
}
bool Segment::intersect(Segment seg){
	Point a(x, y), b(vecX, vecY), c(seg.x, seg.y), d(seg.vecX, seg.vecY);
	Point r = (b.sub(a));
	Point s = (d.sub(c));
	float k = r.x * s.y - r.y * s.x;
	float u = ((c.x - a.x) * r.y - (c.y - a.y) * r.x) / k;
	float t = ((c.x - a.x) * s.y - (c.y - a.y) * s.x) / k;
	return (0 <= u && u <= 1 && 0 <= t && t <= 1);
}
BPD_END