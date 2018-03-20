#include "stdafx.h" //You may want to include this if you create a VS PRJ with cmake.
#include "Heap.h"

void continuePrompt();

int main() {

	std::cout << "A heap is created with a template type H<type> and then a var name.\n";
	std::cout << "The two parameters define the maximum heap size and TRUE if minRoot tree, FALSE if maxRoot tree.\n";
	Heap<int> H(8, true);
	H.insert(13);
	H.insert(100);
	H.insert(52);
	H.insert(34);
	H.insert(22);
	H.insert(76);
	H.insert(0);
	H.insert(12);
	std::cout << "We insert into the heap by every individual element, and then try to add to a full heap: \n";
	H.insert(60);

	std::cout << "\n";
	H.print();
	std::cout << "We created a minHeap, now we will make a maxHeap.\n";
	continuePrompt();

	Heap<int> HMax(8, false);
	HMax.insert(13);
	HMax.insert(100);
	HMax.insert(52);
	HMax.insert(34);
	HMax.insert(22);
	HMax.insert(76);
	HMax.insert(0);
	HMax.insert(12);

	HMax.print();
	continuePrompt();

	std::cout << "\nNow, we shall delete the top ('extract') of the minHeap then maxHeap. If the heap was empty, we would throw.\n";
	H.extractRoot();
	H.print();
	continuePrompt();

	HMax.extractRoot();
	HMax.print();
	continuePrompt();

	std::cout << "\nReturning minima and maxim of the corresponding trees: (will throw if empty)\n" \
		<< "MIN: " << H.getRoot() << " | MAX: " << HMax.getRoot();

	std::cout << "\n\n... And finally, we will show heap init given an array : [3, 0, 2, 6, 4, 1, 7]";

	int arr[7] = {3, 0, 2, 6, 4, 1, 7};
	Heap<int> HL(7, true, arr); // (HList)
	Heap<int> HLMax(7, false, arr);
	std::cout << "\nMinima Tree Initialized via Array: "; HL.print();
	std::cout << "Maxima Tree Initialized via Array: "; HLMax.print();
	std::cout << "\n";
	std::system("pause");

	return 0;
}

void continuePrompt() {
	std::cout << "Press enter to continue...";
	std::cin.get();
}
