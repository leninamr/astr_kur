#pragma once
#include "List.h"


class Stack {
private:
	class stack_Node {
	public:
		stack_Node(Node* element = nullptr, stack_Node* next = nullptr) {
			this->element = element;
			this->next = next;
		};
		stack_Node(string data = "#", int priority = -1, stack_Node* next = nullptr) {
			this->element = new Node(data, priority, nullptr);
			this->next = next;
		};
		~stack_Node() {};

		Node* element;
		stack_Node* next;
	};
	stack_Node* top;
public:
	Stack();
	~Stack();

	void push(Node*);
	void push(string data, int priority);
	void push(char new_elem, int priority);
	Node* pop();
	bool isEmpty();
	Node* getTop();
};
