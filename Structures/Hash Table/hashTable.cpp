// Showcase of using the hash table:

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include "hashTable.h"

void continuePrompt(); 

int main()
{
	std::cout << "First, we create a hashtable with a size of 5. Try to predict an accurate limit of possible entries.\n";
	std::cout << "Default initialized hashtable of type K = int, V = str:";
	std::cout << "\n(Note that this hashtable is only implemented for K = int and V = str)\n";
	hashTable<int, std::string> H(5);
	H.print();

	std::cout << "\nNext, we insert pokedex entries into the table. \n" << \
		"Insertions test collisions, full table, and more. Explained in comments. \n";
	H.insert(34, "Nidoking"); // Insertion Test
	H.insert(34, "Nidoking"); // Reinserting Same Entry
	H.insert(33, "Nidorino"); // Inserting Entry before a used space
	H.insert(32, "NidoranM"); // ... Inserting ... 
	H.insert(30, "Nidorina"); // Inserting entry at the beginning. 
	H.insert(40, "Wigglytuff"); // Inserting entry at COLLISION (start). Should go to 2.
	H.insert(112, "Rhydon"); // Inserting entry into a FULL table.
	H.print();
	continuePrompt();
	
	std::cout << "\nGreat! Now, we will showcase removing 32 (NidoranM) from the hashtable, then replacing it:\n";
	H.remove(32); // Removing Pokemon #32 from the Dex. 
	H.insert(62, "Poliwrath"); // Inserting to a once full index.
	H.print();
	std::cout << "\nPrinting entry 34's value: ";
	std::cout << H.at(34);
	std::cout << "\nPrinting an entry that doesn't exist will try to print nullptr and throw.\n";
	continuePrompt();

	std::cout << "\nLastly, we will showcase H2, where we let K = str, V = int:";
	hashTable<std::string, int> H2(6);
	H2.insert("Zero", 0); H2.insert("One", 1); H2.insert("Two", 2); 
	H2.insert("Three", 3); H2.insert("Four", 4); H2.insert("Five", 5);
	H2.remove("Two");
	H2.print();
	std::cout << "\n";

	continuePrompt();
    return 0;
}

void continuePrompt() {
	std::cout << "Press enter to continue...";
	std::cin.get();
}
