#include "Connect_Four_AI.hpp"
#include <cstdlib>

int AIselectCol(Board board)
{
    return randInt(0, 6);
}

int randInt( int min, int max )
{
    if( min > max ){
        
        return (min + 1);
    }
    
    return (int)( ( ( rand() / (RAND_MAX * 1.0) ) * (1 + max - min) ) + min );
}
