#pragma once
/// ------------------------------------------------------------------------------------ ///
/*
The following .h file includes an implementation of the AVL tree, a modified version of the 
BST included in the project. 
*/
/// ------------------------------------------------------------------------------------ ///

#include "stdafx.h" //You may want to include this if you create a VS PRJ with cmake.
#include <iostream>

template <typename T>
struct Node {

	/// ------------------------------------------------------------------------------------ ///
	/*
	A Node struct that contains a left child and a right child note, which would normally be assigned to nullptr.
	*/
	/// ------------------------------------------------------------------------------------ ///

	T data;
	Node<T> * left;
	Node<T> * right;
	Node<T> * parent;
	int balance;

	Node<T>(T input) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Basic Node constructor, takes an input value of type T for the data held inside of the Node. L^R are nullptr.
		*/
		/// ------------------------------------------------------------------------------------ ///

		this->data = input;
		this->right = nullptr;
		this->left = nullptr;
		this->parent = nullptr;
		this->balance = 0;
	}

};

template <typename T>
class AVLTree {

	/// ------------------------------------------------------------------------------------ ///
	/*
	This is an implementation of the AVL Tree.
	The AVL tree is a binary tree that is self-balancing. 
	The tree uses what are called "rotations" (really tree-realignment, not rotations)
	... to balance itself automatically.

	This assures O(lgn) time instead of O(n) time, which is the goal of a binary tree.
	We do this by assuring that a height / balance factor is always not greater than +-1. 
	*/
	/// ------------------------------------------------------------------------------------ ///

private:

	Node<T> * root;
	int length;

	void deletePartition(Node<T> *& where) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Recursively delete subtrees of the tree.
		*/
		/// ------------------------------------------------------------------------------------ ///


		if (where->left) {
			deletePartition(where->left);
		}
		if (where->right) {
			deletePartition(where->right);
		}
		delete where;
		--(this->length);
		return;
	}

	void printPartition(Node<T> *& where) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Recursively print each node in the tree, in order from the leftmost node to the rightmost node.
		*/
		/// ------------------------------------------------------------------------------------ ///

		if (where->left) {
			printPartition(where->left);
		}
		std::cout << where->data << " ";
		if (where->right) {
			printPartition(where->right);
		}

	}

	Node<T> * findNode(Node<T>* &where, T &what) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Find the node starting from a parent where, containing content T what.
		Return the pointer to said node containing what.
		*/
		/// ------------------------------------------------------------------------------------ ///


		if (where->data == what) {
			return where;
		}
		else {
			if (what > where->data) {
				if (!(where->right)) {
					return nullptr;
				}
				else {
					return findNode(where->right, what);
				}
			}
			else {
				if (!(where->left)) {
					return nullptr;
				}
				else {
					return findNode(where->left, what);
				}
			}
		}
	}

	T prepareSuccessor(Node<T>* &where) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Find the leftmost node of the right subtree at where, and return its content.
		The leftmost RST node can only have a right child, and MUST follow the properties of where.
		A right subtree will always exist at where because this is only called when a deletion node
		... has two children.
		This function maintains all of the pointers needed, because it DELETES the node with
		... the content we want to replace where with.
		*/
		/// ------------------------------------------------------------------------------------ ///


		Node<T> *current = where->right;
		// Find the leftmost child in the right subtree
		// ... that is the successor.
		if (current->left) {
			while (current->left->left) {
				current = current->left;
			}
		}

		T value;
		if (current->left) {
			value = current->left->data;
		}
		else {
			value = current->data;
		}

		if (where->right->right) {
			where->right = where->right->right;
		}

		Node<T> *nodeToDel;
		nodeToDel = current->left;
		if (current->left) {
			// current->left need not exist if we are deleting the root 
			if (current->left->right) {
				current->left->right->parent = current;
				current->left = current->left->right;
			}
		}
		delete nodeToDel;
		return value;
	}

	void deleteNode(T what) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Remove a node in the tree that is not the root.
		*/
		/// ------------------------------------------------------------------------------------ ///

		// Find the node BEFORE the node we need to delete.
		// (Why? we have to set that node's pointer unless there are 2 children)
		Node<T> *target = findNode(this->root, what);
		Node<T> *prior = target->parent;

		if (prior == nullptr) {
			// The node to erase doesn't exist.
			return;
		}

		else {
			// We've got to erase the node. 

			// Find the location of the node to delete.
			Node<T> *nodeToDel;
			bool left = false;

			if (prior->left) {
				if (prior->left->data == what) {
					nodeToDel = prior->left;
					left = true;
				}
				else {
					nodeToDel = prior->right;
				}
			}
			else {
				nodeToDel = prior->right;
			}

			// Managing Children, then deletion process
			if (!(nodeToDel->left || nodeToDel->right)) {
				// The Node has no children...
				// First, we set the pointer to our erased node to nullptr.
				if (left) {
					prior->left = nullptr;
				}
				else {
					prior->right = nullptr;
				}
				delete nodeToDel;
			}

			else if ((nodeToDel->left && nodeToDel->right)) {
				// The node to erase has 2 children...
				T successor = prepareSuccessor(nodeToDel);
				// prepareSuccessor automatically sets the
				// successorsPrior pointer to successor to nullptr.
				nodeToDel->data = successor;
			}
			else if (nodeToDel->left) {
				// The node has 1 child, and it's to the left.
				nodeToDel->left->parent = prior;
				prior->right = nodeToDel->left;
				delete nodeToDel;
			}
			else {
				// The node has 1 child, and it's to the right.
				nodeToDel->right->parent = prior;
				prior->left = nodeToDel->right;
				delete nodeToDel;
			}
		}
	}

	void copyTree(Node<T>* &copyTreeRoot, Node<T>* otherRoot) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Recursively call copyTree to copy data into a NEW tree at copyTreeRoot.
		*/
		/// ------------------------------------------------------------------------------------ ///

		if (!(otherRoot)) {
			copyTreeRoot = nullptr;
		}
		else {
			copyTreeRoot = new Node<T>(otherRoot->data);
			copyTreeRoot->left = otherRoot->left;
			copyTreeRoot->right = otherRoot->right;
			copyTreeRoot->balance = otherRoot->balance;
			copyTreeRoot->parent = otherRoot->parent;
			copyTree(copyTreeRoot->left, otherRoot->left);
			copyTree(copyTreeRoot->right, otherRoot->right);
		}
	}

public:

	void print() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Check if the tree is null, if not, setup the boundaries of the structure (< and >)
		Calls a recursive private function to print nodes in order.
		*/
		/// ------------------------------------------------------------------------------------ ///


		if (!(this->root)) {
			std::cout << "nullptr";
		}
		else {
			std::cout << "\n---\nRoot: " << (this->root->data);
			std::cout << "\nLength: " << this->length;
			std::cout << "\n< ";
			int len = this->length;
			printPartition(this->root);
			std::cout << ">\n---\n\n";
		}
	}

	void erase(T what) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Find and erase a node in the tree with content what.
		Returns instantly if node doesn't exist.
		*/
		/// ------------------------------------------------------------------------------------ ///


		if (this->root == nullptr) {
			// The tree doesn't exist.
			return;
		}
		if (this->root->data == what) {
			// Generic Node deletion requires a prior node...
			if (!(root->left || root->right)) {
				// No Children
				delete this->root;
				--(this->length);
				this->root = nullptr;
			}
			else if (this->root->left && this->root->right) {
				// Root has 2 children:
				T successor = prepareSuccessor(this->root);
				this->root->data = successor;
			}
			else if (this->root->left) {
				// Root has 1 child to the left.
				Node<T> *nodeToDel = this->root;
				this->root = this->root->left;
				delete nodeToDel;
			}
			else {
				// Root has 1 child to the right.
				Node<T> *nodeToDel = this->root;
				this->root = this->root->right;
				delete nodeToDel;
			}
			--(this->length);
		}
		else {
			deleteNode(what);
			--(this->length);
		}

	}

	void insert(T data) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Add a node with content data into the tree at the proper position.
		*/
		/// ------------------------------------------------------------------------------------ ///


		Node<T> *next = new Node<T>(data);
		if (this->root == nullptr) {
			this->root = next;
			++(this->length);
		}
		else {
			Node<T> *current = this->root;
			do {
				if (next->data == current->data) {
					break; // No repeats in this binary tree. 
				}
				else if (next->data > current->data) {
					if (!(current->right)) {
						next->parent = current;
						current->right = next;
						++(this->length);
						break;
					}
					current = current->right;
					continue;
				}
				else {
					if (!(current->left)) {
						next->parent = current;
						current->left = next;
						++(this->length);
						break;
					}
					current = current->left;
					continue;
				}
			} while (true);
		}
	}

	T getRoot() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Return the root node of the tree, of type Node.
		*/
		/// ------------------------------------------------------------------------------------ ///
		if (this->root) {
			return this->root;
		}
		else {
			throw;
		}
	}

	int getLength() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Returns the length of the tree, of type int.
		*/
		/// ------------------------------------------------------------------------------------ ///

		return this->length;

	}

	Node<T>* find(T what) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Basically a function wrapper to a private function that recursively finds a node.
		Returns the location of a node with content what, nullptr if DNE.
		*/
		/// ------------------------------------------------------------------------------------ ///


		if (!(this->root)) {
			return nullptr;
		}
		else {
			return findNode(this->root, what);
		}

	}

	void deleteTree() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Destruct each node in the tree. Should be optimized later with unique_ptr...
		*/
		/// ------------------------------------------------------------------------------------ ///

		// If tree is null:
		if (!(this->root)) {
			return;
		}
		else {
			deletePartition(this->root);
			this->root = nullptr;
		}

	}

	AVLTree<T>() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Basic constructor, sets the length to 0 and the root to a nullptr.
		*/
		/// ------------------------------------------------------------------------------------ ///

		this->root = nullptr;
		this->length = 0;

	}

	~AVLTree<T>() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Very simple destructor, calls the deleteTree function.
		*/
		/// ------------------------------------------------------------------------------------ ///

		deleteTree();

	}

	AVLTree<T>(const AVLTree<T> &other) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Copy constructor, calls copyTree.
		*/
		/// ------------------------------------------------------------------------------------ ///

		if (!(other.getRoot())) {
			this->root = nullptr;
		}
		else {
			copyTree(this->root, (other.getRoot()));
		}

	}

	const AVLTree<T>& operator=(const AVLTree &other) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Reassignment operator, turns the tree into other. (DEEP)
		*/
		/// ------------------------------------------------------------------------------------ ///

		if (this != &other) {
			if (this->root) {
				this->deleteTree();
			}
			if (!(other.root)) {
				this->root = nullptr;
			}
			else {
				copyTree(this->root, (other.root));
			}
		}
		return *this;
	}

};
