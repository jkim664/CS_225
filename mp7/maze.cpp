


#include "maze.h"



SquareMaze::SquareMaze() {
	
	

}

void SquareMaze::initWalls(int width, int height) {

	
	
	for (int i = 0; i < (width*height); i++) {
	
		downWalls.push_back(true);
		rightWalls.push_back(true);
		visited.push_back(false);
	
	
	}
	



}





void SquareMaze::makeMaze(int width, int height) {

	W = width;
	H = height;

	DS.addelements(width*height);

	for (int i = 0; i < width; i++) {				//Fill vector of pairs
	
		for (int j = 0; j < height; j++) {
		
			grid.push_back(std::make_pair(i,j));
				
		}	
			
	}
	
	initWalls(width, height);
	
	srand(time(0));
	
	random_shuffle( grid.begin(), grid.end() );
	
	for (int i = 0; i < grid.size(); i++) {
		int x = grid[i].first;
		int y = grid[i].second;
		
		//std::cout << x << "," << y << endl;
		if (!(x == width-1 && y == height-1)) {
			int ds_coord = x + (y*width);
			int ds_right = (x+1) + (y*width);
			int ds_down = x + ((y+1)*width);
			int root_r, root_d;
			int root = DS.find(ds_coord);
			
			
			
			if (x == width-1) {						//Rightmost column
				root = DS.find(ds_coord);
				root_d = DS.find(ds_down);
				if (root != root_d) {
					setWall(x, y, 1, false);			//Knock down down wall
					DS.setunion(root, root_d);
				}
			
			}
			
			else if (y == height-1) {					//Bottom row
				root = DS.find(ds_coord);
				root_r = DS.find(ds_right);
				if (root != root_r) {
					setWall(x, y, 0, false);			//Knock down right wall
					DS.setunion(root, root_r);
				}
			}
			
			else {	
				root = DS.find(ds_coord);
				root_r = DS.find(ds_right);											
				if (root != root_r) {
					setWall(x, y, 0, false);			
					DS.setunion(root, root_r);
				}
				
				
				root = DS.find(ds_coord);
				root_d = DS.find(ds_down);
				if ( root != root_d ) {
				
					setWall(x, y, 1, false);
					DS.setunion(root, root_d);
				}
			}
		}	
	}
	
}

bool SquareMaze::canTravel(int x, int y, int dir) const {

	if ( x < 0 || y < 0 || x >= W || y >= H ) return false;
	
	int idx = y*W + x;
	int idx_L = y*W + (x-1);
	int idx_U = (y-1)*W + x;
	
	if (dir == 0) {					//RIGHT
	
		if (x != W-1) {
			
			return !rightWalls[idx];
		}
		
		return false;
	
	}
	
	if (dir == 1) {					//DOWN
	
		if (y != H-1) {
		
			return !downWalls[idx];
		}
		
		return false;
	
	}
	
	if (dir == 2) {					//LEFT
	
		if (x != 0) {
		
			return !rightWalls[idx_L];	
		}
		
		return false;
	
	}
	
	if (dir == 3) {					//UP
	
		if (y != 0) {
		
			return !downWalls[idx_U];
		}
		
		return false;
		
	}
	
	return false;

}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {

	int idx = y*W + x;

	if (dir == 0) {
		if (x != W-1) {
			rightWalls[idx] = exists;
		}
	}
	
	if (dir == 1) {
		if (y != H-1) {
			downWalls[idx] = exists;
		}
	}
}

vector<int> SquareMaze::solveMaze() {

		
	queue< pair<int,int> > q;						//Stores coordinates for BFS

	vector<int> paths[W][H];						//Stores movement path starting from (0,0), RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3
										//
	//int PATHS[W][H];
	
	//int size[W][H];
										
	int x = 0;
	int y = 0;	
	
	//size[x][y] = 0;
	
	q.push(std::make_pair(x,y));
	
	
	while (!q.empty()) {
	
		x = q.front().first;
		y = q.front().second;
		visited[x + y*W] = true;
		q.pop();
		
		
		if (canTravel(x, y, 0) ) {					//GO RIGHT
			
			if ( !visited[(x+1) + y*W] ) {
				q.push(std::make_pair(x+1,y));
				//PATHS[x+1][y] = 0;
				//size[x+1][y] = size[x][y] + 1;
				paths[x+1][y] = paths[x][y];
				paths[x+1][y].push_back(0);
			}
		
		}
		
		if (canTravel(x, y, 1) ) {					//GO DOWN
			
			if ( !visited[x + (y+1)*W] ) {
				q.push(std::make_pair(x,y+1));
				//PATHS[x+1][y] = 1;
				//size[x+1][y] = size[x][y] + 1;
				paths[x][y+1] = paths[x][y];
				paths[x][y+1].push_back(1);
			}
			
		}

		if (canTravel(x, y, 2) ) {					//GO LEFT
			
			if ( !visited[(x-1) + y*W] ) {
				q.push(std::make_pair(x-1,y));
				//PATHS[x-1][y] = 2;
				//size[x-1][y] = size[x][y] + 1;
				paths[x-1][y] = paths[x][y];
				paths[x-1][y].push_back(2);
			}
		}
		
		if (canTravel(x, y, 3)) {					//GO UP
			
			if ( !visited[x + (y-1)*W] ) {
				q.push(std::make_pair(x,y-1));
				//PATHS[x][y-1] = 3;
				//size[x][y-1] = size[x][y] + 1;
				paths[x][y-1] = paths[x][y];
				paths[x][y-1].push_back(3);
			}
		}


	}
	
	
	int maxSize = 0;
	int idx;
	
	for (int i = 0; i < W; i++) {
	
		if (paths[i][H-1].size() > maxSize) {
			
			maxSize = paths[i][H-1].size();
			idx = i;
		}
	
	
	}
	
	
	destX = idx;
	destY = H-1;
	destination = paths[idx][H-1];
	
	/*vector<int> D;
	
	
	x = destX;
	y = destY;
	bool done = false;
	
	
	for (int i = 0; i < size[destX][destY]; i++) {
	
		if (PATHS[x][y] == 0 && !done) {				//Went RIGHT
			D.push_back(0);
			x--;
			done = true;
		}
		
		if (PATHS[x][y] == 1 && !done) {				//Went DOWN
			D.push_back(1);
			y--;
			done = true;
		}
		
		if (PATHS[x][y] == 2 && !done) {				//Went LEFT
			D.push_back(2);
			x++;
			done = true;
		}
		
		if (PATHS[x][y] == 3 && !done) {				//Went UP
			D.push_back(3);
			y--;
			done = true;
		}
		
		done = false;
	
	}
	
	for (int i = D.size()-1; i >= 0; i--) {
	
		destination.push_back(D[i]);
		D.pop_back();
	
	}*/
	
	
	return destination;

}

PNG* SquareMaze::drawMaze() const {

	int img_width = W*10 + 1;
	int img_height = H*10 + 1;

	PNG* theMaze = new PNG(img_width, img_height);
	
	for (int i = 0; i < img_width; i++) {
	
		if (i >= 1 && i <= 9) {
		
			*(*theMaze)(i,0) = RGBAPixel(255, 255, 255);			//Set white pixels for (1,0) through (9,0)
		}
		else {
			*(*theMaze)(i,0) = RGBAPixel(0, 0, 0);				//Set black pixels for topmost row
		
		}
		
	}
	
	for (int i = 0; i < img_height; i++) {
	
		*(*theMaze)(0,i) = RGBAPixel(0, 0, 0);					//Set black pixels for leftmost column
	}
	
	
	for (int x = 0; x < W; x++) {
	
		for (int y = 0; y < H; y++) {
			
			if (rightWalls[y*W + x]) {
				
				for (int k = 0; k < 11; k++) {
					
					*(*theMaze)((x+1)*10,y*10+k) = RGBAPixel(0, 0, 0);
				
				}
				
			}
			
			if (downWalls[y*W + x]) {
			
				for (int k = 0; k < 11; k++) {
					
					*(*theMaze)(x*10+k, (y+1)*10) = RGBAPixel(0, 0, 0);
				
				}
			
			
			}
		
		}
		
	}
	
	
	return theMaze;
	

}

PNG* SquareMaze::drawMazeWithSolution() {

	PNG* sol = drawMaze();
	
	vector<int> v = destination;
	int x = 5;
	int y = 5;
	
	for (int i = 0; i < v.size(); i++) {
		
		
			
		if (v[i] == 0) {						//RIGHT
			
			for (int j = 0; j < 11; j++) {
				*(*sol)(x+j, y) = RGBAPixel(255, 0, 0);
			
			}
			x += 10;
			
		}
			
		if (v[i] == 1) {						//DOWN
		
			for (int j = 0; j < 11; j++) {
				*(*sol)(x, y+j) = RGBAPixel(255, 0, 0);
				
			}
			y += 10;
			
		}
			
		if (v[i] == 2) {						//LEFT
			
			for (int j = 0; j < 11; j++) {
				*(*sol)(x-j, y) = RGBAPixel(255, 0, 0);
				
			}
			x -= 10;
		}
			
		if (v[i] == 3) {						//UP
			
			for (int j = 0; j < 11; j++) {
				*(*sol)(x, y-j) = RGBAPixel(255, 0, 0);
				
			}
			y -= 10;
		}
			
		
	}
	
	for (int k = 1; k < 10; k++) {
		
		*(*sol)(destX*10+k, (destY+1)*10) = RGBAPixel(255, 255, 255);
	
	}
	
	
	return sol;

}



