#pragma once
/// ------------------------------------------------------------------------------------ ///
/*
The following .h file includes an implementation of the BINARY heap, of types
... min and max, using std::vector.
*/
/// ------------------------------------------------------------------------------------ ///
#include <vector>
#include <iostream>

template <typename T>
class Heap{

	/// ------------------------------------------------------------------------------------ ///
	/*
	The heap data structure is a tree structure, where each parent >= (max) or (min) <= ALL children. 
	It comes in many types, but this heap is implemented as an array (std::vector). 
	It is a binary heap (not a binary tree) and contains both a max implementation and a min implementation.

	bool isMinType is true if the minima is at the root, else, the maxima is at the root.
	The heap contains a capacity, the maximum allocation for elements in the heap, and a current size.
	Constructor takes a size and true or false depending on whether or not if the root is the minima.
	*/
	/// ------------------------------------------------------------------------------------ ///

	private:

		std::vector<T> heap;
		bool minType; // If false, max is at root.
		int capacity;
		int currentSize;
		 
		void swap(int pos1, int pos2) {
			T temp = this->heap[pos1];
			this->heap[pos1] = this->heap[pos2];
			this->heap[pos2] = temp;
		}
		
		void heapifyInsert(int where) {
			if (this->minType) {
				heapifyMinUp(where);
			}
			else {
				heapifyMaxUp(where);
			}
		}

		void heapifyMinUp(int where) {

			int parentLoc = parent(where);
			T parent = this->heap[parentLoc];
			T child = this->heap[where];

			if (parent <= child){
				return;
			}
			else {
				swap(parentLoc, where);
				heapifyMinUp(parentLoc);
			}
		}

		void heapifyMaxUp(int where) {

			int parentLoc = parent(where);
			T parent = this->heap[parentLoc];
			T child = this->heap[where];

			if (parent >= child) {
				return;
			}
			else {
				swap(parentLoc, where);
				heapifyMaxUp(parentLoc);
			}
		}

		void heapifyMinDown(int where) {

			int rightChildLoc = (where + 1) * 2;
			int leftChildLoc = rightChildLoc - 1;


			if (leftChildLoc > this->currentSize - 1) {
				// The node at WHERE has no children. Property is good.
				return;
			}
			else if (rightChildLoc > this->currentSize - 1) {
				// The node has 1 child.

				if (this->heap[leftChildLoc] < this->heap[where]) {
					// If the child of the node is less than the parent!
					swap(leftChildLoc, where); // Swap the child and parent.
					heapifyMinDown(leftChildLoc);
				}
				else {
					return; // The property is satisfied.
				}
			}
			else {
				// The node has 2 children.
				// Find the lower child: 
				if (this->heap[leftChildLoc] > this->heap[rightChildLoc]) {
					// the right child is the smaller child.
					if (this->heap[rightChildLoc] < this->heap[where]) {
						// The right child is smaller than the parent.
						swap(rightChildLoc, where);
						heapifyMinDown(rightChildLoc);
					}
					else {
						return; // The property is valid.
					}
				}
				else {
					// the left child is the smaller child.
					if (this->heap[leftChildLoc] < this->heap[where]) {
						// The left child could be the new minima.
						swap(leftChildLoc, where);
						heapifyMinDown(leftChildLoc);
					}
					else {
						return; // The property is valid.
					}
				}
			}
		}

		void heapifyMaxDown(int where) {

			int rightChildLoc = (where + 1) * 2;
			int leftChildLoc = rightChildLoc - 1;


			if (leftChildLoc > this->currentSize - 1) {
				// The node at WHERE has no children. Property is good.
				return;
			}
			else if (rightChildLoc > this->currentSize - 1) {
				// The node has 1 child.

				if (this->heap[leftChildLoc] > this->heap[where]) {
					// If the child of the node is less than the parent!
					swap(leftChildLoc, where); // Swap the child and parent.
					heapifyMaxDown(leftChildLoc);
				}
				else {
					return; // The property is satisfied.
				}
			}
			else {
				// The node has 2 children.
				// Find the lower child: 
				if (this->heap[leftChildLoc] < this->heap[rightChildLoc]) {
					// the right child is the smaller child.
					if (this->heap[rightChildLoc] > this->heap[where]) {
						// The right child is smaller than the parent.
						swap(rightChildLoc, where);
						heapifyMaxDown(rightChildLoc);
					}
					else {
						return; // The property is valid.
					}
				}
				else {
					// the left child is the smaller child.
					if (this->heap[leftChildLoc] > this->heap[where]) {
						// The left child could be the new minima.
						swap(leftChildLoc, where);
						heapifyMaxDown(leftChildLoc);
					}
					else {
						return; // The property is valid.
					}
				}
			}



		}

		int parent(int where) {
			return (where <= 0) ? 0 : ((where - 1) / 2);
		}

	public:

		Heap<T>(const int &reserveSizeMax, bool minAtTop) {
			
			if (minAtTop) {
				this->minType = true;
			}
			else {
				this->minType = false;
			}
			this->capacity = reserveSizeMax;
			this->heap.reserve(reserveSizeMax);
			this->currentSize = 0;

		}
		
		Heap<T>(const int &arrSize, bool minAtTop, T arr[]) {

			if (minAtTop) {
				this->minType = true;
			}
			else {
				this->minType = false;
			}
			this->capacity = arrSize;
			this->heap.reserve(arrSize);
			this->currentSize = arrSize;

			for (auto i = 0; i != (arrSize); ++i) {
				this->heap.push_back(arr[i]);
			}

			int k = (arrSize / 2) -1;
			if (minAtTop) {
				while (k > -1) {
					heapifyMinDown(k);
					--k;
				}
			}
			else {
				while (k > -1) {
					heapifyMaxDown(k);
					--k;
				}
			}

		}

		void print() {
			std::cout << "[ ";
			for (auto member : this->heap) {
				std::cout << member << " ";
			}
			std::cout << "]\n";
		}

		void insert(T what) {
			if (this->currentSize >= this->capacity) {
				std::cout << "\n<ERR: The heap is full, or insertion too big.>\n";
				return;
			}
			else {
				this->heap.push_back(what);
				heapifyInsert(currentSize);
				++(this->currentSize);
			}
		}

		T extractRoot() {

			if (this->currentSize == 0) {
				// Tree is empty.
				throw;
			}

			else {
				T top = this->heap[0];

				this->heap[0] = this->heap[this->currentSize -1];
				this->heap.pop_back();
				--(this->currentSize);


				if (this->minType == true) {
					heapifyMinDown(0);
				}

				else {
					heapifyMaxDown(0);
				}

				return top;
			}
		}
		
		T getRoot() {
			if (this->currentSize == 0) {
				// Tree is empty
				throw;
			}
			else {
				return this->heap[0];
			}
		}
};
