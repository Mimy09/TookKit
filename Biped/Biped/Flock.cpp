#include "Flock.h"

Flock::Flock() {}

Flock::~Flock() {
}

void Flock::run() {
	for (int i = 0; i < boids.size(); i++) {
		boids[i].run(boids);
	}
}

void Flock::addBoid(Boid b) {
	boids.push_back(b);
}
