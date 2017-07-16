// ################################################################## //
// ##							OBJECT POOL						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Mar 21 - AIE			   ## //
// ################################################################## //
#pragma once
#include "Core\bpddef.h"
#include "LinkedList.h"

BPD_BEGIN
/* ---- OBJECT POOL ---- */
template<typename T> class ObjectPool {
public:
	/*---- CONSTRUCTOR ----
	Sets the pool to a empty Vector*/
	ObjectPool() {}

	/*---- GET OBJECT ----
	adds and returns a new object at end of the pool or
	if it exists in the pool all ready return the pointer
	to the object in the pool*/
	T* ReturnObject(T Object);
	/*---- GET OBJECT ----
	adds and returns a new object at end of the pool or
	if it exists in the pool all ready return the pointer
	to the object in the pool*/
	T* ReturnObjectIndex(int index);

	/*---- ADD OBJECT ----
	Adds a object to the end of the pool if it is not
	all ready in the pool*/
	void AddObject(T Object);

	/*---- REMOVE OBJECT ----
	Removes an object form the pool if it is in the pool*/
	void RemoveObejct(T Object);

private:
	/*---- POOL ----
	m_pool stores all the pooled data*/
	LinkedList< T > m_pool;

	/*---- CHECK OBJECT ----
	Returns the index of the object if it is in the pool*/
	int CheckObject(T Object);
};
BPD_END