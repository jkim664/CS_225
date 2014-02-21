
#ifndef EMAZE_H
#define EMAZE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "png.h"
#include "dsets.h"
using std::queue;
using std::vector;
using std::pair;



class SquareMaze
{

	public:
	
		SquareMaze();
		
		void makeMaze(int width, int height);
		
		bool canTravel(int x, int y, int dir) const;
		
		void setWall(int x, int y, int dir, bool exists);
		
		vector<int> solveMaze();

		PNG* drawMaze() const;
		
		PNG* drawMazeWithSolution();

	private:
		
		int W;				//number of cells
		int H;
		
		int destX;
		int destY;
		
		vector< pair<int,int> > grid;		//x, y
		
		vector<bool> downWalls;
		vector<bool> rightWalls;
		
		vector<bool> visited;
		
		vector<int> destination;
		
		DisjointSets DS;
		
		
		
		
		void initWalls(int width, int height);



};

#endif
