//#include "stdafx.h" //You may want to include this if you create a VS PRJ with cmake.
#include "BinaryTree.h"

int main() {
	
	binaryTree<int> T;
	T.insert(4);
	T.insert(2);
	T.insert(5);
	T.insert(2);
	T.insert(3);
	T.insert(10);
	T.insert(9);
	T.insert(7);
	T.insert(8);
	T.insert(13);
	T.insert(11);
	T.insert(13);
	T.insert(12);
	T.insert(1);
	std::cout << "Showcasing adding values to the binary tree, and printing the tree:\n";
	T.print();
	
	std::cout << "Using TreeObj.Find(value) to find 3 and 6. 6 is not in the tree.\n";
	std::cout << "3 is at memory location: " << T.find(3) << "\n";
	std::cout << "6 is at memory location: " << T.find(6) << "\n";
	
	std::cout << "\nWe delete 10, 13, 3, and then 4 from the tree.";
	T.erase(10);
	T.erase(13);
	T.erase(3);
	T.erase(4); 
	T.print();

	std::cout << "\nUsing the assignment operator to create a copy tree: \n";
	binaryTree<int> T2;
	T2 = T;
	T2.print();
	std::cout << "\n";
	T2.deleteTree();
	std::cout << "We validate the copy by deleting the copy, and then printing the original:\n";
	T.print();
	
	std::cout << "... and, to validate the deletion of the tree copy: ";
	T2.print();
	std::cout << "\n";
	system("pause");
	return 0;
}
