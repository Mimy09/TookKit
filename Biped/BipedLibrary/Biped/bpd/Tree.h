// ################################################################## //
// ##							   TREE    						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 June 21 - AIE		   ## //
// ################################################################## //
#pragma once
#include "core/bpddef.h"

BPD_BEGIN
/* ---- TREE ---- */
template<typename T> class Tree {
public:
	/* ---- NODE ----
	Node struct to hold the value and
	a pointer to the next element*/
	struct Node {
		Node() : node_left(nullptr), node_right(nullptr){}
		Node(T Value, Node* Right, Node* Left) : node_left(Left), node_right(Right), data(Value){}
		T data;
		int level = 0;
		Node *node_left, *node_right;
		void operator=(const Node & n);
	}; 
	/* DEFAULT CONSTRUCTOR */
	Tree();
	/* DEFAULT EDCONSTRUCTOR */
	~Tree() { }

	/* ---- SEARCH ----
	Serches through the Tree for the value
	#param Value - The value that is being searched for
	#return Node* - Pointer to the node that was found*/
	Node *Search(const T Value);
	/* ---- INSERT ----
	Adds a new node with the value passed in
	#param Value - The value that will be added*/
	void Insert(const T Value);
	/* ---- DELETE ----
	Deletes the whole Tree*/
	void Delete();
	/* ---- DELETE NODE ----
	Deletes a node withibn the Tree
	#param Value - The value that will be deleted out of the Tree*/
	void DeleteNode(T Value);
	/* ---- ROOT ----
	Returns the root of the Tree*/
	Node * Root();
private:
	// Stores the root of the tree
	Node* m_root;
	// Null node used to check for empty node
	Node* NULL_NODE;

	void DeleteTree(Node * leaf);
	void DeleteNode(T Value, Node * & n);
	void Insert(T Value, Node * & leaf);
	Node * Search(T Value, Node * leaf);
	void RotateWithRightChild(Node * & n) const;
	void RotateWithLeftChild(Node * & n2) const;
	void Skew(Node * & n) const;
	void Split(Node * & n) const;
};
BPD_END