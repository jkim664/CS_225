/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
        if (curDim > Dim) return false;
        
        if (first[curDim] == second[curDim]) return (first < second);
        
	return (first[curDim] < second[curDim]);
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
	
	
	if (distance(target, potential) == distance(target, currentBest) ) return (potential < currentBest);
	
	return ( distance(target, potential) < distance(target, currentBest) );
}


template<int Dim>
double KDTree<Dim>::distance(const Point<Dim> & a, const Point<Dim> & b) const
{
	
	double dist = 0;
	
	for (int i = 0; i < Dim; i++) {
	
		dist += pow( (a[i] - b[i]), 2);

	}
	
	return dist;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
	points = newPoints;
	
	build(0, points.size() - 1, 0);
}

template<int Dim>
void KDTree<Dim>::build(int lo, int hi, int curDim)
{
	
	if (lo > hi) return;
	
	curDim = curDim%Dim;
	
	int mid = (hi+lo)/2;
	
	int medIndex = setMedian(lo, hi, curDim, mid);
	
	build(lo, mid-1, curDim+1);
	
	build(mid+1, hi, curDim+1);
	
	
}

template<int Dim>
int KDTree<Dim>::setMedian(int lo, int hi, int curDim, int mid)
{
	if (lo == hi) return lo;
	
	int medIndex = (hi+lo)/2;
	
	int pivotNewIndex = partition(lo, hi, curDim, medIndex);
	
	if (pivotNewIndex == mid) {
	
		return pivotNewIndex;
		
	}
	
	else if (mid < pivotNewIndex) {
	
		return setMedian(lo, pivotNewIndex - 1, curDim, mid);
	}
	
	else { 
	
		return setMedian(pivotNewIndex + 1, hi, curDim, mid);
	}
	
	
}

template<int Dim>
int KDTree<Dim>::partition(int lo, int hi, int curDim, int mid)
{
	int pivotIndex = (hi+lo)/2;
	
	Point<Dim> pivotValue = (points[pivotIndex]);
	
	swap(pivotIndex, hi);
	
	int storeIndex = lo;
	
	for (int i = lo; i <= hi-1; i++) {
	
		if ( smallerDimVal(points[i], pivotValue, curDim) ) {
		
			swap(storeIndex, i);
			storeIndex++;
		}
	}
	
	swap(hi, storeIndex);
	
	return storeIndex;
	
	
}

template<int Dim>
void KDTree<Dim>::swap(int a, int b)
{
	Point<Dim> temp = points[a];
	points[a] = points[b];
	points[b] = temp;
	
}



template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{	
	
    	
	return nearestHelper(query, 0, points.size()-1, 0);
}


template<int Dim>
Point<Dim> KDTree<Dim>::nearestHelper(const Point<Dim> & query, int lo, int hi, int curDim) const
{
	int mid = (lo+hi)/2;
	curDim = curDim%Dim;
	Point<Dim> curr = points[mid];
	Point<Dim> curr_best;
	Point<Dim> curr_other;
	
	
	if (lo >= hi) {
		
		return curr;
	
	}
	
	if ( smallerDimVal(query, curr, curDim) ) {
	
		curr_best = nearestHelper(query, lo, mid-1, curDim+1);			//Recurse Left
			
		
	} else {
		
		curr_best = nearestHelper(query, mid+1, hi, curDim+1);			//Recurse Right
		
	}
	
	
	if ( shouldReplace(query, curr_best, curr) ) {
	
		
		curr_best = curr;
		
	}
	
	
	if ( pow( (query[curDim] - curr[curDim]), 2) <= distance(query, curr_best) ) {
		
	
		if (smallerDimVal(query, curr, curDim)  ) {
			
			curr_other = nearestHelper(query, mid+1, hi, curDim+1);			//go right
				
		}
			
		else {
		
			curr_other = nearestHelper(query, lo, mid-1, curDim+1);			//go left
				
		}
		
		if ( shouldReplace(query, curr_best, curr_other) ) {
		
			curr_best = curr_other;
		}
	}
		
	
	
	return curr_best;
	
}












