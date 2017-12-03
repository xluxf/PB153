#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <future>
#include <pthread.h>

struct Matrix {

private:
    std::vector<float> data;
    const uint xdim;
    const uint ydim;

public:
    Matrix (uint xdim, uint ydim) : xdim(xdim), ydim(ydim) {
        data.resize(xdim*ydim);
    }

    void randomFill() {

        std::random_device rd;
        std::mt19937 e2(rd());
        std::uniform_real_distribution<> dist(1, 10);

        for (uint x = 0; x < xdim; x++){
            for (uint y = 0; y < ydim; y++) {
                set(x,y,dist(e2));
            }
        }
    }

    float get(uint x, uint y) {
        if (x >= xdim || y >= ydim) {
            return float();
        }
        return data[ydim*x + y];
    }

    void set(uint x, uint y, float value) {
        data[ydim*x + y] = value;
    }

    void add(uint x, uint y, float value) {
        data[ydim*x + y] += value;
    }

    uint getX() { return xdim; }
    uint getY() { return ydim; }

    static Matrix elementMultiply(Matrix & A, Matrix & B) {
        if ( A.getY() != B.getX() )
            throw -1;
        uint dim = A.getY();
        uint Cx = A.getX();
        uint Cy = B.getY();
        Matrix C = Matrix(Cx, Cy);

        for (uint ax = 0; ax < Cx; ax++) {
            for (uint by = 0; by < Cy; by++){
                float result = 0;
                for (uint k = 0; k < dim; k++) {
                    result += A.get(ax, k) * B.get(k, by);
                }
                C.set(ax, by, result);
            }
        }
        return C;
    } 

    static Matrix parallelMultiply(Matrix & A, Matrix & B) {

        if ( A.getY() != B.getX() )
            throw -1;
        uint dim = A.getY();
        uint Cx = A.getX();
        uint Cy = B.getY();
        Matrix C = Matrix(Cx, Cy);

        #pragma omp parallel for
        for (uint ax = 0; ax < Cx; ax++) {
            for (uint by = 0; by < Cy; by++){
                for (uint k = 0; k < dim; k++) {
                    C.add(ax, by, A.get(ax, k) * B.get(k, by));
                }
            }
        }
        return C;
    } 

    Matrix transpose() {

        uint Ax = xdim;
        uint Ay = ydim;
        Matrix At = Matrix(Ay, Ax);

        for (uint x = 0; x < Ax; x++) {
            for (uint y = 0; y < Ay; y++){
                At.set(y, x, get(x, y));
            }
        }
        return At;
    } 

    static Matrix casheFriendlyMultiply(Matrix & A, Matrix & B) {
        if ( A.getY() != B.getX() )
            throw -1;

        Matrix Bt = B.transpose();
        uint dim = A.getY();
        uint Cx = A.getX();
        uint Cy = B.getY();
        Matrix C = Matrix(Cx, Cy);

        for (uint ax = 0; ax < Cx; ax++) {
            for (uint bx = 0; bx < Cy; bx++){
                float result = 0;
                for (uint k = 0; k < dim; k++) {
                    result += A.get(ax, k) * Bt.get(bx, k);
                }
                C.set(ax, bx, result);
            }
        }
        return C;
    } 

    static Matrix parallelMultiply2(Matrix & A, Matrix & B) {
        if ( A.getY() != B.getX() )
            throw -1;

        Matrix Bt = B.transpose();
        uint Cx = A.getX();
        uint Cy = B.getY();
        Matrix C = Matrix(Cx, Cy);

        std::vector<std::future<float > > futures(Cy);

        for (uint x = 0; x < Cx; x++) {

            for (uint y = 0; y < Cy; y++) {

                futures[y] = std::async(std::launch::async, &runKernel, A, Bt, x, y);
            }

            for (uint y = 0; y < Cy; y++) {
                futures[y].wait();
                C.set(x,y,futures[y].get());
            }
        }
        return C;
    } 


    static float runKernel(Matrix A, Matrix Bt, uint x, uint y) {

        float result = 0;
        for (uint s = 0; s < A.getY(); s++) {
            result += A.get(x,s) * Bt.get(y,s);
        }
        return result;

    }
    



    void print() {
        for (uint x = 0; x < xdim; x++){
            for (uint y = 0; y < ydim; y++) {
                std::cout << data[x*ydim + y] << " ";
            }
            std::cout << "\n";
        }
    }

};