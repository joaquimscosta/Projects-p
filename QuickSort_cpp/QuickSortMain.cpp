/*  QuickSortMain.cpp -- uses the QuickSort class to sort lists
Joaquim Costa
April 19, 2012
CS 423 -- Algorithm Analisys

I HAVE DECIDED TO USE VECTOR INSTEAD OF ARRAY FOR SIMPLICITY
( do not have to worry about dynamic array, pointer, memory leaks,...)
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "QuickSort.h"


using namespace std;

// function prototype -- add the numbers from the file to a vector
void readData(vector<int> &list );

// run a batch test with multiple list sizes
void testBatch();

// run test for the specified list
void runTest(vector<int> &list);

// generate random numbers for the list
void generateNumber( vector<int> &list, int n);

// display the list elements in the console
void testLog(vector<int> list, string title = "Before Sort" );


/*Global variables
this is an instance of the logfile to be used trought the program*/
ofstream logFile("testOuputLog.txt");



int main( int argv, char* argc[])
{
	vector<int> list;
	list.reserve(200000);

	//check if any argument was passed
	if( argv > 1 )
	{
		// check if argume is equal to '-test'
		if(strcmp(argc[1], "-test" ) == 0)
		{
			testBatch();
			cout << "Test simulation is done check the log file to see the output\n file name 'testOuputLog.txt'" << endl;
		}
		else
		{
			cout << argc[0] << "-test\t Run the test batch. For debugging purpouse" << endl;
		}
	}
	else
	{
	    cout << "Writting to the logfile" <<endl;
		readData(list);
		logFile << "Total Comparison Median: " << QuickSort::sort(list, QuickSort::Median) << endl;

		readData(list);
		logFile << "Total Comparison LeftMost: " << QuickSort::sort(list, QuickSort::LeftMost) << endl;

		readData(list);
		logFile << "Total Comparison RightMost: " << QuickSort::sort(list, QuickSort::RightMost) << endl;

		testLog(list, "After Sort" );

		cout << "Done Writting to the log file \"testOuputLog.txt\"" <<endl;
	}


	// this is just to prevent the console from closing right way
	cout << "Press the RETURN key to exit." <<endl;
	getchar();

	// close log file
	logFile.close();
}


/* simply read the numbers from the text file and add them to the lists*/
void readData( vector<int> &list )
{
	ifstream in("data.txt");

	// display error if file was not found
	if(!in)
	{
		cout << "Error Reading file 'data.txt'";
		exit(-1);
	}


	int number;

	// iterate trought the file and add the the list
	while(!in.eof())
	{
		in >> number;
		list.push_back(number);
	}

	in.close();
}

/* Do a test batch for lists of different size -- for Debugging */
void testBatch()
{
	vector<int> list(200000);

	cout << "Running Test..." <<endl;

	// N = 100
	generateNumber(list, 10);
	testLog(list);
	runTest(list);
	testLog(list, "After Sort");

	// N = 1000
	generateNumber(list, 100);
	testLog(list);
	runTest(list);
	testLog(list, "After Sort");

	// N = 1000
	generateNumber(list, 1000);
	testLog(list);
	runTest(list);
	testLog(list, "After Sort");


	// N = 10000
	generateNumber(list, 10000);
	testLog(list);
	runTest(list);
	testLog(list, "After Sort");


	// N = 100000
	generateNumber(list, 100000);
	testLog(list);
	runTest(list);
	testLog(list, "After Sort");




}

/** Run a test for the giving list */
void runTest(vector<int> &list)
{
	int randTest = rand() % 3;

	unsigned long totalComparison = QuickSort::sort(list, (QuickSort::Pivot) randTest);

	switch(randTest)
	{
	case QuickSort::LeftMost:
		cout << "Tesing LeftMost Pivot" << endl;
		logFile << "Total Comparison LeftMost: " << totalComparison << endl;
		break;
	case QuickSort::RightMost:
		cout << "Tesing RightMost Pivot" << endl;
		logFile << "Total Comparison RightMost: " << totalComparison << endl;
		break;
	case QuickSort::Median:
		cout << "Tesing Median Pivot" << endl;
		logFile << "Total Comparison Median: " << totalComparison << endl;
		break;
	default:
		cout << "Error: Invalid Pivot Type" <<endl;
		exit(-1);
		break;
	}

}


/* this method return a list of n element contaning integers between 0 to 100000
for testing purpose*/
void generateNumber( vector<int> &list, int n)
{
	// clear all the content from the list and resize
	list.clear();
	list.resize(n);


	// seed the random number generator
	srand(time(0));

	// generate a random number 0 to 100000
	for( int i = 0; i < n; i++ )
	{
		list[i] = ((rand() % 100000));
	}
}

void testLog( vector<int> list, string title)
{
	// exit the program if the error writing to file
	if( !logFile)
	{
		cout << "Error writing to file" <<endl;
		exit(-1);
	}

	int size = list.size();

	logFile << title << endl;
	logFile << "List Size: " << size <<endl;

	//vector<int>::iterator it;
	//for ( it=list.begin() ; it < list.end(); it++ )
	for( int i = 0; i < size; i++ )
	{

		if( (i%10) == 0) logFile <<endl;
		logFile << setw(10) << list[i];
	}

	logFile <<endl <<endl;

}


//void testLog( vector<int> list, string title)
//{
//	int size = list.size();
//
//	cout << title << endl;
//	cout << "List Size: " << size <<endl;
//
//	vector<int>::iterator it;
//	for ( it=list.begin() ; it < list.end(); it++ )
//	for( int i = 0; i < size; i++ )
//	{
//
//		if( (i%10) == 0) cout <<endl;
//		cout << setw(10) << list[i];
//	}
//
//	cout <<endl <<endl;
//
//}
