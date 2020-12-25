#include "List.h"
List::List()
{
	head = nullptr;
	tail = nullptr;
}

List::~List() {
	clear();
}

bool List::isEmpty() {
	return (head == nullptr);
}

void List::add_first(string newElem, int priority)
{
	head = new Node(newElem,priority);
	tail = head;
}

void List::add_first(Node* newElem)
{
	head = newElem;
	head->next = nullptr;
	tail = head;
}

Node* List::set_head() {
	return head;
}

//insert element in the end of list
void List::push_back(string newElem, int priority)
{
	if (isEmpty()) {
		add_first(newElem,priority);
	}
	else {
		tail->next = new Node(newElem,priority);
		tail = tail->next;
	}
}

//insert element in the end of list
void List::push_back(Node* newElem)
{
	if (isEmpty()) {
		add_first(newElem);
	}
	else {
		tail->next = newElem;
		tail = tail->next;
	}
}

//output of list elements to the console
void List::print_to_console() {
	Node* current = head;
	while (current != nullptr) {
		//if (!((current->data[0] == '0') && (current->data.size() == 1)))
			cout << current->data<<' ' ;
		current = current->next;
	}
	cout << endl;
}


void List::clear() {
	if (isEmpty()) {
		throw out_of_range("Removing elements in an empty list is not possible");
	}
	Node* current = head;
	while (!(this->isEmpty())) {
		current = head;
		head = current->next;
		delete current;
	}
}
