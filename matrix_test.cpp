//#define BRICK_BENCHMARK_REG
//#define BRICK_BENCHMARK_MAIN

// benchmark of hashtables

/* ./bench category:stack | gnuplot > soubor.pdf */

//#include "hashTables.h"
//#include <brick-benchmark>
//#include <stack>
//#include <deque>
//#include <list>
//#include <queue>
#include "iostream"
#include <vector>
#include "matrix.h"

//using namespace brick;


int main() {

    Matrix A = Matrix(3,3);
    for (uint i = 0; i < A.getX(); i++) {
        for (uint j = 0; j < A.getY(); j++) {
            A.set(i,j,i+j*A.getX());
        }
    }

    Matrix B = Matrix(3,4);
    for (uint i = 0; i < B.getX(); i++) {
        for (uint j = 0; j < B.getY(); j++) {
            B.set(i,j,i+j*B.getX());
        }
    }


    Matrix C = Matrix::elementMultiply(A, B);

    C.print();

    Matrix D = Matrix::parallelMultiply2(A, B);

    D.print();

    std::cout << A.get(0,0) << " should be 0\n";
    std::cout << A.get(2,2) << " should be 8\n";
    std::cout << A.get(0,2) << " should be 6\n";

}



