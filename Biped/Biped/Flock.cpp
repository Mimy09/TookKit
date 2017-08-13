#include "Flock.h"

Flock::Flock() {}

Flock::~Flock() {
}

void Flock::run(ID2D1HwndRenderTarget* rt, ID2D1SolidColorBrush* brush, ID2D1SolidColorBrush* brush2, int width, int height) {
	for (int i = 0; i < boids.size(); i++) {
		boids[i].run(boids, rt, brush, brush2, width, height);
	}
}

void Flock::addBoid(Boid b) {
	boids.push_back(b);
}
void Flock::addBoid2(Boid b, bpd::LinkedList< AINode* > path){
	b.followASTAR = true;
	b.setPath(path);
	boids.push_back(b);
}

void Flock::deleteBoid2() {
	for(int i = 0; i < boids.size(); i++) {
		boids[i].deleteNode2();
		if(boids[i].followASTAR == true) {
			boids.erase(i); deleteBoid2();
		}
	}
}
