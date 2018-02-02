/// ------------------------------------------------------------------------------------ ///
/*
The following .cpp file includes an implementation of the linked list data structure in C++, using 
Node<T> values with pointers and a data type. 
*/
/// ------------------------------------------------------------------------------------ ///

//#include "stdafx.h" You may want to include this if you create a VS PRJ with cmake.
#include <iostream>
#include <exception>

struct nullptrProbed : public std::exception {

	/// ------------------------------------------------------------------------------------ ///
	/*
	Custom exception. users do not want their program to continue when accessing a nullptr.
	*/
	/// ------------------------------------------------------------------------------------ ///

	const char * what() const throw() {
		return "Can't access this value of the list, probe led to nullptr.";
	}
};

template <typename T>
struct Node {

	/// ------------------------------------------------------------------------------------ ///
	/*
	Node<T> class, has a pointer to the next Node and a data value of type T.
	Not meant to be used or accessed outside of the list structure.
	*/
	/// ------------------------------------------------------------------------------------ ///

	T data;
	Node<T> *next;

};

template <typename T>
class linkedList {

	/// ------------------------------------------------------------------------------------ ///
	/*
	You should initialize the list using the initialization function.
	Template implementation of the linked list like data structure. 
	Linked lists can be used to implement arrays, vectors, etc. This template based linked list uses a collection
	of Nodes with values data of type T, and pointers to each next Node.

	The list contains a head and a tail so we can access those elements in O(1) time.
	*/
	/// ------------------------------------------------------------------------------------ ///

	private:

		Node<T> *head;
		Node<T> *tail;
		int length;

	public:

		linkedList<T> operator=(linkedList<T> &other) {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Assign one linked list's values into a new list. Creates a deep copy. 
			*/
			/// ------------------------------------------------------------------------------------ ///

			copyList(other);
			return *this;

		}

		linkedList() {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Basic constructor of the linked list data structure. Assigns head and tail to nullptr.
			*/
			/// ------------------------------------------------------------------------------------ ///

			this->head = nullptr;
			this->tail = nullptr;
			this->length = 0;
		}

		void initList(T value);
		void destructList();
		void deleteNode(const int where);
		void print();
		void append(T what);
		void copyList(const linkedList<T>& other);
		void insert(const int &where, T value);
		int getLength();
		bool isEmpty();

		T top() {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Get the top of the list.
			*/
			/// ------------------------------------------------------------------------------------ ///

			return this->head->data;
		}

		T back() {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Get the bottom of the list. 
			*/
			/// ------------------------------------------------------------------------------------ ///

			return this->tail->data;
		}

		T at(int i) {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Return the value of the list at an iteration point i. 
			If i goes outside of the list, exceptions are thrown.
			*/
			/// ------------------------------------------------------------------------------------ ///

			Node<T> *current = this->head;
			int loc = 0;
			while (current->next != nullptr && loc != i) {
				current = current->next;
				++loc;
			}
			if (current->next == nullptr && i+1 != this->length) {
				throw nullptrProbed(); // Can't access this value of the list, probe led to nullptr
			}
			else {
				return current->data;
			}
		}
};

template <typename T>
void linkedList<T>::initList(T value) {

	/// ------------------------------------------------------------------------------------ ///
	/*
	Initialize a list so we can access the values without reaching nullptr.
	*/
	/// ------------------------------------------------------------------------------------ ///

	this->head = new Node<T>();
	this->head->next = nullptr;
	this->head->data = value;
	this->tail = this->head;
	this->length = 1;
}

template <typename T>
void linkedList<T>::copyList(const linkedList<T>& other) {
	
	/// ------------------------------------------------------------------------------------ ///
	/*
	Create a deep copy of a list, from other into *this.
	*/
	/// ------------------------------------------------------------------------------------ ///

	if (this->head != nullptr) {
		this->destructList();
	}
	if (other.head == nullptr) {
		this->head = nullptr;
		this->tail = nullptr;
		this->length = 0;
	}
	else {
		Node<T> *where = other.head;
		this->head = new Node<T>;
		this->head->data = other.head->data;
		this->head->next = other.head->next;
		while (!(where->next == nullptr)) {
			this->append(where->data);
			where = where->next;
		}
		this->append(where->data);
	}
}

template <typename T>
void linkedList<T>::deleteNode (const int where) {

	/// ------------------------------------------------------------------------------------ ///
	/*
	Delete the node at a point, where. Where starts at 0 and goes to the length of the node. 
	Exception thrown if we go out of range.
	*/
	/// ------------------------------------------------------------------------------------ ///

	Node<T> *current;
	auto i = 0;
	if (!(this->head == nullptr)) {
		current = this->head;
	}
	else {
		std::cout << "nullptr\n";
		return;
	}
	if ((current != nullptr)) {
		while (!(current->next == nullptr) && i != where) {
			current = current->next;
			++i;
		}
		if (current->next == nullptr && where+1 != this->length) {
			throw nullptrProbed(); // Can't access this value of the list, probe led to nullptr
		}
		else {
			if (where+1 == this->length) {
				Node<T> *kill = this->tail;
				this->tail = current;
				--(this->length);
				delete kill;
			}
			else if(where == 0){
				Node<T> *kill = this->head;
				this->head = this->head->next;
				--(this->length);
				delete kill;
			}
			else {
				current->next = current->next->next;
				--(this->length);
				delete (current->next);
			}
		}
	}
	else {
		return;
	}
}

template <typename T>
void linkedList<T>::print() {
	
	/// ------------------------------------------------------------------------------------ ///
	/*
	Print all elements in the list in a python like list structure. 
	Gives "nullptr" string if null.
	*/
	/// ------------------------------------------------------------------------------------ ///

	Node<T> *current;
	if (!(this->head == nullptr)) {
		current = this->head;
	}
	else {
		std::cout << "nullptr\n";
		return;
	}
	std::cout << "<";
	while (!(current->next == nullptr)) {
		std::cout << current->data << ", ";
		current = current->next;
	}
	std::cout << current->data << ">";
}

template <typename T>
void linkedList<T>::destructList() {

	/// ------------------------------------------------------------------------------------ ///
	/*
	Free all of the memory used inside of the list.
	*/
	/// ------------------------------------------------------------------------------------ ///

	Node<T> *kill;
	while (this->head != nullptr) {
		kill = this->head;
		this->head = this->head->next; 
		delete kill; 
	}
	this->tail = nullptr;
	this->length = 0;
}

template <typename T>
bool linkedList<T>::isEmpty() {

	/// ------------------------------------------------------------------------------------ ///
	/*
	If the list is empty, true. Else, false.
	*/
	/// ------------------------------------------------------------------------------------ ///

	return !(this->head);
}

template <typename T>
void linkedList<T>::insert(const int &where, T value) {

	/// ------------------------------------------------------------------------------------ ///
	/*
	Insert a new Node with the value of value, of type T.
	The new Node is inserted after iterator int where. Insert at 0 and you will have a new Node at 1. 
	*/
	/// ------------------------------------------------------------------------------------ ///
	
	Node<T> *current;
	int i = 0;
	if (!(this->head == nullptr)) {
		current = this->head;
	}
	else {
		return;
	}

	while (!(current->next == nullptr) && i+1 != where) {
		current = current->next;
		++i;
	}
	Node<T> *newNode = new Node<T>();
	newNode->data = value;
	newNode->next = current->next;
	if (where == this->length) {
		newNode->next = nullptr;
		this->tail = newNode;
	}
	current->next = newNode;
	++(this->length);
}

template <typename T>
int linkedList<T>::getLength() {
	
	/// ------------------------------------------------------------------------------------ ///
	/*
	Return the length of the list.
	*/
	/// ------------------------------------------------------------------------------------ ///

	return this->length;
}

template <typename T>
void linkedList<T>::append(T what) {

	/// ------------------------------------------------------------------------------------ ///
	/*
	Append a new Node<T> to the end of the list with the value of what. 
	*/
	/// ------------------------------------------------------------------------------------ ///

	Node<T> *end = new Node<T>();
	end->data = what;
	end->next = nullptr;
	if (this->length != 0) {
		this->tail->next = end;
	}
	++(this->length);
	this->tail = end;
}

int main()
{

	/// ------------------------------------------------------------------------------------ ///
	/*
	Gain a few insights on how to use the list, and see a testable demo that checks the list class and assures everything works.
	*/
	/// ------------------------------------------------------------------------------------ ///

	std::cout << "Here, we will showcase the usage of the likedList class.\nYou declare a linkedList like so: linkedList<data_type> variable_name.\n";
	linkedList<int> List;
	std::cout << "\nYou should use initList on each list object you create. \nThis allows us to avoid exceptions, and ensure at least one node exists.\n";
	List.initList(4);
	List.append(5);
	List.append(6); 
	List.append(7);
	std::cout << "\n\nThe list after we append 5, 6, and then 7: ";
	List.print(); 

	linkedList<int> List2;
	List2.initList(5);
	List2.insert(1, 2); 
	List2.append(6);
	std::cout << "\nHere, we showcase the creation of a second list. \nThis list uses the insert method to insert 2 at the 2nd (i = 1) element: ";
	List2.print();
	std::cout << "\nList after calling deleteNode at 0: ";
	List2.deleteNode(0);
	List2.print();
	List2 = List;
	std::cout << "\nAssignment of list to another, the second list has turned into the original: ";
	List.print();
	std::cout << "\n\n";
	std::system("pause");
    return 0;
}
