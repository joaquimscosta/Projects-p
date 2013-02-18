/*  QuickSort.cpp -- defines the interface for the QuickSort class
Joaquim Costa
April 19, 2012
CS 423 -- Algorithm Analisys*/

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>

class QuickSort
{
public:
	// define the type of pivot that the quicksort supports
	enum Pivot {LeftMost, RightMost, Median};
	
	/**this is the only method visible by the client
	 list -- the array of elements
	 pivotType -- specify the type of pivot to choose*/
	static unsigned long sort(std::vector<int> &list, Pivot pivotType);

private:
	static Pivot pivotType;
	static unsigned long totalComparison;
	static void sort(std::vector<int> &list, int left, int right);
	static int partitionLeftMost(std::vector<int> &list, int left, int right);
	static int partitionRightMost(std::vector<int> &list, int left, int right);
	static int partitionMedian(std::vector<int> &list, int left, int right);
	static void swap(std::vector<int> &list, int i, int j );
	static int getMedian(std::vector<int> &list, int left, int right);


	
};

#endif // QUICKSORT_H