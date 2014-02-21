
#ifndef EDSETS_H
#define EDSETS_H


#include <vector>

using std::vector;



class DisjointSets
{
	public:
		
		void addelements(int num);	     	

		int find(int elem);

		void setunion(int a, int b);
	
	
	private:
	
		vector<int> theVector;



};

#endif
