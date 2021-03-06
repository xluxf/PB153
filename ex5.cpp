#include <set>
#include <list>
#include <vector>
#include <random>
#include <cassert>
#include <functional>
#include "ex5.h"


template< typename G >
std::pair< int, int > bfs( G &graph )
{
    std::list< int > open;
    std::set< int > closed;

    graph.initials( [&]( auto v ) { open.push_back( v ); } );
    int edges = -1, vertices = 0;

    while ( !open.empty() )
    {
        auto v = open.front();
        open.pop_front();

        ++ edges;
        if ( closed.count( v ) )
            continue;

        closed.insert( v );
        ++ vertices;


        bool inserted = false;

        graph.edges( v, [&]( auto v ) { 
            if ( !closed.count(v) ) {
                closed.insert( v );
                inserted = true;

            }
            if (inserted) {
                open.push_back( v );
            }
            
        } );
    }

    return std::make_pair( vertices, edges );
}

int main()
{
    int vertices = 5000, edges = 80000;
    Random r( vertices, edges );
    auto b = bfs( r );
    assert( b.first == vertices );
    assert( b.second == edges );
    return 0;
}
