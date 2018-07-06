/// ------------------------------------------------------------------------------------ ///
/*
The following .cpp file includes an implementation of the stack data structure in C++, based 
upon a linked list like structure using nodes. 
*/
/// ------------------------------------------------------------------------------------ ///

#include <iostream>
#include <exception>
#include "Stack.h"

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
	std::cout << "\n\nPeeking on an empty Stack, (S.peek()); will throw an exception.";
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
	std::cin.get();

    return 0;
}

