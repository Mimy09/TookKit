#pragma once
#include "Core/bpddef.h"
#include <math.h>

BPD_BEGIN
class Point{
public:
	float x, y;
	Point();
	Point(float);
	Point(const Point& Other);
	Point(float px, float py);
	Point sub(Point Other);
	Point add(Point Other);
	Point scale(float s);
	Point operator-(Point Other);
	Point operator+(Point Other);
	Point operator*(float Scale);
	bool operator==(Point Other);
	float distance(Point Other);
	Point normal();
};

class Segment{
public:
	float x, y, vecX, vecY;
	int int_x = 0, int_y = 0;

	Segment();
	Segment(float px, float py, float pvecX, float pvecY);
	Segment(const Segment& Other);
	~Segment();
	
	float length();
	Segment normal();
	Point center();
	bool intersect(Segment seg);
};
BPD_END