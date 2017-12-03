/**
 *  PB153
 * ex7
 * parallel map-reduce
 * @author Filip Lux
 */

#define DATA_SIZE 100


#include <set>
#include <list>
#include <vector>
#include <random>
#include <cassert>
#include <functional>
#include "ex5.h"
#include <future>

template < typename T >
T mapReduceSeq (T * data, T(*map)(T), T (*reduce)(T, T) ) {


    T result = T();
    for (int i = 0; i < DATA_SIZE; i++) {

        result = (*reduce)(result, (*map)(data[i]));
    } 
    return result;

};


template < typename T >
T mapReduceParallel (T * data, T(*map)(T), T (*reduce)(T, T) ) {

    //std::vector< std::future<T> > futureVec;
    std::future<T> futureVec;


    // create future instances

    T result = T();

    for ( int i = 0; i < DATA_SIZE; i++) {

        std::future<T> f = std::async(std::launch::async,
                                [&]() { return (*map)(data[i]); }); 

        f.wait();
        result = (*reduce)(result, f.get() ); 

    }
/**
    
    for ( int i = 0; i < DATA_SIZE; i++) {

        futureVec[i].wait();
        result = (*reduce)(result, futureVec[i].get() );        
    } 
    */

    return result;

};

    

template < typename T >
T addOne ( T x ) {
  return x + 1;
};

template < typename T >
T sum ( T x, T y ) {
  return x + y;
};



int main()
{
    float data[DATA_SIZE];
    for (int i = 0; i < DATA_SIZE; i++) {
        data[i] = float(i/2);
    }

    float a = mapReduceSeq<float>(data, addOne, sum);
    printf("Result seq is: %d\n", (int)a);

    float b = mapReduceParallel<float>(data, addOne, sum);
    printf("Result seq is: %d\n", (int)b);

}
