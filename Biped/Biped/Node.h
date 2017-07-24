#pragma once
#include "bpd\Maths.h"

struct Node {
public:
	Node(){}

	int f() { return h + g; }

private:
	bpd::Point* m_pos;
	bool open;
	int h, g;
};