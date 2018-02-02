/// ------------------------------------------------------------------------------------ ///
/*
The following .cpp file includes an implementation of the stack data structure in C++, based 
upon a linked list like structure using nodes. 
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
		return "Can't access this value of the stack, stack probe led to nullptr.";
	}
};

template <typename T>
struct Node {

	/// ------------------------------------------------------------------------------------ ///
	/*
	Node<T> class, has a pointer to the next node and a data value of type T. 
	Not meant to be used or accessed outside of the stack structure.
	*/
	/// ------------------------------------------------------------------------------------ ///

	T data;
	Node<T> *next;

};

template <typename T> 
class Stack {

	/// ------------------------------------------------------------------------------------ ///
	/*
	Implementation of a stack through a linked list like structure. 
	Stacks have various applications -- think reversing a word, storing undos and redos, etc. 
	Each member of the stack is stored as a Node<T> pointer, in which each node has a next pointer
	as well as a data value. Values are initialized as a nullptr and exceptions are thrown when
	users try to use values with nullptrs. 

	In a stack, the last value placed in the stack is the first value to come out.
	*/
	/// ------------------------------------------------------------------------------------ ///
	
	private:

		Node<T> *head;
		int length;

	public:

		Stack<T>() {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Default stack constructor, initializes values to nullptr.
			*/
			/// ------------------------------------------------------------------------------------ ///

			this->head = nullptr;
			this->length = 0;
		}

		void push(T value) {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Append to the end of the stack a node with value T.
			*/
			/// ------------------------------------------------------------------------------------ ///

			Node<T> *entry = new Node<T>;
			entry->data = value;
			if (!(this->head)) {
				entry->next = nullptr;
			}
			else {
				entry->next = this->head;
			}
			this->head = entry;
			++(this->length);
		}

		T pop() {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Get the value from the top of the stack, in other words, the first value put into the stack. 
			*/
			/// ------------------------------------------------------------------------------------ ///

			if (this->head == nullptr) {
				throw nullptrProbed(); // Can't access this value of the stack, stack probe led to nullptr
			}
			else {
				Node<T> *top = this->head;
				if (!(this->head->next == nullptr)) {
					this->head = this->head->next;
				}
				else {
					this->head = nullptr;
				}
				T value = top->data;
				delete top;
				--(this->length);
				return value;
			}
		}

		T peek() {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Find the first value in the stack, but do not remove it. 
			*/
			/// ------------------------------------------------------------------------------------ ///

			if (this->head == nullptr) {
				throw nullptrProbed(); // Can't access this value of the stack, stack probe led to nullptr
			}
			return this->head->data;
		}

		void print() {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Print all elements in the stack. Does not include \n. Stack is printed as an array. 
			Prints nullptr if null.
			*/
			/// ------------------------------------------------------------------------------------ ///

			if (this->head == nullptr) {
				std::cout << "nullptr";
				return;
			}
			else {
				std::cout << "[";
				Node<T> *current = this->head;
				do {
					std::cout << current->data;
					current = current->next;
					if (current == nullptr) {
						break;
					}
					else {
						std::cout << ", ";
					}
				} while (true);
				std::cout << "]";
			}
		}
		bool isEmpty() {
			return((this->head == nullptr));
		}
		int& getLength() {
			return this->length;
		}
};


int main()
{

	/// ------------------------------------------------------------------------------------ ///
	/*
	Gain a few insights on how to use the stack, and see a testable demo that checks the Stack class and assures everything works. 
	*/
	/// ------------------------------------------------------------------------------------ ///

	std::cout << "Declaration of a stack: Stack<data_type> stack_name.\nIn this demo, we declare a stack S.\n";
	Stack<int> S;
	std::cout << "Return value of an empty stack.pop, S.pop(), will throw an exception."; 
	std::cout << "\n\nPeeking on an empty Stack :" << (S.peek());
	std::cout << "\nisEmpty function checks if the stack is empty: " << S.isEmpty();
	std::cout << "\nAnd... Printing the length of the empty stack: " << S.getLength();
	S.push(4);
	S.push(5);
	S.push(2); std::cout << "\nValue of the stack after pushing 4, 5, and then 2: ";
	S.print(); 
	S.pop();
	S.pop();
	std::cout << "\n\nAfter we pop 2 values from the stack, peek returns: " << S.peek(); 
	S.pop(); std::cout << "\nThe stack returns to the nullptr form after all values are popped: ";
	S.print();
	S.push(4);
	std::cout << "\nOf course, we can push 4 back to the empty stack and then print the stack: "; S.print();
	std::cout << "\n";
	std::system("pause");

    return 0;
}
