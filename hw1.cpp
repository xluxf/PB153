// FI MUNI - PB153
// Filip Lux
// implementing hash function


#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <set>
#include <stdlib.h>
#include <time.h>
#include <functional>

#define TEST_INSERT_ITER 10000000
#define TESTED_TYPE float
#define C 0.7


/**
 * hastable used link-listed buckets
 */
template <typename V>
class HashTableLL {

	const size_t TABLE_SIZE = TEST_INSERT_ITER * C;

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
		if (true or !find(value)) {
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
template <typename T, int ALPHA>
class HashTableLPR {

	const size_t INIT_SIZE = 100;


public:

	std::string name = "linear probing, rehashing, alpha=";

	std::vector<T> * table;
	size_t size;
	size_t free;

	HashTableLPR() {


		for (size_t i = 0; i < INIT_SIZE; ++i) {
			tmpTable.insert(NULL);
		}

		T * tmpTable = new T[INIT_SIZE];
		for (size_t i = 0; i < INIT_SIZE; ++i) {
			tmpTable[i] = 0;
		}
		size = INIT_SIZE;
		free = size_t(INIT_SIZE*ALPHA/100);
		table = &tmpTable;

	}

	~HashTableLPR() {
		delete[] *table;
	}

	void insert ( const T & item ) {

		if ( !find(item) ) {

			size_t key = getHash(std::hash<T> {} (item));

			while ((*table)[key] != 0) {
				key = getHash(key + 1);
			}
			(*table)[key] = item;
			--free;
			if (free == 0) {
				rehash();
			}
		}

	}

	bool find (const T & item) {
		size_t key = getHash(std::hash<T> {} (item));

		while ((*table)[key] != 0) {
			if ((*table)[key] == item) {
				return true;
			}
			key = getHash(key + 1);
		}
		return false;
	}

	inline size_t getHash(const size_t & key) {
		return key % size;
	}

	void print() {

		std::cout << "Table contains: \n";
		for (size_t i = 0; i < size; i++) {
			
			if ((*table)[i] != 0) {
				std::cout << i << ": " << (*table)[i]  << "\n";
			}
		}
		std::cout << "free : " << free << ", size: " << size << ".\n";
	}

	void printName () {
		std::cout << name << ALPHA << "%" << ": ";
	}

private:
	void rehash() {
		size *= 2;
		free = size_t(size*ALPHA/100);

		T * oldTable = *table;

		T * newTable = new T[size];

		for (size_t i = 0; i < size; ++i ) {
			newTable[i] = 0;
		}

		table = &newTable;

		for (size_t i = 0; i < size/2; i++) {
			if (oldTable[i] != 0) {
				insert( oldTable[i] );
			}
		}

		delete[] oldTable;

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

	void printName () {
		std::cout << name << ": ";
	}

};

template <typename T, typename INPUT_TYPE>
void manualTest () {

	T table;

	std::string cmd;
	INPUT_TYPE number;

	while (true) {

		std::cout << ">> ";

		std::cin >> cmd;

		if (cmd == "insert" || cmd == "i") {
			std::cin >> number;
			table.insert(number);
			table.print();
		}

		else if ( cmd == "find" || cmd == "f") {
			std::cin >> number;
			if (table.find(number))
				std::cout << number << " is in table.\n";
			else
				std::cout << number << " is not there.\n";
		}

		else if ( cmd == "print" || cmd == "p") {
			table.print();
		}

		else if (cmd == "exit" || cmd == "e") {
			break;
		}
		else {
			std::cout << "Wrong argument. Type insert | find | print | exit \n";
		}
	}
}

template <typename T, typename I>
void automaticTest () {

	T table;

	table.printName();

	srand ( time(NULL) );

	long long i;
	clock_t t;
	t = clock();

	for (i = 0; i < TEST_INSERT_ITER; ++i) {
		I number = rand();
		table.insert(number);
	}
	t = clock() - t;


	std::cout << float(t)/CLOCKS_PER_SEC << " s \n";

}

void benchmark () {

	std::cout << "Benchmark of hash tables\n\n";

	std::cout << "tested type: " << "float" << "\n";
	std::cout << "number of inserted objects: " << TEST_INSERT_ITER << "\n\n";


	automaticTest < HashTableS<TESTED_TYPE> , TESTED_TYPE > ();
	automaticTest < HashTableUS<TESTED_TYPE> , TESTED_TYPE > ();
	automaticTest < HashTableLL<TESTED_TYPE> , TESTED_TYPE > ();
	automaticTest < HashTableLPR<TESTED_TYPE, 40> , TESTED_TYPE > ();



}

int main () {

	benchmark();
	//manualTest < HashTableLPR<TESTED_TYPE, 70> , TESTED_TYPE>();
	//manualTest < HashTableLPR<TESTED_TYPE, 40> , TESTED_TYPE>();

	return 0;
}