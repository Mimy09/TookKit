#pragma once
#include "bpd\Maths.h"
#include "bpd\LinkedList.h"

struct Edge;
struct AINode {
public:
	AINode(bpd::Point p): g(10), m_pos(p), open(-1){}
	AINode() : g(10), m_pos(NULL), open(-1) {}
	int f() { return h + g; }

	bool IsOpen() { return open; }
	void Open() { open = 1; }
	void Close() { open = 0; }

	bool operator==(AINode & other) { return GetPos() == other.GetPos(); }

	void SetPos(bpd::Point p) { m_pos = p; }
	bpd::Point& GetPos() { return m_pos; }

	bpd::LinkedList< Edge > m_edges;
private:
	bpd::Point m_pos;
	int open, h, g;
};

struct Edge {
	Edge(AINode& n1, AINode& n2) : Point1(&n1), Point2(&n2){}
	Edge() : Point1(nullptr), Point2(nullptr) {}
	AINode* Point1 = nullptr, *Point2 = nullptr;
};
