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

Quadtree::Quadtree():root(NULL){
	//mp5.1
	//nothing
}
Quadtree::Quadtree(PNG const& source, int resolution):root(NULL){
	buildTree(source,resolution);
	this->myWidth=resolution;//mp5.1
} 
Quadtree::Quadtree(Quadtree const & other):root(copy(other.root)){
	this->myWidth=other.myWidth;//mp5.1
	//nothing
}
Quadtree::~Quadtree(){
	clear();
}
const Quadtree & Quadtree::operator =(Quadtree const & other){
	if(this!=&other){
		clear();
		root=copy(other.root);
		this->myWidth=other.myWidth;
	}
	return *this;//mp5.1
}
void Quadtree::buildTree(PNG const & source, int resolution){
	clear();
	root=new QuadtreeNode();
	myWidth=resolution;
	buildTree(source,resolution,0,0,root); //mp5.1
}
RGBAPixel Quadtree::getPixel(int x, int y) const{
	return getPixel(x,y,myWidth,root);//mp5.1
}
PNG Quadtree::decompress() const{
	if(root==NULL)
		return PNG();
	PNG::PNG myPic= PNG(myWidth,myWidth);
	
	decompress(1,myWidth,0,0,root,myPic);
	return myPic;//mp5.1
}
void Quadtree::clockwiseRotate(){
	clockwiseRotate(root);//mp5.2
}
void Quadtree::prune(int tolerance){
	prune(tolerance,root);//mp5.2
}
int Quadtree::pruneSize(int tolerance) const{
	return pruneSize(tolerance,root);//mp5.2
}
int Quadtree::idealPrune(int numLeaves)const{
	int y=INT_MAX;
	int myMax=myWidth*myWidth;
	if(root==NULL||numLeaves>=myMax)
		return 0;	
	return idealPrune(numLeaves,y/2,0,y);//mp5.2
}
void Quadtree::clear(){
	clear(root);
	root=NULL;//mp5.1
}
void Quadtree::clear(QuadtreeNode *& subRoot){
	if(subRoot==NULL)	return;
	clear(subRoot->nwChild);
	clear(subRoot->neChild);
	clear(subRoot->swChild);
	clear(subRoot->seChild);
	delete subRoot;
	subRoot=NULL;//mp5.1
}
Quadtree::QuadtreeNode* Quadtree::copy(const QuadtreeNode * subRoot){
	if(subRoot==NULL)
		return NULL;
	QuadtreeNode * myNode= new QuadtreeNode();
	myNode->element=subRoot->element;
	myNode->nwChild=copy(subRoot->nwChild);
	myNode->neChild=copy(subRoot->neChild);
	myNode->swChild=copy(subRoot->swChild);
	myNode->seChild=copy(subRoot->seChild);
	return myNode;//mp5.1
}
void Quadtree::buildTree(PNG const & source, int resolution,int x, int y, QuadtreeNode* subRoot){
	if(resolution<=1){
		subRoot->element=*source(x,y);
		return;
	}
	subRoot->nwChild= new QuadtreeNode();
	subRoot->neChild= new QuadtreeNode();
	subRoot->swChild= new QuadtreeNode();
	subRoot->seChild= new QuadtreeNode();
	buildTree(source,resolution/2,x,y,subRoot->nwChild);
	buildTree(source,resolution/2,x+resolution/2,y,subRoot->neChild);
	buildTree(source,resolution/2,x,y+resolution/2,subRoot->swChild);
	buildTree(source,resolution/2,x+resolution/2,y+resolution/2,subRoot->seChild);
	subRoot->element=RGBAPixel();
	subRoot->element.red=(subRoot->nwChild->element.red	+subRoot->neChild->element.red
				+subRoot->swChild->element.red	+subRoot->seChild->element.red)/4;
	subRoot->element.green=(subRoot->nwChild->element.green	+subRoot->neChild->element.green
                                +subRoot->swChild->element.green+subRoot->seChild->element.green)/4;
	subRoot->element.blue=(subRoot->nwChild->element.blue	+subRoot->neChild->element.blue
                                +subRoot->swChild->element.blue +subRoot->seChild->element.blue)/4;//mp5.1
}
RGBAPixel Quadtree::getPixel(int x, int y, int resolution, QuadtreeNode * subRoot) const {
	if(subRoot==NULL||x>=resolution||x<0||y>=resolution||y<0)
		return RGBAPixel();
	if(subRoot->nwChild==NULL)
		return subRoot->element;
	if(x<resolution/2 && y<resolution/2)
		return getPixel(x,y,resolution/2,subRoot->nwChild);
	if(x>=resolution/2 && y<resolution/2)
		return getPixel(x-resolution/2,y,resolution/2, subRoot->neChild);
	if(x<resolution/2 && y>=resolution/2)
		return getPixel(x,y-resolution/2, resolution/2, subRoot->swChild);
	return getPixel(x-resolution/2,y-resolution/2,resolution/2,subRoot->seChild);
	
}
void Quadtree::decompress(int currSize, int resolution,int x, int y, QuadtreeNode * subRoot, PNG & myPic) const{
	if(subRoot==NULL)
		return;
	if(subRoot->nwChild==NULL)
		for(int i=0;i<resolution/currSize;i++)
			for(int j=0;j<resolution/currSize;j++)
				*myPic(x+i,y+j)=subRoot->element;
	decompress(2*currSize,resolution,x,y,subRoot->nwChild,myPic);
	decompress(2*currSize,resolution,x+resolution/(2*currSize),y,subRoot->neChild,myPic);
	decompress(2*currSize,resolution,x,y+resolution/(2*currSize),subRoot->swChild,myPic);
	decompress(2*currSize,resolution,x+resolution/(2*currSize),y+resolution/(2*currSize),subRoot->seChild,myPic);
	//mp5.1
}

/*
int Quadtree::height(QuadtreeNode * subRoot) const{
	if(subRoot==NULL)
		return -1;
	return 1+fmax(fmax(height(subRoot->nwChild),height(subRoot->neChild)),fmax(height(subRoot->swChild),height(subRoot->seChild)));//mp5.1
}
**/
void Quadtree::clockwiseRotate(QuadtreeNode * subRoot){
	if(subRoot==NULL)		return;
	//if(subRoot->nwChild==NULL)	return;
	QuadtreeNode * myNode=subRoot->nwChild;
	subRoot->nwChild=subRoot->swChild;
	subRoot->swChild=subRoot->seChild;
	subRoot->seChild=subRoot->neChild;
	subRoot->neChild=myNode;
	clockwiseRotate(subRoot->nwChild);
	clockwiseRotate(subRoot->neChild);
	clockwiseRotate(subRoot->swChild);
	clockwiseRotate(subRoot->seChild);
	//mp5.2
}

void Quadtree::prune(int tolerance, QuadtreeNode * subRoot) {
	if(subRoot==NULL)	return;
	int myRed =	subRoot->element.red;
	int myGreen =	subRoot->element.green;
	int myBlue =	subRoot->element.blue;
	bool doPrune =	checkLeaf(tolerance,subRoot,myRed,myGreen,myBlue);
	if(doPrune) {
		clear(subRoot->nwChild);
		subRoot->nwChild=NULL;
		clear(subRoot->neChild);
		subRoot->neChild=NULL;
		clear(subRoot->swChild);
		subRoot->swChild=NULL;
		clear(subRoot->seChild);
		subRoot->seChild=NULL;
		return;
	}
	prune(tolerance, subRoot->nwChild);
	prune(tolerance, subRoot->neChild);
	prune(tolerance, subRoot->swChild);
	prune(tolerance, subRoot->seChild);//mp5.2
} 

int Quadtree::pruneSize(int tolerance, QuadtreeNode * subRoot) const {
	if(subRoot==NULL)	
		return 0;
	if(subRoot->nwChild==NULL)       return 1;
        int myRed =     subRoot->element.red;
        int myGreen =   subRoot->element.green;
        int myBlue =    subRoot->element.blue;
        bool doPrune =  checkLeaf(tolerance,subRoot,myRed,myGreen,myBlue);
        if(doPrune) 
                return 1;
        int nw=pruneSize(tolerance, subRoot->nwChild);
        int ne=pruneSize(tolerance, subRoot->neChild);
        int sw=pruneSize(tolerance, subRoot->swChild);
        int se=pruneSize(tolerance, subRoot->seChild);
	return nw+ne+sw+se;
}
bool Quadtree::checkLeaf(int tolerance, QuadtreeNode * subRoot, int myRed, int myGreen, int myBlue)const{
	if(subRoot->nwChild==NULL) {
		int difR=subRoot->element.red-myRed;
		int difG=subRoot->element.green-myGreen;
		int difB=subRoot->element.blue-myBlue;
		int myDist=difR*difR+difG*difG+difB*difB;
		if(myDist<=tolerance)
			return true;
		else 
			return false;
	}
	bool nw=checkLeaf(tolerance,subRoot->nwChild, myRed, myGreen, myBlue);
	bool ne=checkLeaf(tolerance,subRoot->neChild, myRed, myGreen, myBlue);
	bool sw=checkLeaf(tolerance,subRoot->swChild, myRed, myGreen, myBlue);
	bool se=checkLeaf(tolerance,subRoot->seChild, myRed, myGreen, myBlue);
	return nw&&ne&&sw&&se;
}

int Quadtree::idealPrune(int numLeaves, int tolerance, int x, int y) const {
	int myLeaves=pruneSize(tolerance);
	int myLeaves2=pruneSize(tolerance-1);
	if(myLeaves<=numLeaves&&myLeaves2>numLeaves) 
		return tolerance;
	if(myLeaves<=numLeaves)
		return idealPrune(numLeaves,(tolerance+x)/2,x,(x+y)/2);
	else		
		return idealPrune(numLeaves,(tolerance+y)/2,(x+y)/2,y);
	
	
}
