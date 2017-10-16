#define BRICK_BENCHMARK_REG
#define BRICK_BENCHMARK_MAIN

/* ./bench category:stack | gnuplot > soubor.pdf */

#include <brick-benchmark>
#include <stack>
#include <deque>
#include <list>

using namespace brick;

struct Stack : benchmark::Group
{
    Stack()
    {
        x.type = benchmark::Axis::Quantitative;
        x.name = "items";
        x.min = 1000;
        x.max = 5000;
        x.step = 1000;

        y.type = benchmark::Axis::Qualitative;
        y.name = "implementation";
        y.min = 1;
        y.max = 3;
        y._render = []( int i )
        {
            switch ( i )
            {
                case 1: return "vector";
                case 2: return "deque";
                case 3: return "list";
            }
        };
    }

    std::string describe() { return "category:stack"; }

    BENCHMARK( insert )
    {
        switch ( q )
        {
            case 1: do_insert< std::vector >(); break;
            case 2: do_insert< std::deque >(); break;
            case 3: do_insert< std::list >(); break;
        }
    }

    template< template< typename, typename > class C >
    void do_insert()
    {
        //using container = C< int, std::allocator< int > >;
        std::stack< int, container > stack;
        for ( int i = 0; i < p; ++i )
            if ( i % 3 == 0 && !stack.empty() )
                stack.pop();
            else
                stack.push( i );
    }
};
