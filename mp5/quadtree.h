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
#include <math.h>
class Quadtree
{
	public:
	Quadtree();
	Quadtree(PNG const & source, int resolution);
	Quadtree( Quadtree const & other);
	~Quadtree();	
	const Quadtree & operator = (Quadtree const& other);
	void buildTree(PNG const & source, int resolution);
	RGBAPixel getPixel(int x, int y) const;
	PNG decompress() const;
	void clockwiseRotate();
	void prune(int tolerance);
	int pruneSize( int tolerance) const;
	int idealPrune(int numLeaves) const;
	
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
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree
	int myWidth;
	
	void clear();
	void clear(QuadtreeNode * & subRoot);
	QuadtreeNode * copy(const QuadtreeNode * subRoot);
	void buildTree(PNG const & source, int resolution,int x, int y, QuadtreeNode * subRoot);
	RGBAPixel getPixel(int x, int y, int resolution, QuadtreeNode * subRoot) const;
	void decompress(int currSize,int resolution,int x,int y,QuadtreeNode * subRoot,PNG & myPic) const;
	//int height(QuadtreeNode * subRoot) const;
	void clockwiseRotate(QuadtreeNode * subRoot);
	void prune(int tolerance, QuadtreeNode * subRoot);
	int pruneSize(int tolerance, QuadtreeNode * subRoot) const ;
	bool checkLeaf(int tolerance, QuadtreeNode * subRoot, int myRed, int myGreen, int myBlue) const ;
	int idealPrune(int numLeaves, int tolerance,int x, int y) const;
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
