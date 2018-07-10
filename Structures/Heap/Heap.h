#pragma once
/// ------------------------------------------------------------------------------------ ///
/*
The following .h file includes an implementation of the binary heap, of types
... min and max, using std::vector.
*/
/// ------------------------------------------------------------------------------------ ///

#include <vector>
#include <iostream>

template <typename T>
class Heap{

	/// ------------------------------------------------------------------------------------ ///
	/*
	The heap data structure is a complete tree structure, where each parent >= (max) or (min) <= ALL children. 
	It comes in many types, but this heap is implemented as an "array" (std::vector). 
	It is a binary heap (not a binary tree) and contains both a max implementation and a min implementation.
	Heaps are typically used as priority queues (order is not based on first in, but who is "more important.") 

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

			/// ------------------------------------------------------------------------------------ ///
			/*
			Swap the nodes in the heap at a given group of positions, pos1 and pos2.
			*/
			/// ------------------------------------------------------------------------------------ ///

			T temp = this->heap[pos1];
			this->heap[pos1] = this->heap[pos2];
			this->heap[pos2] = temp;
		}
		
		void heapifyInsert(int where) {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Interface that allows insertion into the heap without an explicit boolean parameter.
			Calls heapifyUp for either min or max depending on minType of the tree *this.
			*/
			/// ------------------------------------------------------------------------------------ ///

			if (this->minType) {
				heapifyMinUp(where);
			}
			else {
				heapifyMaxUp(where);
			}
		}

		void heapifyMinUp(int where) {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Going up the tree, swap the parents if need be to ensure the minima is at the top. (use after INSERTION.)
			Typical time is O(1), bounded by O(lgn)
			*/
			/// ------------------------------------------------------------------------------------ ///

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

			/// ------------------------------------------------------------------------------------ ///
			/*
			Going up the tree, swap the parents if need be to ensure the maxima is at the top (use after INSERTION.)
			Typical time is O(1), bounded by O(lgn)
			*/
			/// ------------------------------------------------------------------------------------ ///

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

			/// ------------------------------------------------------------------------------------ ///
			/*
			Going down the tree, assure that the heap is balanced with the minima at a parent P.
			Typical time is O(lgn)
			*/
			/// ------------------------------------------------------------------------------------ ///

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

			/// ------------------------------------------------------------------------------------ ///
			/*
			Going down the tree, assure that the heap is balanced with the maxima at a parent P.
			Typical time is O(lgn)
			*/
			/// ------------------------------------------------------------------------------------ ///

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

			/// ------------------------------------------------------------------------------------ ///
			/*
			Returns an integer index of the parent node of a child at position WHERE, 0 if no parent.
			*/
			/// ------------------------------------------------------------------------------------ ///

			return (where <= 0) ? 0 : ((where - 1) / 2);
		}

	public:

		Heap<T>(const int &reserveSizeMax, bool minAtTop) {

			/// ------------------------------------------------------------------------------------ ///
			/*
			reserveSizeMax - max amount of elements in the heap.
			minAtTop - true if mini heap, false if max heap. O(1) time.
			*/
			/// ------------------------------------------------------------------------------------ ///
			
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

			/// ------------------------------------------------------------------------------------ ///
			/*
			minAtTop - True if mini tree, false if max tree.
			An array of type T is passed and used to construct the heap.

			Typically takes O(n) time. On a basic analysis, it appears this would take 
			... O(nlgn) time, because you insert at lgn each time, but the time complexity 
			... can be written as a series that converges to n. Refer to MIT Heaps and Heap Sort. 
			*/
			/// ------------------------------------------------------------------------------------ ///

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

			/// ------------------------------------------------------------------------------------ ///
			/*
			Print the heap in an array / list like representation.
			*/
			/// ------------------------------------------------------------------------------------ ///

			std::cout << "[ ";
			for (auto member : this->heap) {
				std::cout << member << " ";
			}
			std::cout << "]\n";
		}

		void insert(T what) {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Inserts and then heapifies up using private functions.
			Typical time is O(lgn)
			*/
			/// ------------------------------------------------------------------------------------ ///

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

			/// ------------------------------------------------------------------------------------ ///
			/*
			Throws if empty tree, else returns max or min depending upon the tree type, THEN removes the top. O(1).
			*/
			/// ------------------------------------------------------------------------------------ ///

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

			/// ------------------------------------------------------------------------------------ ///
			/*
			Get the tree top WITHOUT popping. O(1).
			*/
			/// ------------------------------------------------------------------------------------ ///

			if (this->currentSize == 0) {
				// Tree is empty
				throw;
			}
			else {
				return this->heap[0];
			}
		}
};
