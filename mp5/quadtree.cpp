// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
#include <math.h>


Quadtree::Quadtree() {							//MP5.1 no argument Quadtree constructor

	root = NULL;
	rez = 0;
	
}


Quadtree::Quadtree(const PNG & source, int resolution) {		//MP5.1 two args Quadtree constructor
	
	rez = resolution;
	buildTree(source, resolution);

}


Quadtree::Quadtree(Quadtree const &other) {				//MP5.1 copy constructor

	root = NULL;
	rez = 0;
	copy(other);

}

void Quadtree::copy(Quadtree const & other) {

	rez = other.rez;

	copy(root, other.root);
}

void Quadtree::copy(QuadtreeNode* &subRoot, QuadtreeNode* const &N) {

	if (N == NULL) return;

	subRoot = new QuadtreeNode(N->element);
	
	copy(subRoot->nwChild, N->nwChild);
	copy(subRoot->neChild, N->neChild);
	copy(subRoot->swChild, N->swChild);
	copy(subRoot->seChild, N->seChild);
	



}



PNG Quadtree::decompress() const {					//MP5.1

	if (root == NULL) return PNG(rez, rez);

	PNG out(rez, rez);
	
	for (int i = 0; i < rez; i++) {
	
		for (int j = 0; j < rez; j++) {
		
			*out(i, j) = getPixel(i, j);
		}
	}
	

	return out;

}


Quadtree::~Quadtree() {							//MP5.1

	clear();

}




void Quadtree::clear() {

	clear(root);


}

void Quadtree::clear(QuadtreeNode* &subRoot) {

	if (subRoot== NULL) {
		return;
	}
	
	clear(subRoot->seChild);
	clear(subRoot->swChild);
	clear(subRoot->neChild);
	clear(subRoot->nwChild);
	
	delete subRoot;
	subRoot = NULL;


}


Quadtree const & Quadtree::operator=(Quadtree const &other) {		//MP5.1 overloaded assignment operator

	if (this != &other) {
	
		clear();	
	
		copy(other);
	
	}
	
	
	return *this;

}

void Quadtree::buildTree(PNG const &source, int resolution) {		//MP5.1

	rez = resolution;	
	buildTree(source, resolution, 0, 0, root);

}

void Quadtree::buildTree(PNG const &source, int resolution, int x, int y, QuadtreeNode* &subRoot) {		//buildTree helper

	subRoot = new QuadtreeNode();
	
	
	
	if (resolution == 1) {
		
		subRoot->element = *source(x,y);
		return;	
	
	}

	buildTree(source, resolution/2, x, y, subRoot->nwChild);
	buildTree(source, resolution/2, x + resolution/2, y, subRoot->neChild);
	buildTree(source, resolution/2, x, y + resolution/2, subRoot->swChild);
	buildTree(source, resolution/2, x + resolution/2, y + resolution/2, subRoot->seChild);
	
	(subRoot->element).red = ((subRoot->nwChild->element).red + (subRoot->neChild->element).red + (subRoot->swChild->element).red + (subRoot->seChild->element).red)/4;
	(subRoot->element).green = ((subRoot->nwChild->element).green + (subRoot->neChild->element).green + (subRoot->swChild->element).green + (subRoot->seChild->element).green)/4;
	(subRoot->element).blue = ((subRoot->nwChild->element).blue + (subRoot->neChild->element).blue + (subRoot->swChild->element).blue + (subRoot->seChild->element).blue)/4;
	
	


}


RGBAPixel Quadtree::getPixel(int x, int y) const {			//MP5.1
	
	if (root == NULL || x >= rez || y >= rez) {
		return RGBAPixel();
	}
	
	return getPixel(x, y, rez, root);

}

RGBAPixel Quadtree::getPixel(int x, int y, int R, QuadtreeNode* subRoot) const {

	 

	if (R == 1 || (subRoot->nwChild == NULL && subRoot->neChild == NULL && subRoot->swChild == NULL && subRoot->seChild == NULL )) {
	 	return subRoot->element;
	}
	
	else {
	
		if (x < (R/2) && y < (R/2)) {
		
		return getPixel(x, y, (R/2), subRoot->nwChild);
	
		}
	
		if (x >= (R/2) && y < (R/2)) {
		
		return getPixel(x - (R/2), y, (R/2), subRoot->neChild);
	
		}
	
		if (x < (R/2) && y >= (R/2)) {
		
		return getPixel(x, y - (R/2), (R/2), subRoot->swChild);
	
		}

		if (x >= (R/2) && y >= (R/2)) {
		
		return getPixel(x - (R/2), y - (R/2), (R/2), subRoot->seChild);
	
		} else {
			return subRoot->element;
		
		}
		
		
	}
	
	

}


void Quadtree::clockwiseRotate() {

	if (root == NULL) return;

	clockwiseRotate(root);
}

void Quadtree::clockwiseRotate(QuadtreeNode* &subRoot) {

	if (subRoot->nwChild == NULL) return;
	
	QuadtreeNode* temp = subRoot->neChild;
	subRoot->neChild = subRoot->nwChild;
	subRoot->nwChild = subRoot->swChild;
	subRoot->swChild = subRoot->seChild;
	subRoot->seChild = temp;
	
	clockwiseRotate(subRoot->nwChild);
	clockwiseRotate(subRoot->neChild);
	clockwiseRotate(subRoot->swChild);
	clockwiseRotate(subRoot->seChild);



}

void Quadtree::prune(int tolerance) {

	if (root == NULL) return;	
	prune(tolerance, root);
}

void Quadtree::prune(int tolerance, QuadtreeNode* &subRoot) {

	if (subRoot == NULL) return;

	
	
	if (helpPrune(tolerance, subRoot, subRoot)) {
		
		clear(subRoot->nwChild);
		clear(subRoot->neChild);
		clear(subRoot->swChild);
		clear(subRoot->seChild);
	}
	else {
		prune(tolerance, subRoot->nwChild);
		prune(tolerance, subRoot->neChild);
		prune(tolerance, subRoot->swChild);
		prune(tolerance, subRoot->seChild);
	}

}

bool Quadtree::helpPrune(int tolerance, QuadtreeNode* &theNode, QuadtreeNode* &subRoot) {

	if (root == NULL) return false;

	if (subRoot->nwChild == NULL && subRoot->neChild == NULL && subRoot->swChild == NULL && subRoot->seChild == NULL) {
	
		return (checkTolerance(tolerance, theNode, subRoot));
		
	}
	
	return helpPrune(tolerance, theNode, subRoot->nwChild) && helpPrune(tolerance, theNode, subRoot->neChild) &&
	       helpPrune(tolerance, theNode, subRoot->swChild) && helpPrune(tolerance, theNode, subRoot->seChild);
	
	
}

bool Quadtree::checkTolerance(int tolerance, QuadtreeNode* &subRoot, QuadtreeNode* &other) {

	if (root == NULL) return false;

	return ( ( pow((subRoot->element.red - other->element.red), 2)
           	  + pow((subRoot->element.green - other->element.green), 2)
                  + pow((subRoot->element.blue - other->element.blue), 2) ) <= tolerance);

}


int Quadtree::pruneSize(int tolerance) const {

	if (root == NULL) return 0;
	return pruneSize(tolerance, root);
}

int Quadtree::pruneSize(int tolerance, QuadtreeNode* const &subRoot) const {

	if (subRoot == NULL) return 0;

	if (helpPruneSize(tolerance, subRoot, subRoot)) {
		
		return 1;
	}
	else {
		return pruneSize(tolerance, subRoot->nwChild) + pruneSize(tolerance, subRoot->neChild) +
		       pruneSize(tolerance, subRoot->swChild) + pruneSize(tolerance, subRoot->seChild);
	}


}

bool Quadtree::helpPruneSize(int tolerance, QuadtreeNode* const &theNode, QuadtreeNode* const &subRoot) const {

	if (root == NULL) return false;

	if (subRoot->nwChild == NULL && subRoot->neChild == NULL && subRoot->swChild == NULL && subRoot->seChild == NULL) {
	
		return (checkToleranceConst(tolerance, theNode, subRoot));
		
	}
	
	return helpPruneSize(tolerance, theNode, subRoot->nwChild) && helpPruneSize(tolerance, theNode, subRoot->neChild) &&
	       helpPruneSize(tolerance, theNode, subRoot->swChild) && helpPruneSize(tolerance, theNode, subRoot->seChild);
	
	
}

bool Quadtree::checkToleranceConst(int tolerance, QuadtreeNode* const &subRoot, QuadtreeNode* const &other) const {

	if (root == NULL) return false;

	return ( ( pow((subRoot->element.red - other->element.red), 2)
           	  + pow((subRoot->element.green - other->element.green), 2)
                  + pow((subRoot->element.blue - other->element.blue), 2) ) <= tolerance);

}


int Quadtree::idealPrune(int numLeaves) const {

	if (root == NULL || numLeaves > (rez*rez)) return 0;
	
	return idealPrune(numLeaves, 0, 195075);	//195075, 262144, 
	
	
}

int Quadtree::idealPrune(int numLeaves, int min, int max) const {

	

	int mid = (max+min)/2;
	
	if (min >= max) return min;
	
	if (pruneSize(mid) > numLeaves) {
		
		return idealPrune(numLeaves, mid+1, max);
	
	} else {

		return idealPrune(numLeaves, min, mid);
	}
		
}













