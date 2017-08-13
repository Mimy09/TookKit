#include "Boid.h"

Boid::Boid(int x, int y) {
	acceleration = bpd::Point(0, 0);

	srand(time(0));
	float angle = (((float)rand()) / (float)RAND_MAX) * M_PI_2;
	velocity = bpd::Point(cos(angle), sin(angle));

	position = bpd::Point(x, y);
	r = 2;
	maxspeed = 2;
	maxforce = 0.1;
	followASTAR = false;
}

Boid::Boid(const Boid &) { }
Boid::Boid() { followASTAR = false; }
Boid::~Boid() {}

void Boid::run(bpd::LinkedList<Boid> boids, ID2D1HwndRenderTarget* rt, ID2D1SolidColorBrush* brush, ID2D1SolidColorBrush* brush2, int width, int height) {
	this->height = height;
	this->width = width;
	flock(boids);
	update();
	render(rt, brush, brush2);
	borders();
}

void Boid::deleteNode2() {
	m_path.clear();
	m_currentNode = 0;
	dir = false;
	followASTAR = false;
}

void Boid::applyForce(bpd::Point force) {
	acceleration = acceleration.add(force);
}

void Boid::flock(bpd::LinkedList<Boid> boids) {
	if(!followASTAR) {
		bpd::Point sep = separate(boids);
		bpd::Point ali = align(boids);
		bpd::Point coh = cohesion(boids);

		sep = sep.mult(0.5);
		ali = ali.mult(0.1);
		coh = coh.mult(0.1);

		applyForce(sep);
		applyForce(ali);
		applyForce(coh);
	} else {
		if(m_path.size() <= 0) {
			followASTAR = false;
		} else {
			if(position.distance(m_path[m_currentNode]->GetPos()) < 10) {
				if (dir) m_currentNode--; else m_currentNode++;
				if(m_currentNode < 0) {
					m_currentNode++;
					dir = !dir;
				}
				if(m_currentNode >= m_path.size()) {
					m_currentNode--;
					dir = !dir;
				}
			} applyForce(seek(m_path[m_currentNode]->GetPos()));
		}
	}
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

void Boid::render(ID2D1HwndRenderTarget* rt, ID2D1SolidColorBrush* brush, ID2D1SolidColorBrush* brush2){
	float theta = velocity.dot(bpd::Point(0, 1)) + (M_PI / 2);
	if(!followASTAR) {
		rt->DrawLine(
			D2D1::Point2F(position.x, position.y),
			D2D1::Point2F(position.x, position.y + 10),
			brush, 10, 0);
	} else {
		rt->DrawLine(
			D2D1::Point2F(position.x, position.y),
			D2D1::Point2F(position.x, position.y + 15),
			brush2, 15, 0);
	}
}

void Boid::borders() {
	//if (position.x < -r) position.x = 1920 + r;
	//if (position.y < -r) position.y = 1080 + r;
	//if (position.x > 1920 + r) position.x = -r;
	//if (position.y > 1080 + r) position.y = -r;
	if(position.x < -r) position.x = width + r;
	if(position.y < -r) position.y = height + r;
	if(position.x > width + r) position.x = -r;
	if(position.y > height + r) position.y = -r;
}

bpd::Point Boid::separate(bpd::LinkedList<Boid> boids) {
	float desiredseparation = 25.0f;
	bpd::Point steer = bpd::Point(0, 0);
	int count = 0;

	for (int i = 0; i < boids.size(); i++) {
		float d = position.distance(boids[i].position);
		if((d > 0) && (d < desiredseparation)) {
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
		if(boids[i].followASTAR) {
			if((d > 0) && (d < (neighbordist * 2))) {
				sum = sum.add(boids[i].velocity);
				count++;
			}
		} else {
			if((d > 0) && (d < neighbordist)) {
				sum = sum.add(boids[i].velocity);
				count++;
			}
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
		if(boids[i].followASTAR) {
			if((d > 0) && (d < (neighbordist * 2))) {
				sum = sum.add(boids[i].position);
				count++;
			}
		} else {
			if((d > 0) && (d < neighbordist)) {
				sum = sum.add(boids[i].position);
				count++;
			}
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