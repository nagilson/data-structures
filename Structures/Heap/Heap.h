#pragma once
#include <vector>
#include <iostream>

template <typename T>
class Heap{

	private:
		std::vector<T> heap;
		int capacity;
		int currentSize;

	public:
		Heap<T>(const int &reserveSizeMax) : heap(reserveSizeMax, T()){
			this->capacity = reserveSizeMax;
			this->currentSize = 0;
		}

		void print() {
			std::cout << "[ ";
			for (auto member : this->heap) {
				std::cout << member << " ";
			}
			std::cout << "]\n";
		}
};
