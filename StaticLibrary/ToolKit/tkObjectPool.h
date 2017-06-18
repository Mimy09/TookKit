// ################################################################## //
// ##							OBJECT POOL						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Mar 21 - AIE			   ## //
// ################################################################## //
#pragma once
#include "tkLinkList.h"

namespace tk {
	template<typename T>
	class ObjectPool {
	public:
		// ---- CONSTRUCTOR ----
		// Sets the pool to a empty Vector
		ObjectPool() {
			//m_pool = {};
		}

		// ---- GET OBJECT ----
		// adds and returns a new object at end of the pool or
		// if it exists in the pool all ready return the pointer
		// to the object in the pool
		T* ReturnObject(T Object) {
			int id = CheckObject(Object);
			if (id == -1) {
				AddObject(Object);
				return &m_pool.Find(CheckObject(Object));
			} else { return &m_pool.Find(id); }
		}
		// ---- GET OBJECT ----
		// adds and returns a new object at end of the pool or
		// if it exists in the pool all ready return the pointer
		// to the object in the pool
		T* ReturnObject(int index) {
			return &m_pool.Find(index);
		}

		// ---- ADD OBJECT ----
		// Adds a object to the end of the pool if it is not
		// all ready in the pool
		void AddObject(T Object) {
			if (CheckObject(Object) == -1) {
				m_pool.InsertEnd(Object);
			}
		}

		// ---- REMOVE OBJECT ----
		// Removes an object form the pool if it is in the pool
		void RemoveObejct(T Object) {
			int id = CheckObject(Object);
			if (id != -1) {
				//m_pool.erase(std::find( m_pool.begin(), m_pool.end(), Object));
				m_pool.DeletePos(id);
			}
		}

	private:
		// ---- POOL ----
		// m_pool stores all the pooled data
		tk::LinkList< T > m_pool;

		// ---- CHECK OBJECT ----
		// Returns the index of the object if it is in the pool
		int CheckObject(T Object) {
			for (int i = 0; i < m_pool.Length(); i++) {
				if (m_pool.Find(i) == Object) return i;
			} return -1;
		}
	};
}