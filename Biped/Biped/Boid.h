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
	Boid(const Boid&);
	Boid();
	~Boid();

	bpd::Point separate(bpd::LinkedList<Boid> boids);
	bpd::Point cohesion(bpd::LinkedList<Boid> boids);
	bpd::Point align(bpd::LinkedList<Boid> boids);
	bpd::Point seek(bpd::Point target);
	void flock(bpd::LinkedList<Boid> boids);
	void applyForce(bpd::Point force);


	void borders();
	void update();
	float theta();
	void run(bpd::LinkedList<Boid> boids);


private:

};