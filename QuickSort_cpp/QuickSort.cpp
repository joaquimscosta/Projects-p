/*
QuickSort.cpp -- implements the QuickSort class
Joaquim Costa
April 19, 2012
CS 423 -- Algorithm Analisys*/

#include "QuickSort.h"
#include <iostream>
#include <vector>


using std::vector;

// the variable that specifies which version of quicksort to use
QuickSort::Pivot QuickSort::pivotType;	// define here simply to let the linker know it exists

// hold the totalComparison made
unsigned long QuickSort::totalComparison;

/**
performs the sorting */
unsigned long QuickSort::sort( vector<int> &list, Pivot type )
{
	totalComparison = 0;
	pivotType = type;

	sort(list, 0, list.size()-1);

	return totalComparison;
}

/**perform the left most partition*/
int QuickSort::partitionLeftMost( vector<int> &list, int left, int right )
{
	int pivot = list[left];	// choose left most element as the pivot
	int i = left + 1;

	for( int j = left+1; j <= right; j++)
	{
		if(list[j] < pivot)
		{
			swap(list, i,j);
			i++;
		}

		totalComparison++; // keep track of total numbers of comparisons
	}

	swap(list, left, (i-1));	// swap the pivot with element at index(i-1)
	return (i-1);				// final index of the pivot
}

/**
perform the right most partion*/
int QuickSort::partitionRightMost( vector<int> &list, int left, int right )
{
	swap(list, left, right);

	// choose the right most element as the pivot,
	// left was swapped with right, so now left is right
	int pivot = list[left];
	int i = left + 1;

	for( int j = left+1; j <= right; j++)
	{
		if(list[j] < pivot)
		{
			swap(list, i,j);
			i++;
		}

		totalComparison++; // keep track of total numbers of comparisons
	}

	swap(list, left, (i-1));	// swap the pivot with element at index(i-1)
	return (i-1);				// final index of the pivot
}

/**
permorm the median partion*/
int QuickSort::partitionMedian( vector<int> &list, int left, int right )
{
		int pivot = getMedian(list, left, right);

		int i = left + 1;

		for( int j = left+1; j <= right; j++)
		{
			if(list[j] < pivot)
			{
				swap(list, i,j);
				i++;
			}

			totalComparison++; // keep track of total numbers of comparisons
		}

		swap(list, left, (i-1));	// swap the pivot with element at index(i-1)
		return (i-1);				// final index of the pivot
}

/**
selects which partition to use and perform the sort,
i did it this way so i can reuse the other methods, but this is not more efficient
because i will have to check for pivot type every time the partition is called*/
void QuickSort::sort( vector<int> &list, int left, int right)
{
	if(right <= left) return;

	// select the partition version to use
	int j = 0;
	switch(pivotType)
	{
	case LeftMost:
		j = partitionLeftMost(list, left, right );	// partition
		break;
	case RightMost:
		j = partitionRightMost(list, left, right);
		break;
	case Median:
		j = partitionMedian(list, left, right);
		break;
	default:
		std::cout << "Erro Invalid Partion Type" << std::endl;
		//exit(-1);
		break;
	}

	sort(list, left, j-1);					// sort the left part list [left...j-1]
	sort(list, j+1, right);					// sort right part list[j+1...right]
}


/**
swaps the two elements in the list*/
void QuickSort::swap(vector<int> &list, int i, int j)
{
	int temp = list[i];
	list[i] = list[j];
	list[j] = temp;
}

/**
find the medium of 3 and return the value*/
int QuickSort::getMedian(vector<int> &list, int left, int right)
{
	int center = (left + right) / 2;
	// order left & center
	if (list[left] > list[center])
		swap(list, left, center);
	// order left & right
	if (list[left] > list[right])
		swap(list, left, right);
	// order center & right
	if (list[center] > list[right])
		swap(list, center, right);

	swap(list, left, center); // put pivot on left
	return list[left]; // return median value
}
