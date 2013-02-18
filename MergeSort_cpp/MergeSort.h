/*  MergeSort.h -- defines the class interface
    Joaquim Costa
    April 04, 2012
    CS 423 -- Algorithm Analisys
*/


#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>

using std::vector;

class MergeSort
{
    private:
	
	// holds the count of total inversion
	static unsigned long inversion;

	// holds the temporary list so data can be processed 
	static vector<int> temp;
   
	// sorts each sublists
    static void sort(vector<int> &list, int left, int right);

	// merges the sorted sublists into the original list
    static void merge(vector<int> &list, int left, int mid, int right);

    public:
	
	// takes a list of integer and sortes the list
    static unsigned long sort(vector<int> &list);

	// this method use brute force to calculate inverstion in the list
	static unsigned long bruteInversion(const vector<int> list);
};

#endif  //MERGESORT_H