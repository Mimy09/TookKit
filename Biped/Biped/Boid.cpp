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

Boid::Boid(const Boid &) {}
Boid::Boid() {}
Boid::~Boid() {}

void Boid::run(bpd::LinkedList<Boid> boids) {
	flock(boids);
	update();
	borders();
}

void Boid::applyForce(bpd::Point force) {
	acceleration.add(force);
}

void Boid::flock(bpd::LinkedList<Boid> boids) {
	bpd::Point sep = separate(boids);
	bpd::Point ali = align(boids);
	bpd::Point coh = cohesion(boids);

	sep = sep.mult(1.5);
	ali = ali.mult(1.0);
	coh = coh.mult(1.0);

	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}

void Boid::update() {
	velocity = velocity.add(acceleration);
	velocity.limit(maxspeed);
	position = position.add(velocity);
	acceleration = acceleration.mult(0);
}

bpd::Point Boid::seek(bpd::Point target) {
	bpd::Point desired = target - position;

	desired = desired.normal();
	desired = desired.mult(maxspeed);

	bpd::Point steer = desired - velocity;
	steer.limit(maxforce);
	return steer;
}

float Boid::theta() {
	return velocity.dot(bpd::Point(0, 1)) + (M_PI / 2);
}

void Boid::borders() {
	if (position.x < -r) position.x = 800 + r;
	if (position.y < -r) position.y = 600 + r;
	if (position.x > 800 + r) position.x = -r;
	if (position.y > 600 + r) position.y = -r;
}

bpd::Point Boid::separate(bpd::LinkedList<Boid> boids) {
	float desiredseparation = 25.0f;
	bpd::Point steer = bpd::Point(0, 0);
	int count = 0;

	for (int i = 0; i < boids.size(); i++) {
		float d = position.distance(boids[i].position);
		if ((d > 0) && (d < desiredseparation)) {
			bpd::Point diff = position - boids[i].position;
			diff = diff.normal();
			diff = diff.div(d);
			steer = steer.add(diff);
			count++;
		}
	}
	if (count > 0) { steer = steer.div((float)count); }

	if (steer.mag() > 0) {
		steer = steer.normal();
		steer = steer.mult(maxspeed);
		steer = steer.sub(velocity);
		steer.limit(maxforce);
	}
	return steer;
}

bpd::Point Boid::align(bpd::LinkedList<Boid> boids) {
	float neighbordist = 50;
	bpd::Point sum = bpd::Point(0, 0);
	int count = 0;

	for (int i = 0; i < boids.size(); i++) {
		float d = position.distance(boids[i].position);
		if ((d > 0) && (d < neighbordist)) {
			sum = sum.add(boids[i].velocity);
			count++;
		}
	}
	if (count > 0) {
		sum = sum.div((float)count);
		sum = sum.normal();
		sum = sum.mult(maxspeed);
		bpd::Point steer = sum - velocity;
		steer.limit(maxforce);
		return steer;
	} else { return bpd::Point (0, 0); }
}

bpd::Point Boid::cohesion(bpd::LinkedList<Boid> boids) {
	float neighbordist = 50;
	bpd::Point sum = bpd::Point(0, 0);
	int count = 0;
	for (int i = 0; i < boids.size(); i++) {
		float d = position.distance(boids[i].position);
		if ((d > 0) && (d < neighbordist)) {
			sum = sum.add(boids[i].position);
			count++;
		}
	}
	if (count > 0) {
		sum = sum.div(count);
		return seek(sum); 
	}
	else {
		return bpd::Point(0, 0);
	}

}