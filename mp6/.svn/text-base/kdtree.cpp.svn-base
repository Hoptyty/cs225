/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
	if(first[curDim]==second[curDim])
		return first < second;
    	return first[curDim] < second[curDim];
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
	int sum1 = 0;
	int sum2 = 0;
	for(int i = 0; i < Dim ; i++)	{
		int dif1 = currentBest[i] - target[i];
	    int dif2 =  potential[i] - target[i];
		sum1 += dif1 * dif1;
		sum2 += dif2 * dif2;
	}
	if(sum1 == sum2)
		return potential < currentBest;
    	return sum2 < sum1;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    /**
     * @todo Implement this function!
     */
	points = newPoints;
	if(!points.empty())
	    buildTree(points, 0, points.size()-1, 0);
	
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
   return points[findLeaf(query, 0, points.size()-1, 0)]; 
   //return Point<Dim>();
}

template<int Dim>
void KDTree<Dim>::buildTree(vector< Point<Dim> > & points, int x, int y, int currDim)
{
    if(x >= y)
        return;
    int mid = ( x + y ) / 2;
    ctrHelper(points, x, y, mid, currDim);
    //points[mid]= myPoint;
    buildTree(points, x, mid-1, (currDim+1)%Dim);
    buildTree(points, mid+1, y, (currDim+1)%Dim);
}

template<int Dim>
int KDTree<Dim>::ctrHelper(vector< Point<Dim> > & points, int x, int y, int mid, int currDim)
{
	if(x >= y)
		return y;
	int myIdx=helpHelper(points, x, y, mid, currDim);
	if(mid == myIdx)
		return mid;
	if(mid < myIdx)
		return ctrHelper(points, x, myIdx-1, mid, currDim);
    else
		return ctrHelper(points, myIdx+1, y, mid, currDim);
}

template<int Dim>
int KDTree<Dim>::helpHelper(vector< Point<Dim> > & points, int x, int y, int n, int currDim)
{
	Point<Dim> myVal = points[n];
	points[n] = points[y];
	points[y] = myVal;
	int myIdx = x;
	for( int i = x; i < y; i++)
		if(smallerDimVal(points[i], myVal, currDim)) {
			Point<Dim> temp = points[i];
			points[i] = points[myIdx];
			points[myIdx] = temp;
			myIdx++;
		}
	points[y] = points[myIdx];
	points[myIdx] = myVal;
	return myIdx;		
}

template<int Dim>
int KDTree<Dim>::findLeaf(const Point<Dim> & query, int x, int y, int currDim) const
{   
    int currPos;
    int nPos;
    int mid = ( x + y ) / 2;
    if(x >= y)
        return mid;
    int dif = query[currDim] - points[mid][currDim];
    if(smallerDimVal(query, points[mid], currDim)) {
            currPos = findLeaf(query, x, mid-1, ( currDim + 1 ) % Dim);
            if(shouldReplace(query, points[currPos], points[mid]))
                currPos = mid;
            if(dif * dif <= dist(query, points[currPos])) {  
                nPos = findLeaf(query, mid+1, y, ( currDim + 1 ) % Dim);
                if(shouldReplace(query, points[currPos], points[nPos]))
                    currPos = nPos;
            }

    }
    else {
            currPos = findLeaf(query, mid+1, y, ( currDim + 1 ) % Dim);
            if(shouldReplace(query, points[currPos], points[mid]))
                currPos = mid;
            if(dif * dif <= dist(query, points[currPos])) {
                nPos = findLeaf(query, x, mid-1, ( currDim + 1 ) % Dim);
                if(shouldReplace(query, points[currPos], points[nPos]))
                    currPos = nPos;
            }
    }
    return currPos;
}

template<int Dim>
int KDTree<Dim>::dist(const Point<Dim> & query, const Point<Dim> & myPoint) const
{
    int sum = 0.0;
    for( int i = 0; i < Dim; i++ ) {
        int dif = query[i] - myPoint[i];
        sum += dif*dif;
    }
    return sum;
}
    
