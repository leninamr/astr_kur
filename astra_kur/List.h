#pragma once
#include <iostream>
using namespace std;

class Node {
public:
	Node(string data, int priority = -1, Node* next = nullptr) {
		this->data = data;
		this->priority = priority;
		this->next = next;
	};
	~Node() {};
	string data;
	int priority = -1;
	Node* next = nullptr;
};


class List
{
private:
	Node* head;
	Node* tail;
	void add_first(string newElem, int priority);
	void add_first(Node* newElem);

public:
	List();
	~List();
	bool isEmpty();
	Node* set_head();
	
	void push_back(string newElem, int priority);
	void push_back(Node* newElem);
	void print_to_console();
	void clear();
};

