// ################################################################## //
// ##							HASH MAP   						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 June 23 - AIE		   ## //
// ################################################################## //
#pragma once
// INCLUDES
#include "Core\bpddef.h"
#include "String.h"
#include "Exception.h"

// DEFINES
#define BPD_HASH(_cp) tk::std::hash(_cp, TK_SIZEOF(_cp))

BPD_BEGIN
/* ---- HASH TABLE ---- */
template <typename T > class HashTable {
public:
	/* CONSTRUCTOR */
	HashTable(const int size);
	/* DEFAULT CONSTRUCTOR */
	HashTable();
	/* DEFAULT DECONSTRUCTOR */
	~HashTable();

	/* ---- SIZE ---- */
	inline int Size() { return m_size; }
	/* ---- SET SIZE ---- */
	void SetSize(const int size);
	/* ---- ADD ----
	Adds a map to the hash map
	#param key - The key used to access the value in the future
	#param value - The value that will be assigned to the key*/
	u_int add(char * key, T* value);
	/* ---- ADD ----
	Adds a map to the hash map
	#param key - The key used to access the value in the future
	#param value - The value that will be assigned to the key*/
	u_int add(char * key, T value);
	/* ---- REMOVE ----
	Deletes a map
	#param key - The key for the value that will be deleted*/
	bool remove(char * key);
	/* ---- GET ----
	Returns the value assigned to the key
	#param key - The key used to get the value
	#return T* - The a ponier to value assigned to the key*/
	T* get(char * key);
	/* ---- GET ----
	Returns the value assigned to the key
	#param key - The key used to get the value
	#return T* - The a ponier to value assigned to the key*/
	T* get(u_int key);
	/* ---- CLEAR ----
	Clears everything in the HashTable*/
	void clear();

	/* ---- HASH ----
	Gets the hash of the key
	#param key - the key for the hash
	#return u_int - the hash for the key*/
	u_int hash(char * key);
	/* ---- HASH ----
	Gets the hash of the key
	#param key - the key for the hash
	#param key - size of the key
	#return u_int - the hash for the key*/
	u_int hash(char * key, int size, u_int seed = 0x811C9DC5);

private:
	u_int fnv1a(unsigned char oneByte, u_int hash);

private:
	/* ---- PRIVATE VARIABLES ---- */
	// stores the hashes
	u_int* m_hash;
	// stores pointers to the values
	T** m_values;
	// stores the size of the hash table
	int m_size;
	/* ---- CONST VARIABLES ---- */
	const u_int m_prime = 0x01000193;
};

static u_int hash(char * key, int size, const u_int seed = 0x811C9DC5) {
	u_int hash = seed;
	while (*key)
		hash = ((unsigned char)*key++ ^ hash) * 0x01000193;
	return hash;
}
BPD_END