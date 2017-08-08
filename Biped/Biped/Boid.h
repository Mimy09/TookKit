#pragma once
#define _USE_MATH_DEFINES
#include "bpd\LinkedList.h"
#include "bpd\Maths.h"
#include <math.h>
#include <random>

class Boid {
public:
	bpd::Point position;
	bpd::Point velocity;
	bpd::Point acceleration;
	float r;
	float maxforce;
	float maxspeed;

	Boid(int x, int y);
	~Boid();

	void run();
	void applyForce(bpd::Point force);
	void flock(bpd::LinkedList<Boid> boids);
	void update();

private:

};