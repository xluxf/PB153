// implemetation of hashtables for PB153
// author Filip Lux

#ifndef HASHTABLES_H
#define HASHTABLES_H

#include <unordered_set>
#include <algorithm>
#include <set>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include <functional>
#include <iostream>

#define TEST_INSERT_ITER 10000000

/**
 * hastable used link-listed buckets
 */
template <typename V>
class HashTableLL {

	const size_t TABLE_SIZE = TEST_INSERT_ITER * 0.07;

	struct HashNode {

		const V value;
		HashNode * next;

		HashNode () : next(NULL) {}
		HashNode (const V & value) : value(value), next(NULL) {}

    };

	HashNode ** table;

public:

	std::string name = "linked-list";

	HashTableLL () {
		table = new HashNode * [TABLE_SIZE];
		for (size_t i = 0; i < TABLE_SIZE; ++i) 
			table[i] = NULL;

	}

	void insert(const V & value) {
		if (!find(value)) {
			const size_t key = getHash(std::hash<V> {} (value));
			auto newNode = new HashNode(value);

			if (table[key] == NULL)
				table[key] = newNode;
			else {

				HashNode * ptr = table[key];

				while ( ptr->next != NULL ) {
					ptr = ptr->next;
				}

				ptr->next = newNode;

			}

		}
	}

	bool find(const V & value) {
		size_t key = getHash(std::hash<V> {} (value));

		HashNode * ptr = table[key];
		while (ptr != NULL ) {
			if (ptr->value == value )
				return true;
			ptr = ptr->next;
		}
		return false;

	}

	void erase(const V & value) {
		size_t key = getHash(std::hash<V> {} (value));

		if (find(value)) {

			HashNode * ptr = table[key]; //it is not NULL, because the value is in the table

			if (ptr->value == value) {
				auto tmp = ptr->next;
				delete ptr;
				table[key] = tmp;
			}
			else {
				while (ptr->next != NULL ) {
					auto tmp = ptr->next;
					if (tmp->value == value ) {
						ptr->next = tmp->next;
						delete tmp;
						break;
					}
					else
						ptr = ptr->next;
				}
			}
		}	

	}

	inline size_t getHash ( size_t key ){
		return key % TABLE_SIZE;
	}

	~HashTableLL () {
		for (size_t i = 0; i < TABLE_SIZE; ++i) {
			HashNode * ptr = table[i];
			while (ptr != NULL) {
				HashNode * tmp = ptr;
				ptr = ptr->next;
				delete  tmp;
			}
		}
		delete[] table;
	}

	void print() {

		std::cout << "Table contains: \n";
		for (size_t i = 0; i < TABLE_SIZE; i++) {
			
			if (table[i] != NULL) {

				std::cout << i << ": ";

				HashNode * ptr = table[i];
				do {
					std::cout << ptr->value << " - ";
					ptr = ptr->next;
				} while (ptr != NULL);
				std::cout << "\n";
			}
		}
	}

	void printName () {
		std::cout << name << ": ";
	}

};

/**
 * hastable used probing and rehashing
 */
template <typename T>
class HashTableLPR {

	const size_t INIT_SIZE = 128;


public:

	std::string name = "linear probing, rehashing";

	std::vector<std::pair<bool, T> > table;
	size_t size;
	size_t free;

	HashTableLPR() {

		std::pair< bool, T> empty;
		empty.first = false;


		for (size_t i = 0; i < INIT_SIZE; ++i) {
			table.push_back(empty);
		}

		size = INIT_SIZE;
		free = size_t(INIT_SIZE*0.4);

	}

	~HashTableLPR() {}

	void insert ( T & item ) {

		if ( !find(item) ) {

			size_t key = getHash(std::hash<T> {} (item));

			while ( table[key].first != false) {
				key = getHash(key + 1);
			}
			table[key].first = true;
			table[key].second = item;
			--free;
			if (free == 0) {
				rehash();
			}
		}

	}

	bool find ( T & item) {
		size_t key = getHash(std::hash<T> {} (item));

		while (table[key].first != false) {
			if (table[key].second == item) {
				return true;
			}
			key = getHash(key + 1);
		}
		return false;
	}

	inline size_t getHash(const size_t & key) {
		return key % size;
	}

	void erase( T & item ) {

		size_t key = getHash(std::hash<T> {} (item));

		while ( table[key].first != false) {
			if ( table[key].second == item) {
				table[key].first = false;
				break;
			}
			key = getHash(key + 1);
		}
	}

	void print() {

		std::cout << "Table contains: \n";
		for (size_t i = 0; i < size; i++) {
			
			if (table[i].first != false) {
				std::cout << i << ": " << table[i].second  << "\n";
			}
		}
		std::cout << "free : " << free << ", size: " << size << ".\n";
	}

	void printName () {
		std::cout << name << ": ";
	}

private:
	void rehash() {

		std::vector< std::pair<bool, T> > oldTable;

		size *= 2;
		free = size_t(size*0.4);
		table.reserve(size);

		std::pair< bool, T> empty;
		empty.first = false;

		std::pair< bool, T> item;
		item.first = true;

		for (auto it = table.begin() ; it != table.begin() + size/2; ++it) {
			if ((*it).first == false)
				oldTable.push_back(empty);
			else {
				item.second = (*it).second;
				oldTable.push_back( item );
			}
			(*it).first = false;
		}

		for (auto it = table.begin() + size/2 ; it != table.begin() + size; ++it) {
			table.push_back(empty);
		}

		for (auto it = oldTable.begin() ; it != oldTable.begin() + size/2; ++it) {
			if ( (*it).first != false) {
				insert( (*it).second );
			}
		}

	}

};


/**
 * hastable used std::set
 */
template <typename T>
class HashTableS {

	std::set<T> table;

public:

	std::string name = "set";

	void insert( T & item ) {
		table.insert(item);
	}

	bool find( const T & item ) {
		typename std::set<T>::const_iterator result = table.find (item);

		if ( result == table.end() )
			return false;
		return true;
	}

	void print() {

		std::cout << "table contains: ";
		for (auto& x : table) {
			std::cout << int(x) << " ";
		}
		std::cout << "\n";
	}

	void erase( const T & item) {
		table.erase(item);

	}

	void printName () {
		std::cout << name << ": ";
	}
};

/**
 * hastable used std::unordered_set
 */
template <typename T>
class HashTableUS {

	std::unordered_set<T> table;

public:

	std::string name = "unordered_set";

	void insert( T & item ) {
		table.insert( T(item) );
	}

	bool find( const T & item ) {
		typename std::unordered_set<T>::const_iterator result = table.find (item);

		if ( result == table.end() )
			return false;
		return true;
	}

	void print() {

		std::cout << "table contains: ";
		for (auto& x : table) {
			std::cout << int(x) << " ";
		}
		std::cout << "\n";
	}

	void erase (const T & item ) {
		table.erase( item );
	}

	void printName () {
		std::cout << name << ": ";
	}

};

#endif // HASHTABLES_H