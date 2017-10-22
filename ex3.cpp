#define BRICK_BENCHMARK_REG
#define BRICK_BENCHMARK_MAIN

/* ./bench category:stack | gnuplot > soubor.pdf */

#include <brick-benchmark>
#include <stack>
#include <deque>
#include <list>
#include <random>


using namespace brick;

struct Memory : benchmark::Group
{

	std::list<int> lis;
    std::vector<int> vec;


    Memory()
    {
        x.type = benchmark::Axis::Quantitative;
        x.name = "items";
        x.min = 1000;
        x.max = 10000;
        x.step = 1000;

        //x.log = True;
        //x.step = cbrt(2);

        y.type = benchmark::Axis::Qualitative;
        y.name = "implementation";
        y.min = 1;
        y.max = 2;


        y._render = []( int i )
        {
            switch ( i )
            {
                case 1: return "vector";
                case 2: return "list";
            }
        };
    }

    void setup (int _p, int _q) {
    	p = _p;
    	q = _q;
    	this->vec.reserve(p);
    	for (int i = 0; i < p; i++) {
    		this->vec.insert(i);
    	}
    }

    std::string describe() { return "category:memory"; }

    BENCHMARK( benchmem )
    {
        switch ( q )
        {
            case 1: bench_vector_random(); break;
            case 2: bench_list(); break;
        }
    }

    void bench_vector_random()
    {
    	//define container
    	for ( int i = 0; i < p; ++i ) {
    		std::mt19937 number = std::mt19937(); //arc4random
            int a = this->vec[number % p];
        }
    }

    void bench_list()
    {
    	//define container
    }


};
