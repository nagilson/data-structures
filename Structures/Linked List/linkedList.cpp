#include "linkedList.h"

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
	std::cin.get();
	return 0;
}
