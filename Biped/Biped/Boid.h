#pragma once
#define _USE_MATH_DEFINES
#include "bpd/bpdWindow.h"
#include "bpd/LinkedList.h"
#include "bpd/Maths.h"
#include "Node.h"
#include <math.h>
#include <random>
#include <ctime>

class Boid {
public:
	//************************************
	// Public variables
	bpd::Point position;
	bpd::Point velocity;
	bpd::Point acceleration;
	float r;
	float maxforce;
	float maxspeed;
	bool followASTAR, dir;
	//************************************

	//************************************
	// Constructor / De-Constructor
	Boid(int x, int y);
	Boid(const Boid&);
	Boid();
	~Boid();
	//************************************


	//************************************
	// Method:    separate
	// FullName:  Boid::separate
	// Access:    public 
	// Returns:   bpd::Point
	// Parameter: bpd::LinkedList<Boid> boids
	// Def: Separation position for Boid
	//************************************
	bpd::Point separate(bpd::LinkedList<Boid> boids);

	//************************************
	// Method:    cohesion
	// FullName:  Boid::cohesion
	// Access:    public 
	// Returns:   bpd::Point
	// Parameter: bpd::LinkedList<Boid> boids
	// Def: cohesion position for Boid
	//************************************
	bpd::Point cohesion(bpd::LinkedList<Boid> boids);

	//************************************
	// Method:    align
	// FullName:  Boid::align
	// Access:    public 
	// Returns:   bpd::Point
	// Parameter: bpd::LinkedList<Boid> boids
	// Def: alignment position for Boid
	//************************************
	bpd::Point align(bpd::LinkedList<Boid> boids);

	//************************************
	// Method:    seek
	// FullName:  Boid::seek
	// Access:    public 
	// Returns:   bpd::Point
	// Parameter: bpd::Point target
	// Def: Seeks to the position
	//************************************
	bpd::Point seek(bpd::Point target);

	//************************************
	// Method:    flock
	// FullName:  Boid::flock
	// Access:    public 
	// Returns:   void
	// Parameter: bpd::LinkedList<Boid> boids
	//************************************
	void flock(bpd::LinkedList<Boid> boids);

	//************************************
	// Method:    applyForce
	// FullName:  Boid::applyForce
	// Access:    public 
	// Returns:   void
	// Parameter: bpd::Point force
	// Def: Applies the force to the Boid
	//************************************
	void applyForce(bpd::Point force);

	
	//************************************
	// Method:    setPath
	// FullName:  Boid::setPath
	// Access:    public 
	// Returns:   void
	// Parameter: bpd::LinkedList< AINode * > path
	// Def: Sets the path of the Boid
	//************************************
	inline void setPath(bpd::LinkedList< AINode* > path) { m_path = path; m_currentNode = m_path.size() - 1; }

	
	//************************************
	// Method:    borders
	// FullName:  Boid::borders
	// Access:    public 
	// Returns:   void
	// Def: Makes the Boid stay within the screen
	//************************************
	void borders();

	//************************************
	// Method:    update
	// FullName:  Boid::update
	// Access:    public 
	// Returns:   void
	// Def: Updates the Boid
	//************************************
	void update();
	
	//************************************
	// Method:    render
	// FullName:  Boid::render
	// Access:    public 
	// Returns:   void
	// Parameter: ID2D1HwndRenderTarget * rt
	// Parameter: ID2D1SolidColorBrush * brush
	// Parameter: ID2D1SolidColorBrush * brush2
	// Def: Renders the Boid
	//************************************
	void render(ID2D1HwndRenderTarget* rt, ID2D1SolidColorBrush* brush, ID2D1SolidColorBrush* brush2);

	//************************************
	// Method:    run
	// FullName:  Boid::run
	// Access:    public 
	// Returns:   void
	// Parameter: bpd::LinkedList<Boid> boids
	// Parameter: ID2D1HwndRenderTarget * rt
	// Parameter: ID2D1SolidColorBrush * brush
	// Parameter: ID2D1SolidColorBrush * brush2
	// Parameter: int width
	// Parameter: int height
	// Def: Runs the Boid
	//************************************
	void run(bpd::LinkedList<Boid> boids, ID2D1HwndRenderTarget* rt, ID2D1SolidColorBrush* brush, ID2D1SolidColorBrush* brush2, int width, int height);


	//************************************
	// Method:    deleteNode2
	// FullName:  Boid::deleteNode2
	// Access:    public 
	// Returns:   void
	// Def: Deletes the Boid
	//************************************
	void deleteNode2();
private:
	//************************************
	// Private variables
	bpd::LinkedList< AINode* > m_path;
	int m_currentNode;
	int width, height;
	//************************************
};