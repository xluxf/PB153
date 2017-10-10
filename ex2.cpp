// FI MUNI - PB153
// Filip Lux
// testing implementations of stack


#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <stdlib.h>
#include <time.h>

#define BRICK_BENCHMARK_REG
#define BRICK_BENCHMARK_MAIN

#include <brick-benchmark>

template <typename T>
class StackVector {
	std::vector<T> * stack;

	StackVector() {
		stack = new std::vector<T>();
	}

	void insert(const T & item) {
		stack.push_back(item);
	}

	T remove() {
		T result = stack.back();
		stack.pop_back();
		return result;
	}

};
