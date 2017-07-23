/*
#include "Biped\bpd\LinkedList.h"
BPD_BEGIN

BPD_TEMPLATE_CLASS bool LinkedList<BPD_TEMPLATE_TYPE>::Node::operator==(const Node& other) const{
	if(value == other.value &&
		next == other.next) return true;
	return false;
};
BPD_TEMPLATE_CLASS typename BPD_TEMPLATE(LinkedList)::Node& LinkedList<BPD_TEMPLATE_TYPE>::Node::operator+(const int value){
	Node* temp;
	temp = this->next;
	for(int i = 0; i < value; i++){
		if(temp->next == nullptr) return *temp;
		temp = temp->next;
	} return *temp;
};
BPD_TEMPLATE_CLASS typename BPD_TEMPLATE(LinkedList)::Node* LinkedList<BPD_TEMPLATE_TYPE>::begin() const { return m_head; };
BPD_TEMPLATE_CLASS typename BPD_TEMPLATE(LinkedList)::Node* LinkedList<BPD_TEMPLATE_TYPE>::end() const { return m_tail; };
BPD_TEMPLATE_CLASS typename BPD_TEMPLATE(LinkedList)::Node& LinkedList<BPD_TEMPLATE_TYPE>::front() { return *m_head; };
BPD_TEMPLATE_CLASS typename BPD_TEMPLATE(LinkedList)::Node& LinkedList<BPD_TEMPLATE_TYPE>::back() { return *m_tail; };

BPD_TEMPLATE_CLASS BPD_TEMPLATE_TYPE& LinkedList<BPD_TEMPLATE_TYPE>::operator[](const size_type index) const{
	if(index == -1) BPD_EXCEPTION("Out of range");
	Node* cur = new Node, *pre = new Node;
	cur = m_head;
	for(int i = 0; i < (int)index; i++){
		if(cur->next == nullptr && i < (int)index)
			BPD_EXCEPTION("Out of range");
		pre = cur;
		cur = cur->next;
	} return cur->value;
};
BPD_TEMPLATE_CLASS BPD_TEMPLATE_TYPE& LinkedList<BPD_TEMPLATE_TYPE>::find(const size_type index) const{
	if(index == -1) BPD_EXCEPTION("Out of range");
	Node* cur = new Node, *pre = new Node;
	cur = m_head;
	for(int i = 0; i < (int)index; i++){
		if(cur->next == nullptr && i <= (int)index)
			BPD_EXCEPTION("Out of range");
		pre = cur;
		cur = cur->next;
	} return cur->value;
};
BPD_TEMPLATE_CLASS int LinkedList<BPD_TEMPLATE_TYPE>::find_n(Node node) const{
	Node* cur = new Node, *pre = new Node;
	cur = m_head;
	int count = 0;
	while(cur != nullptr){
		if(*cur == node) break;
		if(cur->next == nullptr)
			return -1;
		pre = cur;
		cur = cur->next;
		count++;
	} return count;
};
BPD_TEMPLATE_CLASS int LinkedList<BPD_TEMPLATE_TYPE>::find_i(T value) const{
	Node* cur = new Node, *pre = new Node;
	cur = m_head;
	int count = 0;
	while(cur != nullptr){
		if(cur->value == value) break;
		if(cur->next == nullptr) return -1;
		pre = cur;
		cur = cur->next;
		count++;
	} return count;
};
BPD_TEMPLATE_CLASS void LinkedList<BPD_TEMPLATE_TYPE>::operator=(LinkedList& other){
	if(this->size() != other.size()) BPD_EXCEPTION("Linked List Copy Size");
	for(int i = 0; i < m_size; i++) find(i) = other[i];
};
BPD_TEMPLATE_CLASS int LinkedList<BPD_TEMPLATE_TYPE>::size() const{ return m_size; };
BPD_TEMPLATE_CLASS bool LinkedList<BPD_TEMPLATE_TYPE>::empty(){
	if(m_size) return false;
	return true;
};
BPD_TEMPLATE_CLASS void LinkedList<BPD_TEMPLATE_TYPE>::clear(){
	m_size = 0;
	Node* cur = new Node, *pre = new Node;
	cur = m_head;
	while(cur->next != nullptr){
		pre = cur;
		cur = cur->next;
		BPD_SAFE_DELETE(pre);
	} BPD_SAFE_DELETE(cur);
	m_head = m_tail = nullptr;
};
BPD_TEMPLATE_CLASS void LinkedList<BPD_TEMPLATE_TYPE>::insert(const int pos, const T& value) {
	m_size++;
	Node* temp = new Node;
	if(pos != 0){
		temp->value = value;
		temp->next = nullptr;
		Node* cur = new Node, *pre = new Node;
		cur = m_head;
		for(int i = 0; i < pos; i++){
			pre = cur;
			cur = cur->next;
		}
		pre->next = temp;
		temp->next = cur;
	} else {
		temp->value = value;
		temp->next = m_head;
		m_head = temp;
	}
};
BPD_TEMPLATE_CLASS void LinkedList<BPD_TEMPLATE_TYPE>::insert(Node& node, const T& value){
	m_size++;
	Node* temp = new Node;
	temp->value = value;
	temp->next = nullptr;
	Node* cur = new Node, *pre = new Node;
	cur = m_head;
	while(cur->next != nullptr){
		if(*cur == node){
			pre->next = temp;
			temp->next = cur;
			break;
		}
		pre = cur;
		cur = cur->next;
	}
};
BPD_TEMPLATE_CLASS void LinkedList<BPD_TEMPLATE_TYPE>::erase(const int pos){
	m_size--;
	Node* cur = new Node, *pre = new Node;
	cur = m_head;
	for(int i = 0; i < pos; i++){
		pre = cur;
		cur = cur->next;
	}
	pre->next = cur->next;
	BPD_SAFE_DELETE(cur);
};
BPD_TEMPLATE_CLASS void LinkedList<BPD_TEMPLATE_TYPE>::push_back(const T& value){
	m_size++;
	Node* temp = new Node;
	temp->value = value;
	temp->next = nullptr;
	if(m_head == nullptr){
		m_head = temp;
		m_tail = temp;
		temp = nullptr;
	} else{
		if(m_head == m_tail){
			m_head->next = temp;
			m_tail = temp;
		} else{
			m_tail->next = temp;
			m_tail = temp;
		}
	}
};
BPD_TEMPLATE_CLASS void LinkedList<BPD_TEMPLATE_TYPE>::pop_back(){
	m_size--;
	Node* cur = new Node, *pre = new Node;
	cur = m_head;
	while(cur->next != nullptr){
		pre = cur;
		cur = cur->next;
	}
	m_tail = pre;
	pre->next = nullptr;
	delete cur;
}
BPD_TEMPLATE_DEFAULT_P(LinkedList)
BPD_END
*/