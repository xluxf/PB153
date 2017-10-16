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

/* ./bench test:insert | gnuplot > soubor.pdf */

struct stack : benchmark::Group
{
    SelfTest()
    {
        x.type = Axis::Quantitative;
        x.name = "outer";
        x.unit = "iter";
        x.normalize = Axis::Div;

        y.type = Axis::Quantitative;
        y.name = "inner";
        y.unit = "k-iter";
        y.min =      800000;
        y.max =     1600000;
        y.unit_div =   1000;
        y.log = true;
        y.step = 2;
    }

    virtual ~SelfTest() {}

    std::string describe() { return "category:selftest"; }

/**
    BENCHMARK(delay)
    {
        for ( int i = 0; i < p; ++i )
            for ( int j = 0; j < q; ++j );
    }
*/

//hw2a
//hw2b

    BENCHMARK(insert) {
        switch ( q ) {
            case 1:
        }
    }
};

struct BFS : benchmark::Group
{
    BFS()
    {
        x.type = Axis::Quantitative;
        x.name = "outer";
        x.unit = "iter";
        x.normalize = Axis::Div;

        y.type = Axis::Quantitative;
        y.name = "inner";
        y.unit = "k-iter";
        y.min =      800000;
        y.max =     1600000;
        y.unit_div =   1000;
        y.log = true;
        y.step = 2;
    }

    virtual ~SelfTest() {}

    std::string describe() { return "category:selftest"; }

/**
    BENCHMARK(delay)
    {
        for ( int i = 0; i < p; ++i )
            for ( int j = 0; j < q; ++j );
    }
*/

//hw2a
//hw2b

    BENCHMARK(insert) {
        switch ( q ) {
            case 1:
        }
    }
};

