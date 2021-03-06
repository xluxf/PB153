#define BRICK_BENCHMARK_REG
#define BRICK_BENCHMARK_MAIN

// benchmark of hashtables

/* ./bench category:stack | gnuplot > soubor.pdf */

#include "matrix.h"
#include <brick-benchmark>
#include <stack>
#include <deque>
#include <list>
#include <queue>


using namespace brick;

struct MatrixMull : benchmark::Group
{

    MatrixMull()
    {

        x.type = benchmark::Axis::Quantitative;
        x.name = "items";
        x.min = 100;
        x.max = 1500;
        x.step = 100;

        y.type = benchmark::Axis::Qualitative;
        y.name = "implementation";
        y.min = 1;
        y.max = 2;
        y._render = []( int i )
        {
            switch ( i )
            {
                case 1: return "naive mull";
                case 2: return "cache friendly mull";
            }
        };
    }

    std::string describe() { return "category:matrixMull"; }

    BENCHMARK( mull )
    {
        switch ( q )
        {
            case 1: naiveMull(); break;
            case 2: cacheFriandlyMull(); break;
        }
    }

    void naiveMull() {
        Matrix A = Matrix(p,p);
        Matrix B = Matrix(p,p);

        A.randomFill();
        B.randomFill();

        Matrix::elementMultiply(A,B);
    }

    void cacheFriandlyMull() {
        Matrix A = Matrix(p,p);
        Matrix B = Matrix(p,p);

        A.randomFill();
        B.randomFill();

        Matrix::casheFriendlyMultiply(A,B);
    }

};
