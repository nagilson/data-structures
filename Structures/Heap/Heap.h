#pragma once
#include <vector>
#include <iostream>

template <typename T>
class Heap{

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
				heapifyMinIns(where);
			}
			else {
				heapifyMaxIns(where);
			}
		}

		void heapifyMinIns(int where) {

			int parentLoc = parent(where);
			T parent = this->heap[parentLoc];
			T child = this->heap[where];

			if (parent <= child){
				return;
			}
			else {
				swap(parentLoc, where);
				heapifyMinIns(parentLoc);
			}
		}

		void heapifyMaxIns(int where) {

			int parentLoc = parent(where);
			T parent = this->heap[parentLoc];
			T child = this->heap[where];

			if (parent >= child) {
				return;
			}
			else {
				swap(parentLoc, where);
				heapifyMaxIns(parentLoc);
			}
		}

		void heapifyMinDel(int where) {

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
					heapifyMinDel(leftChildLoc);
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
						heapifyMinDel(rightChildLoc);
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
						heapifyMinDel(leftChildLoc);
					}
					else {
						return; // The property is valid.
					}
				}
			}
		}

		void heapifyMaxDel(int where) {

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
					heapifyMaxDel(leftChildLoc);
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
						heapifyMaxDel(rightChildLoc);
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
						heapifyMaxDel(leftChildLoc);
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

			this->capacity = reserveSizeMax - 1;
			this->heap.reserve(reserveSizeMax);
			this->currentSize = 0;
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

		void deleteRoot() {

			if (this->currentSize == 0) {
				// Tree is empty.
				return;
			}

			else {

				this->heap[0] = this->heap[this->currentSize -1];
				this->heap.pop_back();
				--(this->currentSize);


				if (this->minType == true) {
					heapifyMinDel(0);
				}

				else {
					heapifyMaxDel(0);
				}
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
