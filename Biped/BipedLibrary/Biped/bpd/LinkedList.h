// ################################################################## //
// ##							LINKED LIST						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 June 21 - AIE		   ## //
// ################################################################## //
#pragma once
#include "Core\bpddef.h"
#include "String.h"
#include "Exception.h"

BPD_BEGIN
/* ---- LINKED LIST ---- */
template<typename T> class LinkedList {
private:
	/* ---- NODE ----
	Node struct to hold the value and
	a pointer to the next element*/
	struct Node{
		T value; Node *next;
		bool operator==(const Node& other) const;
		Node& operator+(const int value);
	};
	Node *m_head, *m_tail;
public:
	/* DEFAULT CONSTRUCTOR */
	LinkedList()
		: m_size(0), m_head(nullptr), m_tail(nullptr) {
	}
	/* DEFAULT DECONSTRUCTOR */
	~LinkedList() {}

	/* ---- BEGIN ----
	Gets a pointer to the start of the linked list
	#return T* - Pointer to the start of the linked list*/
	Node* begin() const;
	/* ---- END ----
	Gets a pointer to the end of the linked list
	#return T* - Pointer to the end of the linked list*/
	Node* end() const;
	/* ---- FRONT ----
	Gets a reference to the start of the linked list
	#return T* - Reference to the start of the linked list*/
	Node& front();
	/* ---- BACK ----
	Gets a reference to the end of the linked list
	#return T* - Reference to the end of the linked list*/
	Node& back();

	/* ---- OPERATOR[] ----
	Returns the value found at the index
	#return T& - reference to the value found*/
	T& operator[](const size_type index) const;
	/* ---- FIND ----
	Returns the value found at the index
	#param index - The position in the linked list
	#return T& - reference to the value found*/
	T& find(const size_type index) const;

	/* ---- FIND ----
	Returns the Node at the given position
	#param index - The position in the linked list
	#return T& - reference to the value found*/
	int find_n(Node node) const;
	/* ---- FIND ----
	Returns the Node at the given position
	#param index - The position in the linked list
	#return T& - reference to the value found*/
	int find_i(T value) const;
	/* ---- OPERATOR= ----
	Copies the valuse across*/
	void operator=(LinkedList& other);

	/* ---- SIZE ----
	Gets the size of the linked list
	#return int - Returns the size*/
	int size() const;
	/* ---- EMPTY ----
	Checks if the linked list is empty
	#return bool - true if list is empty*/
	bool empty();

	/* ---- CLEAR ----
	Clears the linked list*/
	void clear();
	/* ---- INSERT ----
	Creates a node at the given position in the linked list
	#param pos - The postion in the linked list where the value will be placed
	#param value - The value that will be put into the linked list*/
	void insert(const int pos, const T& value);
	/* ---- INSERT ----
	Creates a node at the given position in the linked list
	#param pos - The postion in the linked list where the value will be placed
	#param value - The value that will be put into the linked list*/
	void insert(Node& node, const T& value);
	/* ---- ERASE ----
	Deletes a node at a given position
	#param pos - The position that will be deleted in the linked list*/
	void erase(const int pos);
	/* ---- PUSH BACK ----
	Pushes a new value onto the end of the linked list
	#param value - The value that will be pushed*/
	void push_back(const T& value);
	/* ---- POP BACK ----
	Deletes the last value in the linked list*/
	void pop_back();

private:
	// Stores the size of the linked list
	int m_size;
};
BPD_END