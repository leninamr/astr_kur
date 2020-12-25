#include "Stack.h"

Stack::Stack() {
	top = nullptr;
}
Stack::~Stack() {
	while (!isEmpty()) {
		pop();
	}
}

void Stack::push(string data, int priority) {
	top = new stack_Node(data, priority, top);
}
void Stack::push(Node* new_elem) {
	top = new stack_Node(new_elem, top);
}
void Stack::push(char new_elem, int priority) {
	string insert;
	insert.push_back(new_elem);
	top = new stack_Node(insert, priority, top);
}

Node* Stack::pop() {
	Node* temp = top->element;
	top = top->next;
	return temp;
}
bool Stack::isEmpty() {
	return (top == nullptr);
}
Node* Stack::getTop() {
	return top->element;
}
