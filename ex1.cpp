// FI MUNI - PB153
// Filip Lux
// testing speed of priority queue


#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <stdlib.h>
#include <time.h>

#define TEST_INSERT_ITER 10000000


template <typename T, int N >
class PriorityBufferSet {

	std::set<T> buffer;
	int size;

public:

	PriorityBufferSet() : size(0) {}

	void const insert( const T & item ) {
		buffer.insert( item );
		if (buffer.size() > N)
			buffer.erase(buffer.begin());
	}
	/**
	 * remove value of largest item 
	 */

	void remove() {
		if (buffer.size() > 0)
			buffer.erase(--buffer.end());
		else
			std::cout << "Buffer is already empty.\n";
	}

	/**
	 * returns largest item
	 */
	T top () {
		if (buffer.size() > 0) {
			T top = *(--buffer.end());
			return top;
		}

		std::cout << "There is no item in the buffer.\n";
		return -1;

	}


	void print () {

		std::cout << "buffer contains: ";


		for (auto& x : buffer) {
		//for (std::set<T>::iterator it = buffer.begin(); it != buffer.end(); ++it) {
			std::cout << int(x) << " ";
		}
		std::cout << "\n";
	}

	void testBuffer () {

		clock_t t;
		t = clock();
		long long i;

		for (i = 0; i < TEST_INSERT_ITER; ++i) {
			this->insert(i);
		}
		t = clock() - t;

		std::cout << "set buffer size " << N << ": ";
		std::cout << "run in seconds: " << float(t)/CLOCKS_PER_SEC << "\n";
	}


};

template <typename T, int N >
class PriorityBufferVec {

	std::vector<T> buffer;
	int size;

public:

	PriorityBufferVec() : size(0) {}

	void insert( const T & item ) {

		buffer.push_back( item );
		std::sort(buffer.begin(), buffer.end(), std::greater<T>());
		if (buffer.size() > N )
			buffer.pop_back();

	}

	T top () {
		if ( buffer.size() < 1 ) {

			std::cout << "There is no item in the buffer.\n";
			return -1;
		}
		return buffer[buffer.size()-1];
	}

	void  remove () {

		if ( buffer.size() < 1 ) {
			std::cout << "There is no item to remove.\n";

		}
		else {
			buffer.pop_back();
			size--;
		}


	}

	void print () {

		std::cout << "buffer contains: ";

		for (int i = 0; i < size; i++) {
			std::cout << buffer[i] << " ";
		}
		std::cout << "\n";
	}

	void testBuffer () {

		clock_t t;
		t = clock();
		long long i;

		for (i = 0; i < TEST_INSERT_ITER; ++i) {
			this->insert(i);
		}
		t = clock() - t;

		std::cout << "vector buffer size " << N << ": ";
		std::cout << "run in seconds: " << float(t)/CLOCKS_PER_SEC << "\n";
	}
};



void automaticTest () {
	

	PriorityBufferVec<long long, 5> vbuffer5;
	PriorityBufferVec<long long, 10> vbuffer10;
	PriorityBufferVec<long long, 10000> vbuffer10_4;

	PriorityBufferSet<long long, 5> sbuffer5;
	PriorityBufferSet<long long, 10> sbuffer10;
	PriorityBufferSet<long long, 10000> sbuffer10_4;

	sbuffer5.testBuffer ();
	sbuffer10.testBuffer ();
	sbuffer10_4.testBuffer ();


	vbuffer5.testBuffer ();
	vbuffer10.testBuffer ();
	vbuffer10_4.testBuffer ();
}

void manualTestVec () {


	PriorityBufferVec<int, 5> buffer;
	std::string cmd;
	int number;

	while (true) {

		std::cin >> cmd;

		if (cmd == "insert") {
			std::cin >> number;
			buffer.insert(number);
		}

		else if ( cmd == "top") {
			number = buffer.top();
			std::cout << "Top number is " << number << "\n";
		}

		else if ( cmd == "remove" ) {
			buffer.remove();
		}
		else if (cmd == "exit" ) {
			break;
		}
		else {
			std::cout << "wrong argument. \n Type insert | top | remove | exit \n";
		}
		
		buffer.print();

	}
}

void manualTestSet () {


	PriorityBufferSet<int, 5> buffer;
	std::string cmd;
	int number;

	while (true) {

		std::cin >> cmd;

		if (cmd == "insert") {
			std::cin >> number;
			buffer.insert(number);
		}

		else if ( cmd == "top") {
			number = buffer.top();
			std::cout << "Top number is " << number << "\n";
		}

		else if ( cmd == "remove" ) {
			buffer.remove();
		}
		else if (cmd == "exit" ) {
			break;
		}
		else {
			std::cout << "wrong argument. \n Type insert | top | remove | exit \n";
		}
		
		buffer.print();

	}
}

int main () {

	//manualTestSet();

	//automatic test
	automaticTest();



}