/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements( int num )
{
    //Your code here!  
    if( num <= 0 )
        return;
    myDset.push_back( -1 );
    addelements( num - 1 );
}

int DisjointSets::find( int num )
{
    //Your code here!
    if( myDset[ num ] < 0 )
        return num;
    return myDset[ num ] = find( myDset[num] );
}

void DisjointSets::setunion( int a, int b )
{
    //Your code here!
    int root1 = find( a );
    int root2 = find( b );
    int size = myDset[ root1 ] + myDset[ root2 ];
    if( myDset[ root1 ] > myDset[ root2 ] ) {
        myDset[ root1 ] = root2;
        myDset[ root2 ] = size;
    }
    else {
        myDset[ root2 ] = root1;
        myDset[ root1 ] = size;
    }
}
