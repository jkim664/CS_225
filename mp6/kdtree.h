/**
 * @file kdtree.h
 * KDTree implementation using Points in k-dimensional space.
 *
 * @author Cinda Heeren
 * @author Jack Toole
 * @author Sean Massung
 * @date Spring 2009
 * 
 * Revision history:
 * 3/31/2009     Created
 * 11/10/2009    Modified for MP6 Submission, Fall 2009
 * July 2012     Modified by Sean Massung to remove points_index, forbid
 *                 students from using std::sort, and generally clean up code
 */

#ifndef _KDTREE_H_
#define _KDTREE_H_

#include <vector>
#include <math.h>
#include "coloredout.h"
#include "point.h"

using std::vector;
using std::string;
using std::ostream;
using std::cout;
using std::endl;

/**
 * KDTree class: implemented using Points in Dim dimensional space (given
 * by the template parameter).
 */
template<int Dim>
class KDTree
{
    public:
        
        bool smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const;

        
        bool shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest,
                const Point<Dim> & potential) const;
        
        
        KDTree(const vector< Point<Dim> > & newPoints);
        
        
        Point<Dim> findNearestNeighbor(const Point<Dim> & query) const;

        // functions used for grading:
        
        /**
         * You do not need to modify this function. Its implementation is in kdtree_extras.cpp.
         * Prints the KDTree to the terminal in a pretty way. 
         */
        void printTree(ostream & out = cout, colored_out::enable_t enable_bold = colored_out::COUT,
                int modWidth = -1) const;
        
        /**
         * You do not need to modify this function. Its implementation is in kdtree_extras.cpp.
         * Prints a tree to a stream.
         * @param out The stream to print to
         */
        void gradingPrint(std::ostream & out) const;

    private:
        /** This is your KDTree representation. Modify this vector to create a KDTree. */
        vector< Point<Dim> > points;

        /** Helper function for grading */
        int getPrintData(int low, int high) const;
        
        
        
        double distance(const Point<Dim> & a, const Point<Dim> & b) const;
        
        void build(int lo, int hi, int curDim);
        
        int setMedian(int lo, int hi, int curDim, int mid);
        
        int partition(int lo, int hi, int curDim, int mid);
        
        void swap(int a, int b);
        
        Point<Dim> nearestHelper(const Point<Dim> & query, int lo, int hi, int curDim) const;
        
        
        /** Helper function for grading */
        void printTree(int low, int high, std::vector<std::string> & output,
                int left, int top, int width, int currd) const;

        /**
         * @todo Add your helper functions here.
         */
};

#include "kdtree.cpp"
#include "kdtree_extras.cpp"
#endif
