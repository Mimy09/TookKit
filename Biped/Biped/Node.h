#pragma once
#include "bpd\Maths.h"
#include "bpd\LinkedList.h"

struct Edge;
struct AINode {
public:
	AINode(bpd::Point p): g(10), m_pos(p) {}
	AINode() : g(10), m_pos(NULL) {}

	int f() { return h + g; }
	enum Type {
		OPEN, CLOSED, NUL = 2
	}; Type type = Type::NUL;

	enum  Type2 {
		START, END
	}; Type2 type2;

	bool operator==(AINode & other) { return GetPos() == other.GetPos(); }

	AINode& GetParent() { return *m_parent; }
	void SetParent(AINode* parent) { m_parent = parent; }


	void SetPos(bpd::Point p) { m_pos = p; }
	bpd::Point& GetPos() { return m_pos; }

	bpd::LinkedList< Edge > m_edges;
	int h, g;
private:
	AINode* m_parent;
	bpd::Point m_pos;
};

struct Edge {
	Edge(AINode& n1, AINode& n2) : Point1(&n1), Point2(&n2){}
	Edge() : Point1(nullptr), Point2(nullptr) {}
	AINode* Point1 = nullptr, *Point2 = nullptr;
};
