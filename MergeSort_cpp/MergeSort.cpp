/**
	MergeSort.cpp -- implements the class interface
    Joaquim Costa
    April 04, 2012
    CS 423 -- Algorithm Analisys
*/


#include "MergeSort.h"
#include <vector>

using std::vector;


// this vector will hold the temporary data from the list
vector<int> MergeSort::temp;

unsigned long MergeSort::inversion = 0;




/* this method merges the sorted sub-lists into the original list*/
void MergeSort::merge(vector<int> &list, int left, int mid, int right)
{
	// declare local variables
    int i = left, j = mid+1;

    // copy data from list to temp
    for( int k = left; k <= right; k++ )
    {
        temp[k] = list[k];
    }

	


    // compares the element in each list and then add them in sorted order
    for(int k = left; k <= right; k++)
    {
        if( i > mid)
            list[k] = temp[j++];
        else if( j > right)
            list[k] = temp[i++];

        else if( temp[j] < temp[i])
		{
            list[k] = temp[j++];

			// MOD -- to calculate the inversion
			inversion += (mid-i+1);		
		}

        else
            list[k] = temp[i++];
    }
}

/**
this method divides the list into two halves and sorts the lists recursively*/
void MergeSort::sort(vector<int> &list, int left, int right)
{
    if( right <= left ) return;

    int mid = (left+right)/2;		// the midpoint 
    sort(list, left, mid);			// first half
    sort(list, mid+1, right);		// second half
    merge(list, left, mid, right);	// merge the two halves back to the original list
}

/*this is the sorting list that does everything
1- initializes the temp list
2- invokes the helper methods which will sorts the sublist 
and then merges the sublist back into the original list
*/
unsigned long MergeSort::sort(vector<int> &list)
{
    int size = list.size();
	temp.resize(size);

	sort(list, 0, size-1);

	return inversion;
}

/* this is a brute force method that returns how many inverstion the list contains*/
unsigned long MergeSort::bruteInversion( const vector<int> list )
{
	int inv = 0;
	int n = list.size();

	// iterate trought the list and accumulate the inversion
	for(int i = 0; i < n-2; i++)
		for(int j = i+1; j < n-1; j++)
			if(list[i] > list[j]) inv++;

	return inv;
}