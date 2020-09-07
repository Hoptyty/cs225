/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas * myCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector< Point<3> > myTree;
    map<Point<3>, TileImage> myMap;
    for( size_t i = 0; i < theTiles.size(); i++ ) {
        RGBAPixel myPixel = theTiles[i].getAverageColor();
        Point<3> p(myPixel.red, myPixel.green, myPixel.blue);
        myTree.push_back(p);
        myMap[p] = theTiles[i];
    }
    KDTree<3>::KDTree myKDTree(myTree);
    for( int i = 0; i < theSource.getRows(); i++ )
        for( int j = 0; j < theSource.getColumns(); j++ ) {
            RGBAPixel mySPixel = theSource.getRegionColor(i, j);
            Point<3> myPoint(mySPixel.red, mySPixel.green, mySPixel.blue);
            myCanvas->setTile(i,j,myMap[myKDTree.findNearestNeighbor(myPoint)]);
    }
	return myCanvas;
}
