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

	MosaicCanvas* theCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
	
	
	vector< Point<3> > tiles;
	map< Point<3>, TileImage> tile_images;
	
	for (int i = 0; i < theTiles.size(); i++) {
	
		RGBAPixel avg = theTiles[i].getAverageColor();
		
		Point<3> p(avg.red, avg.green, avg.blue);
		
		tile_images[p] = theTiles[i];
		
		tiles.push_back(p);
	}
	
	KDTree<3> theTree(tiles);
	
	
	for (int i = 0; i < theSource.getRows(); i++) {
	
		for (int j = 0; j < theSource.getColumns(); j++) {
		
			RGBAPixel src_avg = theSource.getRegionColor(i,j);
			Point<3> q(src_avg.red, src_avg.green, src_avg.blue);
			
			
			theCanvas->setTile(i, j, tile_images[theTree.findNearestNeighbor(q)] );
			
	
	
		}
	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	return theCanvas;
}
