#include "Biped\bpd\Tree.h"
BPD_BEGIN
BPD_TEMPLATE_CLASS void Tree<BPD_TEMPLATE_TYPE>::Node::operator=(const Node & n){
	data = n.data;
	level = n.level;
	node_left = n.node_left;
	node_right = n.node_right;
}
BPD_TEMPLATE_CLASS Tree<BPD_TEMPLATE_TYPE>::Tree(){
	NULL_NODE = new Node();
	NULL_NODE->node_left = NULL_NODE->node_right = NULL_NODE;
	NULL_NODE->level = 0;
	m_root = NULL_NODE;
}
BPD_TEMPLATE_CLASS typename BPD_TEMPLATE(Tree)::Node* Tree<BPD_TEMPLATE_TYPE>::Search(const T Value) { return Search(Value, m_root); }
BPD_TEMPLATE_CLASS void Tree<BPD_TEMPLATE_TYPE>::Insert(const T Value){
	Insert(Value, m_root);
}
BPD_TEMPLATE_CLASS void Tree<BPD_TEMPLATE_TYPE>::Delete(){ DeleteTree(m_root); }
BPD_TEMPLATE_CLASS void Tree<BPD_TEMPLATE_TYPE>::DeleteNode(T Value){ DeleteNode(Value, m_root); }
BPD_TEMPLATE_CLASS typename BPD_TEMPLATE(Tree)::Node * Tree<BPD_TEMPLATE_TYPE>::Root(){ return m_root; }
BPD_TEMPLATE_CLASS void Tree<BPD_TEMPLATE_TYPE>::DeleteTree(Node * leaf){
	if(leaf != nullptr){
		DeleteTree(leaf->node_left);
		DeleteTree(leaf->node_right);
		delete leaf;
	}
}
BPD_TEMPLATE_CLASS void Tree<BPD_TEMPLATE_TYPE>::DeleteNode(T Value, Node * & n){
	static Node * lastNode, *deletedNode = NULL_NODE;
	if(n != NULL_NODE){
		lastNode = n;
		if(Value < n->data){
			DeleteNode(Value, n->node_left);
		} else{
			deletedNode = n;
			DeleteNode(Value, n->node_right);
		}

		if(n == lastNode){
			if(deletedNode == NULL_NODE || Value != deletedNode->data) return;
			deletedNode->data = n->data;
			deletedNode = NULL_NODE;
			n = n->node_right;
			delete lastNode;
		} else{
			if(n->node_left->level < n->level - 1 ||
				n->node_right->level < n->level - 1){
				if(n->node_right->level > --n->level)
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
BPD_TEMPLATE_CLASS void Tree<BPD_TEMPLATE_TYPE>::Insert(T Value, Node * & leaf){
	if(leaf == NULL_NODE){
		leaf = new Node;
		leaf->data = Value;
		leaf->node_left = NULL_NODE;
		leaf->node_right = NULL_NODE;
	} else if(Value < leaf->data){
		Insert(Value, leaf->node_left);
	} else{
		Insert(Value, leaf->node_right);
	}
	Skew(leaf);
	Split(leaf);
}
BPD_TEMPLATE_CLASS typename BPD_TEMPLATE(Tree)::Node * Tree<BPD_TEMPLATE_TYPE>::Search(T Value, Node * leaf){
	if(leaf != NULL_NODE){
		if(Value == leaf->data) return leaf;
		if(Value < leaf->data) return Search(Value, leaf->node_left);
		else return Search(Value, leaf->node_right);
	} else return nullptr;
}
BPD_TEMPLATE_CLASS void Tree<BPD_TEMPLATE_TYPE>::RotateWithRightChild(Node * & n) const{
	Node * n2 = n->node_right;
	n->node_right = n2->node_left;
	n2->node_left = n;
	n = n2;
}
BPD_TEMPLATE_CLASS void Tree<BPD_TEMPLATE_TYPE>::RotateWithLeftChild(Node * & n2) const{
	Node * n = n2->node_left;
	n2->node_left = n->node_right;
	n->node_right = n2;
	n2 = n;
}
BPD_TEMPLATE_CLASS void Tree<BPD_TEMPLATE_TYPE>::Skew(Node * & n) const{
	if(n->node_left->level == n->level)
		RotateWithLeftChild(n);
}
BPD_TEMPLATE_CLASS void Tree<BPD_TEMPLATE_TYPE>::Split(Node * & n) const{
	if(n->node_right->node_right->level == n->level){
		RotateWithRightChild(n);
		n->level++;
	}
}
BPD_TEMPLATE_DEFAULT(Tree)
BPD_END