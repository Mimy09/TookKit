#pragma once

namespace tk {
	namespace std {
		template<typename T>
		class Tree {
		public:
			struct Node {
				Node() 
					: node_left(nullptr), node_right(nullptr){}
				Node(T Value, Node Right, Node Left)
					: node_left(Left), node_right(Right), data(Value){}
				T data;
				int level = 0;
				Node * node_left, *node_right;
				void operator=(const Node & n) {
					data = n.data;
					level = n.level;
					node_left = n.node_left;
					node_right = n.node_right;
				}
			}; 
			Tree() {
				NULL_NODE = new Node();
				NULL_NODE->node_left = NULL_NODE->node_right = NULL_NODE;
				NULL_NODE->level = 0;
				m_root = NULL_NODE;
			}
			~Tree() { if (m_root) { delete m_root; m_root = nullptr; } }
			Node *Search(const T Value) { return Search(Value, m_root); }
			void Insert(const T Value) {
				Insert(Value, m_root);
			}
			void Delete() { DeleteTree(m_root); }
			void DeleteNode(T Value) { DeleteNode(Value, m_root); }
			Node * Root() {}
		private:
			Node* m_root;
			Node* NULL_NODE;

			void DeleteTree(Node * leaf) {
				if (leaf != nullptr) {
					DeleteTree(leaf->node_left);
					DeleteTree(leaf->node_right);
					delete leaf;
				}
			}
			void DeleteNode(T Value, Node * & n) {
				static Node * lastNode, * deletedNode = NULL_NODE;
				if (n != NULL_NODE) {
					lastNode = n;
					if (Value < n->data) {
						DeleteNode(Value, n->node_left);
					}
					else {
						deletedNode = n;
						DeleteNode(Value, n->node_right);
					}

					if (n == lastNode) {
						if (deletedNode == NULL_NODE || Value != deletedNode->data) return;
						deletedNode->data = n->data;
						deletedNode = NULL_NODE;
						n = n->node_right;
						delete lastNode;
					}
					else {
						if (n->node_left->level < n->level - 1 ||
							n->node_right->level < n->level - 1) {
							if (n->node_right->level > --n->level)
								n->node_right->level = n->level;
							Skew(n);
							Skew(n->node_right);
							Skew(n->node_right->node_right);
							Split(n);
							Split(n->node_right);
						}
					}
				}

			}
			void Insert(T Value, Node * & leaf) {
				if (leaf == NULL_NODE) {
					leaf = new Node;
					leaf->data = Value;
					leaf->node_left = NULL_NODE;
					leaf->node_right = NULL_NODE;
				} else if (Value < leaf->data) {
					Insert(Value, leaf->node_left);
				}
				else {
					Insert(Value, leaf->node_right);
				}
				Skew(leaf);
				Split(leaf);
			}
			Node * Search(T Value, Node * leaf) {
				if (leaf != NULL_NODE) {
					if (Value == leaf->data) return leaf;
					if (Value < leaf->data) return Search(Value, leaf->node_left);
					else return Search(Value, leaf->node_right);
				} else return nullptr;
			}

			void RotateWithRightChild(Node * & n) const {
				Node * n2 = n->node_right;
				n->node_right = n2->node_left;
				n2->node_left = n;
				n = n2;
			}
			void RotateWithLeftChild(Node * & n2) const {
				Node * n = n2->node_left;
				n2->node_left = n->node_right;
				n->node_right = n2;
				n2 = n;
			}
			void Skew(Node * & n) const {
				if (n->node_left->level == n->level)
					RotateWithLeftChild(n);
			}
			void Split(Node * & n) const {
				if (n->node_right->node_right->level == n->level) {
					RotateWithRightChild(n);
					n->level++;
				}
			}
		};
	}
}