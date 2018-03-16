/// ------------------------------------------------------------------------------------ ///
/*
The following .h file includes an implementation of the queue data structure in C++, based
upon a linked list like structure using nodes.
*/
/// ------------------------------------------------------------------------------------ ///

//#include "stdafx.h" // You may want to include this if you create a VS PRJ with cmake.
#include <iostream>
#include <exception>

struct nullptrProbed : public std::exception {

	/// ------------------------------------------------------------------------------------ ///
	/*
	Custom exception. users do not want their program to continue when accessing a nullptr.
	*/
	/// ------------------------------------------------------------------------------------ ///

	const char * what() const throw() {
		return "Can't access this value of the queue, probe led to nullptr.";
	}
};

template <typename T>
struct Node {

	/// ------------------------------------------------------------------------------------ ///
	/*
	A simple node, not to be used outside of the class.
	Each node consists of a pointer to the next node (initialized as nullptr) and then data of type T.
	*/
	/// ------------------------------------------------------------------------------------ ///

	Node<T> *next;
	T data;

};

template <typename T>
class Queue {

	/// ------------------------------------------------------------------------------------ ///
	/*
	This is a basic implementation of the queue data structure using a linked list like structure.
	In a queue, the first object to go in is the first object to go out. That is, if you add a value to
	... a queue with two values, then the most recent value won't come out until 3 operations later.

	This is useful for prinitng queues, and CPU scheduling.
	*/
	/// ------------------------------------------------------------------------------------ ///

private:

	Node<T> *head;
	Node<T> *tail;
	int length;

public:

	Queue<T>() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Default queue constructor, initializes values to nullptr.
		*/
		/// ------------------------------------------------------------------------------------ ///

		this->head = nullptr;
		this->tail = nullptr;
		this->length = 0;
	}

	T pop() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Remove the top of the queue, the first element inserted into the queue. Returns the value of the data in the top node.
		Throws an exception if an empty queue is popped.
		*/
		/// ------------------------------------------------------------------------------------ ///

		if (this->head == nullptr) {
			throw nullptrProbed(); // Can't access this value of the queue, probe led to nullptr
		}
		T content = this->head->data;
		Node<T> *first = new Node<T>;
		if (this->head->next == nullptr) {
			first = nullptr;
		}
		else {
			first = this->head->next;
		}
		Node<T>* kill = this->head;
		this->head = first;
		delete kill;
		--(this->length);
		return content;
	}

	void push(T value) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Create a new node<T> with content of value. Put the new node at the end of the queue.
		*/
		/// ------------------------------------------------------------------------------------ ///

		Node<T> *newNode = new Node<T>;
		newNode->data = value;
		++(this->length);
		if (this->head == nullptr) {
			newNode->next = nullptr;
			this->head = newNode;
			this->tail = newNode;
		}
		else if (this->head->next == nullptr) {
			newNode->next = nullptr;
			this->head->next = newNode;
			this->tail = newNode;
		}
		else {
			newNode->next = nullptr;
			this->tail->next = newNode;
			this->tail = newNode;
		}
	}

	void print() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Print all values of the queue, using an array look-alike structure.
		*/
		/// ------------------------------------------------------------------------------------ ///

		if (this->head == nullptr) {
			std::cout << "nullptr";
			return;
		}
		std::cout << "[";
		Node<T> *current = this->head;
		do {
			if (current->next == nullptr) {
				std::cout << current->data << "]";
				break;
			}
			std::cout << current->data << ", ";
			current = current->next;
		} while (true);
	}

	T peek() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Throws an exception if an empty queue is peeked.
		Otherwise, without removing the top, gives the information contained in the top of the queue of type T.
		*/
		/// ------------------------------------------------------------------------------------ ///

		if (this->head == nullptr) {
			throw nullptrProbed(); // Can't access this value of the queue, probe led to nullptr
		}
		else {
			return this->head->data;
		}
	}

	bool isEmpty() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Returns true if the queue is empty, else false.
		*/
		/// ------------------------------------------------------------------------------------ ///

		if (this->head == nullptr) {
			return true;
		}
		return false;
	}

	int getLength() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Returns an int -- the length of the given queue.
		*/
		/// ------------------------------------------------------------------------------------ ///

		return this->length;

	}
};
