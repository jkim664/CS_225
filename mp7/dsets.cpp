
#include "dsets.h"


void DisjointSets::addelements(int num)
{
	
	for (int i = 0; i < num; i++) {
	
		theVector.push_back(-1);
	
	}

}

int DisjointSets::find(int elem)
{
	if (theVector[elem] < 0) return elem;
	
	else return (theVector[elem] = find(theVector[elem]));

}

void DisjointSets::setunion(int a, int b)
{	
	if (a >= theVector.size() || b >= theVector.size() ) return;
	
	if (find(a) == find(b)) return;	
	
	int newSize = theVector[find(a)] + theVector[find(b)];
	
	if (theVector[find(a)] >= theVector[find(b)] ) {
		
		theVector[find(b)] = find(a);
		theVector[find(a)] = newSize;
	
	}
	else {
	
		theVector[find(a)] = find(b);
		theVector[find(b)] = newSize;
	
	}


}


