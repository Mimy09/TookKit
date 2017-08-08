#include "Boid.h"

Boid::Boid(int x, int y) {
	acceleration = bpd::Point(0, 0);

	srand(0);
	float angle = (((float)rand()) / (float)RAND_MAX) * M_PI_2;
	velocity = bpd::Point(cos(angle), sin(angle));

	position = bpd::Point(x, y);
	r = 2;
	maxspeed = 2;
	maxforce = 0.03;
}

Boid::~Boid() {
}

void Boid::run() {
	
}
