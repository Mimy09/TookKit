#pragma once
#include "Boid.h"
#include "bpd\LinkedList.h"

class Flock {
public:
	//************************************
	// Public variables
	bpd::LinkedList<Boid> boids;
	//************************************

	//************************************
	// Constructor / De-Constructor
	Flock();
	~Flock();
	//************************************


	//************************************
	// Method:    run
	// FullName:  Flock::run
	// Access:    public 
	// Returns:   void
	// Parameter: ID2D1HwndRenderTarget * rt
	// Parameter: ID2D1SolidColorBrush * brush
	// Parameter: ID2D1SolidColorBrush * brush2
	// Parameter: int width
	// Parameter: int height
	// Def: Runs and Renders all the Boids in the Flock
	//************************************
	void run(ID2D1HwndRenderTarget* rt, ID2D1SolidColorBrush* brush, ID2D1SolidColorBrush* brush2, int width, int height);

	//************************************
	// Method:    addBoid
	// FullName:  Flock::addBoid
	// Access:    public 
	// Returns:   void
	// Parameter: Boid b
	// Def: Adds a Boid to the Flock
	//************************************
	void addBoid(Boid b);
	
	//************************************
	// Method:    addBoid2
	// FullName:  Flock::addBoid2
	// Access:    public 
	// Returns:   void
	// Parameter: Boid b
	// Parameter: bpd::LinkedList< AINode * > path
	// Def: Adds a A* Boid to the Flock
	//************************************
	void addBoid2(Boid b, bpd::LinkedList< AINode* > path);

	//************************************
	// Method:    deleteBoid2
	// FullName:  Flock::deleteBoid2
	// Access:    public 
	// Returns:   void
	// Def: Deletes the A* Boids
	//************************************
	void deleteBoid2();
};
