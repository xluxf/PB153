
#include <functional>
#include "ex5.h"

void Random::edges( int from, std::function< void(int) > yield )
{
    for ( auto t : _succs[ from ] )
        yield( t );
}

void Random::initials( std::function< void(int) > yield )
{
    yield( 1 );
}

