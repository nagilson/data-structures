#pragma once
#include <vector>
#include <iostream>

template <typename T>
class Heap{

	private:
		std::vector<T> heap;
		bool minType; // If false, max type.
		int capacity;
		int currentSize;
		 
		void swap(int pos1, int pos2) {
			T temp = this->heap[pos1];
			this->heap[pos1] = this->heap[pos2];
			this->heap[pos2] = temp;
		}
		
		void validateInterface(int where) {
			if (this->minType) {
				validateMin(where);
			}
			else {
				validateMax(where);
			}
		}

		void validateMin(int where) {

			int parentLoc = parent(where);
			T parent = this->heap[parentLoc];
			T child = this->heap[where];

			if (parent <= child){
				return;
			}
			else {
				swap(parentLoc, where);
				validateMin(parentLoc);
			}
		}

		void validateMax(int where) {

			int parentLoc = parent(where);
			T parent = this->heap[parentLoc];
			T child = this->heap[where];

			if (parent >= child) {
				return;
			}
			else {
				swap(parentLoc, where);
				validateMax(parentLoc);
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
				std::cout << "\n-------\nERR: The heap is full, or insertion too big.\n-------\n";
				return;
			}
			else {
				this->heap.push_back(what);
				validateInterface(currentSize);
				++(this->currentSize);
			}
		}


};
