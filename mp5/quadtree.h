// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
	
		Quadtree();
		
		Quadtree(const PNG & source, int resolution);
		
		Quadtree(Quadtree const & other);
		
		~Quadtree();
		
		
		
		
		
		Quadtree const & operator=(Quadtree const &other);
		
		void buildTree (PNG const &source, int resolution);
		
		RGBAPixel getPixel(int x, int y) const;
	
		PNG decompress() const;
		
		void clockwiseRotate();
		
		void prune(int tolerance);
		
		int pruneSize(int tolerance) const;
		
		int idealPrune(int numLeaves) const;
		
		int idealPrune(int numLeaves, int min, int max) const;
		
		
	
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
		
		QuadtreeNode(RGBAPixel &thePixel) {
		
			element = thePixel;
			nwChild = NULL;
			neChild = NULL;
			swChild = NULL;
			seChild = NULL;
		
		}
		
		QuadtreeNode() {
		
			nwChild = NULL;
			neChild = NULL;
			swChild = NULL;
			seChild = NULL;
		
		}
		
		
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree
	
	void clear();
	
	void clear(QuadtreeNode* &subRoot);
	
	void buildTree(PNG const &source, int resolution, int x, int y, QuadtreeNode* &subRoot);
	
	void copy(Quadtree const & other);
	
	void copy(QuadtreeNode* &subRoot, QuadtreeNode* const &N);
	
	void clockwiseRotate(QuadtreeNode* &subRoot);
	
	void prune(int tolerance, QuadtreeNode* &subRoot);
	
	bool helpPrune(int tolerance, QuadtreeNode* &theNode, QuadtreeNode* &subRoot);
	
	bool checkTolerance(int tolerance, QuadtreeNode* &subRoot, QuadtreeNode* &other);
	
	int pruneSize(int tolerance, QuadtreeNode* const &subRoot) const;
	
	bool helpPruneSize(int tolerance, QuadtreeNode* const &theNode, QuadtreeNode* const &subRoot) const;
	
	bool checkToleranceConst(int tolerance, QuadtreeNode* const &subRoot, QuadtreeNode* const &other) const;
	
	
	
	RGBAPixel getPixel(int x, int y, int rez, QuadtreeNode* subRoot) const;
	
	int rez;
	
	
	
	
	
	
	
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
