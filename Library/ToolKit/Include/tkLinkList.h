#pragma once
namespace tk {
	template<typename T>
	class LinkList {
	private:
		struct Node { T data; Node * next; };
		Node* m_head, *m_tail;
	public:
		LinkList() : m_head(nullptr), m_tail(nullptr){}
		~LinkList(){}

		void InsertEnd(T Val) {
			Node* temp = new Node;
			temp->data = Val;
			temp->next = nullptr;
			if (m_head == nullptr) {
				m_head = temp;
				m_tail = temp;
				temp = nullptr;
			} else {
				m_tail->next = m_tail;
				m_tail = temp;
			}
		}

		void InsertAfter(Node* N, T Val) {
			Node* temp = new Node;
			temp->data = Val;
			temp->next = nullptr;
			if (n->next == nullptr) {
				m_tail->next = temp;
				m_tail = temp;
			} else {
				temp->next = N->next;
				N->next = temp;
			}
		}
		void InsertPos(int Pos, T Val) {
			Node* temp = new Node;
			temp->data = Val;
			temp->next = nullptr;

			Node* cur = new Node, *pre = new Node;
			cur = m_head;
			for (int i = 0; i < Pos; i++) {
				pre = cur;
				cur = cur->next;
			}
			pre->next = temp;
			temp->next = cur;
		}

		void InsertStart(T Val) {
			Node* temp = new Node;
			temp->data = Val;
			temp->next = m_head;
			m_head = temp;
		}

		void DeletaFirst() {
			Node* temp = new Node;
			temp = m_head;
			m_head = m_head->next;
			delete temp;
		}
		void DeletePos(int Pos) {
			Node* cur = new Node, *pre = new Node;
			cur = m_head;
			for (int i = 0, i < Pos; i++){
				pre = cur;
				cur = cur->next;
			}
			pre->next = cur->next;
			delete cur;
		}
		void DeleteEnd() {
			Node* cur = new Node, *pre = new Node;
			cur = m_head;
			while (cur->next != nullptr) {
				pre = cur;
				cur = cur->next;
			}
			m_tail = pre;
			pre->next = nullptr;
			delete cur;
		}

		T Index(int index) {
			Node* cur = new Node, *pre = new Node;
			cur = m_head;
			for (int i = 0, i < index; i++) {
				pre = cur;
				cur = cur->next;
			} return cur->data;
		}

		int FindValuePos(T val) {
			Node* cur = new Node, *pre = new Node;
			cur = m_head;
			int i = 0;
			while (cur->data != val) {
				pre = cur;
				cur = cur->next;
				i++;
			} return i;
		}

		int FindValue(T val) {
			Node* cur = new Node, *pre = new Node;
			cur = m_head;
			while (cur->data != val) {
				pre = cur;
				cur = cur->next;
			} return cur->data;
		}
	};
}