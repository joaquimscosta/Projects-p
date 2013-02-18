/*  MergeSortMain.h -- uses the MergeSort class to sort lists
Joaquim Costa
April 04, 2012
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


#include "MergeSort.h"

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
		cout << "This run will not use brute force to calculate the inversion," 
			<< "\nbecause the size of the list is too large, and it would take a\n" 
			<< "long time to finish. Use the command MergeSort -test if you want\n"
			<< "to run the test that will also run brute force.\n" << endl;

		cout << "START Reading File" <<endl;
		readData(list);
		cout << "END Reading File\nSTART sorting data." <<endl;
		
		cout << "\tTotal Inversions: " << MergeSort::sort(list) << "\nEND sorting data." <<endl;

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
	cout << "Run Test. Status success | failed" <<endl;

	// this is the lsit in the inversion slide -- inversion # should be 13
	vector<int> list;
	list.reserve(200000);
	list.push_back(3);
	list.push_back(7);
	list.push_back(10);
	list.push_back(14);
	list.push_back(18);
	list.push_back(19);
	list.push_back(2);
	list.push_back(11);
	list.push_back(16);
	list.push_back(17);
	list.push_back(23);
	list.push_back(25);


	testLog(list);		
	runTest(list);
	testLog(list, "After Sort");

	// N = 100
	generateNumber(list, 100);
	testLog(list);
	runTest(list);
	testLog(list, "After Sort");




	// N = 100
	generateNumber(list, 100);
	testLog(list);
	runTest(list);
	testLog(list, "After Sort");
	// N = 100
	generateNumber(list, 50);
	testLog(list);
	runTest(list);
	testLog(list, "After Sort");
	// N = 100
	generateNumber(list, 10);
	testLog(list);
	runTest(list);
	testLog(list, "After Sort");
	// N = 100
	generateNumber(list, 25);
	testLog(list);
	runTest(list);
	testLog(list, "After Sort");
	// N = 100
	generateNumber(list, 80);
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

}

/** Run a test for the giving list */
void runTest(vector<int> &list)
{

	unsigned long invBrute = MergeSort::bruteInversion(list);
	unsigned long invMerge = MergeSort::sort(list);
	string status =  (invBrute == invMerge) ? "success" : "failed";


	cout << "Brute inversion: " << invBrute << ", Merge Inversion: " << invMerge << ", Status: " << status << endl;
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