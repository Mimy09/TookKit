#pragma once
#include "Boid.h"
#include "bpd\LinkedList.h"

class Flock {
public:
	bpd::LinkedList<Boid> boids;

	Flock();
	~Flock();
	void run();
	void addBoid(Boid b);

private:
};
