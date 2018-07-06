#pragma once
/// ------------------------------------------------------------------------------------ ///
/*
The following .h file includes an implementation of the hash table structure, using bucket nodes ...
and linear probing. Implemented cases: K = int, V = str, K = str, V = int.
*/
/// ------------------------------------------------------------------------------------ ///

#include <iostream>
#include <memory>
#include <vector>
#include <string>

template <typename K, typename V>
struct Bucket {

	/// ------------------------------------------------------------------------------------ ///
	/*
	Bucket class is a node / entry of the hash table. 
	Type K is for the key type, V for the value type. 
	K will be used for lookup. V should never point to a null object. 
	*/
	/// ------------------------------------------------------------------------------------ ///

	K key;
	V value;

	Bucket(K key, V value) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Normal bucket constructor.
		*/
		/// ------------------------------------------------------------------------------------ ///

		this->key = key;
		this->value = value;
	}

	Bucket() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Empty bucket constructor. We assume K is int, V is str.
		*/
		/// ------------------------------------------------------------------------------------ ///

		this->key = K(-1);
		this->value = V("");
	}

	void print() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Using std::cout, give a formatted view of the key and value of the bucket. 
		*/
		/// ------------------------------------------------------------------------------------ ///

		std::cout << "Key: " << this->key << " | Value: " << this->value << "\n";
	}

	bool isEmpty() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Return true if empty. -1 Means empty since start, -2 means emptied at some point in execution. 
		*/
		/// ------------------------------------------------------------------------------------ ///

		return (this->key == K(-1) || this->key == K(-2));
	}

};

template <typename K, typename V>
class hashTable {

	/// ------------------------------------------------------------------------------------ ///
	/*
	hashTable class with keys of type K (assumed int) and values V (assumed str.) 
	Enforces linear probing over chaining methods, and uses sub-struct Buckets to contain entries.
	The goal of a hashtable is to insert, find, and remove at O(1) time like an array. 

	We use a hashing function to change a key, K, into an integer index for the table, which allows us to access [hypothetically] ~O(1).
	Sometimes hash functions do not provide a perfect hash :: h(K) may == h(K2) even if K != k2...
		... Which is why we use linear probing, and thus worst time is O(n) but very unlikely.
	*/
	/// ------------------------------------------------------------------------------------ ///

	private:
		std::vector<Bucket<K, V>> table;
		const int size; // intialized size (aim to keep size around this point for optimal time complexity)
		int contains; // Actual used values in the table. 

		int hash(K key) {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Rudimentary hash function, modulus is applied to a key by the const size.
			If K was a string, we could provide specialization and use Berstein's hash.
			*/
			/// ------------------------------------------------------------------------------------ ///

			return key % this->size;
		}

	public:

		hashTable(const int sizeParam) : size(sizeParam), table(sizeParam, Bucket<K, V>()) {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Default initialization, initialization list lets us construct const member. 
			*/
			/// ------------------------------------------------------------------------------------ ///

			this->contains = sizeParam;
		}

		void insert(const K key, const V &value) {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Insert to the bucket. O(1) time if no collision. Else, possible O(n) time. 
			If the bucket is full, we will append to the bucket.
			This appending will slow down the overall speed of the hash table.
			*/
			/// ------------------------------------------------------------------------------------ ///

			const Bucket<K, V> insertion(key, value);
			int position = hash(key);

			if (this->table[position].isEmpty()) {
				this->table[position] = insertion;
				return; // No collision, so the insertion is complete at O(1)! 
			}
			else if (this->table[position].key == key) {
				return; // We've already inserted this entry.
			}
			else {
				// Collision
				++position;
				while (position < ((this->size) - 1)) {
					if (this->table[position].isEmpty()) {
						this->table[position] = insertion;
						return; // Entry inserted. 
					}
					else if (this->table[position].key == key) {
						return; // We've already inserted this entry.
					}
					else {
						++position; // The next slot is full. Continue. 
						continue;
					}
				}
				// If we haven't returned yet, then there aren't any open spaces.
				// We've now traversed ~O(n) regions, which is pretty uncool.
				++(this->contains);
				this->table.push_back(insertion);
			}
		}

		void remove(const K &key) {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Replace a bucket in the table vector with a "once used but now empty" bucket object.
			O(1) if no collision, else possible O(n).
			*/
			/// ------------------------------------------------------------------------------------ ///

			const Bucket<K, V> successor(-2, "nullptr");
			int position = hash(key);

			if (this->table[position].key == key) {
				// The key was placed without any collision.
				this->table[position] = successor;
				--(this->contains);
				return;
			}
			else {
				// Either the key doesn't exist, or the key was placed in collision.
				++position;
				while (position < ((this->size) - 1)) {
					if (this->table[position].isEmpty()) {
						return; // The key doesn't exist
					}
					else if (this->table[position].key == key) {
						// We've found the key. Delete it.
						this->table[position] = successor;
						--(this->contains);
						return;
					}
					else {
						// There's still more elements that could be key.
						++position;
						continue;
					}
				}
			}
			return; // Value isn't in the table.
		}

		V at(const K &key) {

			/// ------------------------------------------------------------------------------------ ///
			/*
			Returns the value at an index in the hash table, K.
			If the value doesn't exist, returns nullptr.
			*/
			/// ------------------------------------------------------------------------------------ ///

			int position = hash(key);

			if (key == this->table[position].key) {
				// No collision occured with this key.
				return (this->table[position].value);
			}

			else {
				// A collision occured with the key, so let's find it
				++position;
				while (position < (this->size) - 1) {
					if (this->table[position].isEmpty()) {
						// Key doesn't exist in the table. 
						std::cout << "Value isn't in table. RETURNS NULLPTR";
						return nullptr; // -1 : Empty, -2 : Once Empty, -3 : DNE 
					}
					else if (this->table[position].key == key) {
						// Found the key! 
						return this->table[position].value;
					}
					else {
						// Looking for more keys. 
						++(position);
						continue;
					}
				}
				std::cout << "Value isn't in the table. RETURNING NULLPTR.";
				return nullptr; // We've reached the end of the table, doesn't exist.
			}
		}

			int howManyEntries() {
				return this->contains;
			} 

			bool isEmpty() {
				return (this->contains == 0);
			}

			void print() {
				std::cout << "\n----------------------------\n" << \
					"Hash Table Starting Size: " << this->size << "\n";
				for (Bucket<K, V> bucket : this->table) {
					bucket.print();
				}
				std::cout << "----------------------------\n";
			}
};

template <typename V>
struct Bucket<std::string, V> {

	/// ------------------------------------------------------------------------------------ ///
	/*
	Bucket class is a node / entry of the hash table.
	Specialization where we let K = str.
	*/
	/// ------------------------------------------------------------------------------------ ///

	std::string key;
	V value;

	Bucket(std::string key, V value) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Normal bucket constructor.
		*/
		/// ------------------------------------------------------------------------------------ ///

		this->key = key;
		this->value = value;
	}

	Bucket() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Empty bucket constructor. We assume K is str, v is int.
		*/
		/// ------------------------------------------------------------------------------------ ///

		this->key = "**EMPTY";
		this->value = V(-1);
	}

	void print() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Using std::cout, give a formatted view of the key and value of the bucket.
		*/
		/// ------------------------------------------------------------------------------------ ///

		std::cout << "Key: " << this->key << " | Value: " << this->value << "\n";
	}

	bool isEmpty() {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Return true if empty. **EMPTY Means empty since start, ***EMPTY means emptied at some point in execution.
		*/
		/// ------------------------------------------------------------------------------------ ///

		return (this->key == "**EMPTY" || this->key == "***EMPTY" );
	}

};

template <typename V>
class hashTable<std::string, V>{

	/// ------------------------------------------------------------------------------------ ///
	/*
	hashTable class with keys of values V (assumed int.)
	Enforces linear probing over chaining methods, and uses sub-struct Buckets to contain entries.
	The goal of a hashtable is to insert, find, and remove at O(1) time like an array.

	We use a hashing function to change a key, K, into an integer index for the table, which allows us to access [hypothetically] ~O(1).
	Sometimes hash functions do not provide a perfect hash :: h(K) may == h(K2) even if K != k2...
	... Which is why we use linear probing, and thus worst time is O(n) but very unlikely.
	*/
	/// ------------------------------------------------------------------------------------ ///

private:
	std::vector<Bucket<std::string, V>> table;
	const int size; // intialized size (aim to keep size around this point for optimal time complexity)
	int contains; // Actual used values in the table. 

	int hash(std::string key) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Berstein's hash using binary shift. 
		*/
		/// ------------------------------------------------------------------------------------ ///
		std::hash<std::string> hasher;
		int index = std::abs((int)hasher(key) % (this->size));
		return index;
	}

public:

	hashTable(const int sizeParam) : size(sizeParam), table(sizeParam, Bucket<std::string, V>()) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Default initialization, initialization list lets us construct const member.
		*/
		/// ------------------------------------------------------------------------------------ ///

		this->contains = sizeParam;
	}

	void insert(const std::string key, const V &value) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Insert to the bucket. O(1) time if no collision. Else, possible O(n) time.
		If the bucket is full, we will append to the bucket.
		This appending will slow down the overall speed of the hash table.
		*/
		/// ------------------------------------------------------------------------------------ ///

		const Bucket<std::string, V> insertion(key, value);
		int position = hash(key);

		if (this->table[position].isEmpty()) {
			this->table[position] = insertion;
			return; // No collision, so the insertion is complete at O(1)! 
		}
		else if (this->table[position].key == key) {
			return; // We've already inserted this entry.
		}
		else {
			// Collision
			++position;
			while (position < ((this->size) - 1)) {
				if (this->table[position].isEmpty()) {
					this->table[position] = insertion;
					return; // Entry inserted. 
				}
				else if (this->table[position].key == key) {
					return; // We've already inserted this entry.
				}
				else {
					++position; // The next slot is full. Continue. 
					continue;
				}
			}
			// If we haven't returned yet, then there aren't any open spaces.
			// We've now traversed ~O(n) regions, which is pretty uncool.
			++(this->contains);
			this->table.push_back(insertion);
		}
	}

	void remove(const std::string &key) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Replace a bucket in the table vector with a "once used but now empty" bucket object.
		O(1) if no collision, else possible O(n).
		*/
		/// ------------------------------------------------------------------------------------ ///

		const Bucket<std::string, V> successor("***EMPTY", 0);
		int position = hash(key);

		if (this->table[position].key == key) {
			// The key was placed without any collision.
			this->table[position] = successor;
			--(this->contains);
			return;
		}
		else {
			// Either the key doesn't exist, or the key was placed in collision.
			++position;
			while (position < ((this->size) - 1)) {
				if (this->table[position].isEmpty()) {
					return; // The key doesn't exist
				}
				else if (this->table[position].key == key) {
					// We've found the key. Delete it.
					this->table[position] = successor;
					--(this->contains);
					return;
				}
				else {
					// There's still more elements that could be key.
					++position;
					continue;
				}
			}
		}
		return; // Value isn't in the table.
	}

	V at(const std::string &key) {

		/// ------------------------------------------------------------------------------------ ///
		/*
		Returns the value at an index in the hash table, K.
		If the value doesn't exist, returns nullptr.
		*/
		/// ------------------------------------------------------------------------------------ ///

		int position = hash(key);

		if (key == this->table[position].key) {
			// No collision occured with this key.
			return (this->table[position].value);
		}

		else {
			// A collision occured with the key, so let's find it
			++position;
			while (position < (this->size) - 1) {
				if (this->table[position].isEmpty()) {
					// Key doesn't exist in the table. 
					std::cout << "Value isn't in table. RETURNS NULLPTR";
					return nullptr; // ** : Empty, *** : Once Empty, -3 : DNE 
				}
				else if (this->table[position].key == key) {
					// Found the key! 
					return this->table[position].value;
				}
				else {
					// Looking for more keys. 
					++(position);
					continue;
				}
			}
			std::cout << "Value isn't in the table. RETURNING NULLPTR.";
			return nullptr; // We've reached the end of the table, doesn't exist.
		}
	}

	int howManyEntries() {
		return this->contains;
	}

	bool isEmpty() {
		return (this->contains == 0);
	}

	void print() {
		std::cout << "\n----------------------------\n" << \
			"Hash Table Starting Size: " << this->size << "\n";
		for (Bucket<std::string, V> bucket : this->table) {
			bucket.print();
		}
		std::cout << "----------------------------\n";
	}
};

