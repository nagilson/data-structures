#include "Queue.h"


int main()
{

	/// ------------------------------------------------------------------------------------ ///
	/*
	Gain a few insights on how to use the queue, and see a testable demo that checks the Queue class and assures everything works.
	*/
	/// ------------------------------------------------------------------------------------ ///

	std::cout << "We declare a queue as Queue<data_type> variable_name.\nThe following sample declares a queue Q.\n"; 
	Queue<int> Q;
	std::cout << "\nChecking if the empty queue is empty: " << Q.isEmpty();
	std::cout << "\nEmpty queue print method: "; Q.print();
	Q.push(4);
	Q.push(5);
	std::cout << "\nWe push 4 and 5 into the queue, pop will return value 4 from the queue: " << Q.pop();
	std::cout << "\nPrinting the new queue value : ";  Q.print();
	Q.pop();
	std::cout << "\nThe length of the queue after a pop: " << Q.getLength();
	std::cout << "\nAnd now, the printing of the queue: "; Q.print();
	Q.push(5);
	Q.push(3); 
	std::cout << "\n\nTo check one more time, we will push 5 and 3 to the queue, and print the queue: ";
	Q.print();
	std::cout << "\n\n";
	std::cin.get();

	return 0;
}
