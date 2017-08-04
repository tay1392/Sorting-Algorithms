/***********************************************************
* Author:					Taylor Caldwell	
* Date Created:				4/14/13
* Last Modification Date:	4/16/13
* Lab Number:				CST 211 Lab2
* Filename:					main.cpp
*
* Overview:
*	This program creates 3 different types of arrays
* 	and fills them with random values. These 3 arrays
* 	are then sorted using a variety of different types
*	of sorting algorithms including the BubbleSort,
* 	FlaggedBubbleSort, SelectionSort, InsertionSort,
*	HeapSort, ShellSort, BinaryInsertionSort
*	MergeSort, ShakerSort, and QuickSort.
*
* Input:
*	None. The size of the array is received from 
*	the command line arguments.
*
* Output:
*	 The output of the program is a series of
*	 messages to the console that indicate that 
* 	 a certain sort is complete. After each sort is
* 	 completed, the 100th element and the execution time
*	 is saved to a text file.
************************************************************/
#include <iostream>
#include <ctime>
#include "Array.h"
#include "Exceptions.h"
#include <algorithm> //used only for Swap function
#include <vector>
#include <stdlib.h>
#include <time.h>  
#include <fstream>
#include <chrono>
#include <thread>
#include <crtdbg.h> 
using std::ofstream;
using std::vector;
using std::fstream;
using std::cout;
using std::endl;
using std::swap;
#define _CRTDBG_MAP_ALLOC

const int ELEMENT = 1000;

template <typename T>
void SetArrays(T rand_array, T & sort_array, int n);

template <typename T>
void BinaryInsertionSort(T & the_array, int n);

template <typename T> 
void BubbleSort(T & the_array, int n);

template <typename T>
void ShakerSort(T & the_array, int n);

template<typename T>
void FlaggedBubbleSort(T & the_array, int n);

template <typename T>
void SelectionSort(T & the_array, int n);

template<typename T>
void InsertionSort(T & the_array, int n);

template <typename T>
void HeapSort(T & the_array, int n);

template<typename T>
void ShellSort(T & the_array, int n);

template <typename T>
void HeapSort(T & the_array, int n);
template <typename T>
void MoveDown(T & the_array, int index, int n);

template <typename T>
void MergeSort(T & the_array, int first, int last, int n);
template <typename T>
void Merge(T & the_array, int first, int last, int n);

template <typename T>
void QuickSort(T & the_array, int n);
template <typename T>
void QuickerSort(T & the_array, int first, int last);

template <typename T>
void WriteToFile(T & the_array, char * message, double time);

template<typename T>
void FillArray(T & EmptyArray, int n);
template <typename T>
void DisplayArray(T SortedAray, char * msg, int time);

int main(int argc, char * argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	const int n = atoi(argv[1]);

	int * TestArray1 = new int[n];
	vector<int>TestArray2(n);
	Array<int>TestArray3(n);

	int * RandNative = new int[n];
	vector<int>RandVect(n);
	Array<int>RandClass(n);

	FillArray(RandNative, n);
	FillArray(RandVect, n);
	FillArray(RandClass, n);

	//Brute Force Bubblesorts
	SetArrays(RandNative, TestArray1, n);
	auto START = std::chrono::high_resolution_clock::now();
	BubbleSort(TestArray1, n);
	auto STOP = std::chrono::high_resolution_clock::now();
	double TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		          (STOP-START).count();
	WriteToFile(TestArray1, "BUBBLESORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);
	DisplayArray(TestArray1, "BUBBLESORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);
	
	SetArrays(RandVect, TestArray2, n);
	START = std::chrono::high_resolution_clock::now();
	BubbleSort(TestArray2, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		          (STOP-START).count();
	WriteToFile(TestArray2, "BUBBLESORT INTEGER VECTOR ARRAY 2", TIME);
	DisplayArray(TestArray2, "BUBBLESORT INTEGER VECTOR ARRAY 2", TIME);

	SetArrays(RandClass, TestArray3, n);
	START = std::chrono::high_resolution_clock::now();
	BubbleSort(TestArray3, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray3, "BUBLESORT ARRAY CLASS INTEGER ARRAY 3", TIME);
	DisplayArray(TestArray3, "BUBLESORT ARRAY CLASS INTEGR ARRAY 3", TIME);

	cout << "\nBUBBLE SORTS DONE." << endl;

	//Flagged Bubble Sorts
	SetArrays(RandNative, TestArray1, n);
	START = std::chrono::high_resolution_clock::now();
	FlaggedBubbleSort(TestArray1, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray1, "FLAGGED BUBBLESORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);
	DisplayArray(TestArray1, "FLAGGED BUBBLESORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);

	SetArrays(RandVect, TestArray2, n);
	START = std::chrono::high_resolution_clock::now();
	FlaggedBubbleSort(TestArray2, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray2, "FLAGGED BUBBLESORT INTEGER VECTOR ARRAY 2", TIME);
	DisplayArray(TestArray2, "FLAGGED BUBBLESORT INTEGER VECTOR ARRAY 2", TIME);

	SetArrays(RandClass, TestArray3, n);
	START = std::chrono::high_resolution_clock::now();
	FlaggedBubbleSort(TestArray3, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray3, "FLAGGED BUBLESORT ARRAY CLASS INTEGER ARRAY 3", TIME);
	DisplayArray(TestArray3, "FLAGGED BUBLESORT ARRAY CLASS INTEGER ARRAY 3", TIME);

	cout << "\nFLAGGED BUBBLE SORTS DONE." << endl;

	//Shaker Sorts - extra credit
	SetArrays(RandNative, TestArray1, n);
	START = std::chrono::high_resolution_clock::now();
	ShakerSort(TestArray1, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray1, "SHAKER SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);
	DisplayArray(TestArray1, "SHAKER SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);

	SetArrays(RandVect, TestArray2, n);
	START = std::chrono::high_resolution_clock::now();
	ShakerSort(TestArray2, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray2, "SHAKER SORT INTEGER VECTOR ARRAY 2", TIME);
	DisplayArray(TestArray2, "SHAKER SORT INTEGER VECTOR ARRAY 2", TIME);

	SetArrays(RandClass, TestArray3, n);
	START = std::chrono::high_resolution_clock::now();
	ShakerSort(TestArray3, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray3, "SHAKER SORT ARRAY CLASS INTEGER ARRAY 3", TIME);
	DisplayArray(TestArray3, "SHAKER SORT ARRAY CLASS INTEGER ARRAY 3", TIME);
	
	cout << "\nSHAKER SORTS DONE." << endl;

	//Binary Insertion Sorts - extra credit
	SetArrays(RandNative, TestArray1, n);
	START = std::chrono::high_resolution_clock::now();
	BinaryInsertionSort(TestArray1, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray1, "BINARY INSERTION SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);
	DisplayArray(TestArray1, "BINARY INSERTION SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);

	SetArrays(RandVect, TestArray2, n);
	START = std::chrono::high_resolution_clock::now();
	BinaryInsertionSort(TestArray2, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray2, "BINARY INSERTION SORT INTEGER VECTOR ARRAY 2", TIME);
	DisplayArray(TestArray2, "BINARY INSERTION SORT INTEGER VECTOR ARRAY 2", TIME);

	SetArrays(RandClass, TestArray3, n);
	START = std::chrono::high_resolution_clock::now();
	BinaryInsertionSort(TestArray3, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray3, "BINARY INSERTION ARRAY CLASS INTEGER ARRAY 3", TIME);
	DisplayArray(TestArray3, "BINARY INSERTION SORT ARRAY CLASS INTEGER ARRAY 3", TIME);
	
	cout << "\nBINARY INSERTION SORTS DONE." << endl;

	// Selection Sorts
	SetArrays(RandNative, TestArray1, n);
	START = std::chrono::high_resolution_clock::now();
	SelectionSort(TestArray1, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray1, "SELECTION SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);
	DisplayArray(TestArray1, "SELECTION SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);

	SetArrays(RandVect, TestArray2, n);
	START = std::chrono::high_resolution_clock::now();
	SelectionSort(TestArray2, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray2, "SELECTION SORT INTEGER VECTOR ARRAY 2", TIME);
	DisplayArray(TestArray2, "SELECTION SORT INTEGER VECTOR ARRAY 2", TIME);

	SetArrays(RandClass, TestArray3, n);
	START = std::chrono::high_resolution_clock::now();
	SelectionSort(TestArray3, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray3, "SELECTION SORT ARRAY CLASS INTEGER ARRAY 3", TIME);
	DisplayArray(TestArray3, "SELECTION SORT ARRAY CLASS INTEGR ARRAY 3", TIME);

	cout << "SELECTION SORTS DONE." << endl;

	//Insertion Sorts
	SetArrays(RandNative, TestArray1, n);
	START = std::chrono::high_resolution_clock::now();
	InsertionSort(TestArray1, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray1, "INSERTION SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);
	DisplayArray(TestArray1, "INSERTION SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);

	SetArrays(RandVect, TestArray2, n);
	START = std::chrono::high_resolution_clock::now();
	InsertionSort(TestArray2, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray2, "INSERTION SORT INTEGER VECTOR ARRAY 2", TIME);
	DisplayArray(TestArray2, "INSERTION SORT INTEGER VECTOR ARRAY 2", TIME);

	SetArrays(RandClass, TestArray3, n);
	START = std::chrono::high_resolution_clock::now();
	InsertionSort(TestArray3, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray3, "INSERTION SORT ARRAY CLASS INTEGER ARRAY 3", TIME);
	DisplayArray(TestArray3, "INSERTION SORT ARRAY CLASS INTEGER ARRAY 3", TIME);

	cout << "INSERTION SORTS DONE." << endl;

	//Shell Sorts
	SetArrays(RandNative, TestArray1, n);
	START = std::chrono::high_resolution_clock::now();
	ShellSort(TestArray1, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray1, "SHELL SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);
	DisplayArray(TestArray1, "SHELL SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);
	
	SetArrays(RandVect, TestArray2, n);
	START = std::chrono::high_resolution_clock::now();
	ShellSort(TestArray2, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray2, "SHELL SORT INTEGER VECTOR ARRAY 2", TIME);
	DisplayArray(TestArray2, "SHELL SORT INTEGER VECTOR ARRAY 2", TIME);

	SetArrays(RandClass, TestArray3, n);
	START = std::chrono::high_resolution_clock::now();
	ShellSort(TestArray3,n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray3, "SHELL SORT ARRAY CLASS INTEGER ARRAY 3", TIME);
	DisplayArray(TestArray3, "SHELL SORT ARRAY CLASS INTEGER ARRAY 3", TIME);

	cout << "SHELL SORTS DONE." << endl;

	//Heap Sorts
	SetArrays(RandNative, TestArray1, n);
	START = std::chrono::high_resolution_clock::now();
	HeapSort(TestArray1, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray1, "HEAP SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);
	DisplayArray(TestArray1, "HEAP SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);

	SetArrays(RandVect, TestArray2, n);
	START = std::chrono::high_resolution_clock::now();
	HeapSort(TestArray2, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray2, "HEAP SORT INTEGER VECTOR ARRAY 2", TIME);
	DisplayArray(TestArray2, "HEAP SORT INTEGER VECTOR ARRAY 2", TIME);

	SetArrays(RandClass, TestArray3, n);
	START = std::chrono::high_resolution_clock::now();
	HeapSort(TestArray3, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray3, "HEAP SORT ARRAY CLASS INTEGER ARRAY 3", TIME);
	DisplayArray(TestArray3, "HEAP SORT ARRAY CLASS INTEGER ARRAY 3", TIME);

	cout << "HEAP SORTS DONE." << endl;

	//Merge Sorts
	SetArrays(RandNative, TestArray1, n);
	START = std::chrono::high_resolution_clock::now();
	MergeSort(TestArray1,0, n-1, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray1, "MERGE SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);
	DisplayArray(TestArray1, "MERGE SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);

	SetArrays(RandVect, TestArray2, n);
	START = std::chrono::high_resolution_clock::now();
	MergeSort(TestArray2,0, n-1, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray2, "MERGE SORT INTEGER VECTOR ARRAY 2", TIME);
	DisplayArray(TestArray2, "MERGE SORT INTEGER VECTOR ARRAY 2", TIME);

	SetArrays(RandClass, TestArray3, n);
	START = std::chrono::high_resolution_clock::now();
	MergeSort(TestArray3,0,n -1, n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray3, "MERGE SORT ARRAY CLASS INTEGER ARRAY 3", TIME);
	DisplayArray(TestArray3, "MERGE SORT ARRAY CLASS INTEGER ARRAY 3", TIME);

	cout << "MERGE SORTS DONE." << endl;

	//Quick Sorts
	SetArrays(RandNative, TestArray1, n);
	START = std::chrono::high_resolution_clock::now();
	QuickSort(TestArray1,n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray1, "QUICK SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);
	DisplayArray(TestArray1, "QUICK SORT PRIMITIVE C++ INTEGER ARRAY 1", TIME);

	SetArrays(RandVect, TestArray2, n);
	START = std::chrono::high_resolution_clock::now();
	QuickSort(TestArray2,n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray2, "QUICK SORT INTEGER VECTOR ARRAY 2", TIME);
	DisplayArray(TestArray2, "QUICK SORT INTEGER VECTOR ARRAY 2", TIME);

	SetArrays(RandClass, TestArray3, n);
	START = std::chrono::high_resolution_clock::now();
	QuickSort(TestArray3,n);
	STOP = std::chrono::high_resolution_clock::now();
	TIME = std::chrono::duration_cast<std::chrono::milliseconds>
		        (STOP-START).count();
	WriteToFile(TestArray3, "QUICK SORT ARRAY CLASS INTEGER ARRAY 3", TIME);
	DisplayArray(TestArray3, "QUICK SORT ARRAY CLASS INTEGER ARRAY 3", TIME);
	cout << "QUICK SORTS DONE." << endl;

	delete [] TestArray1;
	delete [] RandNative;

	system("pause");
	return 0;
}
/***********************************************************
* Name: BubbleSort
*
* Parameters: The Data Array (passed by pointer)
*
* Return: None
*
* Purpose: Sorting an array using BubbleSort Algorithm
*
************************************************************/
template <typename T>
void BubbleSort(T & the_array, int n)
{
	int temp;

	for(int x=0; x<n; x++)
	{
		for(int y=0; y<n-1; y++)
		{
			if(the_array[y]>the_array[y+1])
			{
				temp = the_array[y+1];
				the_array[y+1] = the_array[y];
				the_array[y] = temp;
			}
		}
	}
}
/***********************************************************
* Name: Flagged BubbleSort
*
* Parameters: The Data Array (passed by Reference)
*
* Return: None
*
* Purpose: Sorts an array using Flagged BubbleSort Algorithm
*
************************************************************/
template <typename T>
void FlaggedBubbleSort(T & the_array, int n)
{
	int Temp;
	bool flag = true;

	for(int i = 0; i < n || flag == true; i++)
	{
		flag = false;

		for(int j = 0; j < n - i - 1; j++)
		{
			if(the_array[j] > the_array[j + 1])
			{
				Temp = the_array[j];
				the_array[j] = the_array[j + 1];
				the_array[j + 1] = Temp;
				flag = true;
			}
		}
	}
}
/***********************************************************
* Name: Selection Sort
*
* Parameters: The Data Array (passed by Reference)
*
* Return: None
*
* Purpose: Sorts an array using Selection Sort Algorithm
*
************************************************************/
template <typename T>
void SelectionSort(T & the_array, int n) 
{
	for (int i = 0; i < n; i++)
	{
		int smallest = i;
		 for (int j = i + 1; j < n; j++)
		 {
			if (the_array[j] < the_array[smallest])
			{
				smallest = j;
			}
		 }
		swap(the_array[i], the_array[smallest]);
	}
}
/***********************************************************
* Name: Insertion Sort
*
* Parameters: The Data Array (passed by Reference)
*
* Return: None
*
* Purpose: Sorts an array using Insertion Sort Algorithm
*
************************************************************/
template <typename T>
void InsertionSort(T & the_array, int n)
{
	int temp(0);
	int j(0);

	for(int i = 1; i < n; i++)
	{
		temp = the_array[i];

		for(j = i; j > 0 && temp < the_array[j-1]; j--)
		{
			the_array[j] = the_array[j-1];
		}
		the_array[j] = temp;
	}
}
/***********************************************************
* Name: Shell Sort
*
* Parameters: The Data Array (passed by Reference)
*
* Return: None
*
* Purpose: Sorts an array using Shell Sort Algorithm
*
************************************************************/
template <typename T>
void ShellSort(T & the_array, int n) 
{

	int i, j, hcnt, h;
	int increments[20], k;
	
	for(h = 1, i = 0; h < n; i++)
	{
		increments[i] = h;
		h = 3 * h + 1;
	}

	for(i--; i >= 0; i--)
	{
		h = increments[i];

		for(hcnt = h; hcnt < 2 * h; hcnt++)
		{
			for(j = hcnt; j < n;)
			{
				int temp = the_array[j];
				k = j;

				while(k-h >= 0 && temp < the_array[k-h])
				{
					the_array[k] = the_array[k-h];
					k-=h;
				}
				the_array[k] = temp;
				j += h;
			}
		}
	}
}
/***********************************************************
* Name: Heap Sort
*
* Parameters: The Data Array (passed by Reference)
*
* Return: None
*
* Purpose: Sorts an array using Heap Sort Algorithm
*
************************************************************/
template <typename T>
void HeapSort(T & the_array, int n)
{
	//Build the heap
	for(int i = (n-2)/2; i >= 0; --i)
	{
		MoveDown(the_array, i, n);
	}

	//sort the heap
	for(int i = n - 1; i; --i)
	{
		swap(the_array[i], the_array[0]);
		MoveDown(the_array, 0, i);
	}
}

/***********************************************************
* Name: MoveDown
*
* Parameters: The Data Array (passed by Reference), 
*			  First index, Last index
*
* Return: None
*
* Purpose: Moves elements from calls within HeapSort
************************************************************/
template <typename T>
void MoveDown(T & the_array, int index, int n)
{
	int root(0);
	int child(0);
	bool done = true;

	root = index;

	while((root *2) + 1 < n && done == true)
	{
		child = (2 * root) + 1;
		if((child + 1) < n && the_array[child] < the_array[child + 1])
		{
			++child;
		}
		if(the_array[root] < the_array[child])
		{
			swap(the_array[child], the_array[root]);
			root = child;
		}
		else
		{
			done = false;
		}
	}
}
/***********************************************************
* Name: MergeSort
*
* Parameters: The Data Array (passed by Reference),
*			  the first index, and last (length)
*
* Return: None
*
* Purpose: Sorts the array with Merge Sort Algorithm
************************************************************/
template <typename T>
void MergeSort(T & the_array, int first, int last, int n)
{
	int mid;

	if(first < last)
	{
		mid = (first+last)/2;
		MergeSort(the_array, first, mid, n);
		MergeSort(the_array, mid + 1, last, n);
		Merge(the_array, first, last, n);
	}
}
/***********************************************************
* Name: Merge
*
* Parameters: The Data Array (passed by Reference)
*			  first elem, last elem, size of array n
*
* Return: None
*
* Purpose: used with the MergeSort Algorithm
*
************************************************************/
template <typename T>
void Merge(T & the_array, int first, int last, int n)
{
	int middle;
	middle = (first+last)/2;
	int i1 = 0;
	int i2 = first;
	int i3 = (middle+1);

	int * temp = new int[n];
	
	while(i2 <= middle && i3 <= last)
	{
		if(the_array[i2] < the_array[i3])
		{
			temp[i1++] = the_array[i2++];
		}
		else
		{
			temp[i1++] = the_array[i3++];
		}
	}

	while( i2 <= middle)
	{
		temp[i1++] = the_array[i2++];
	}
	while(i3 <= last)
	{
		temp[i1++] = the_array[i3++];
	}
	for(int i = first; i <= last; i++)
	{
		the_array[i] = temp[i-first];
	}
	
	delete [] temp;
}
/***********************************************************
* Name: QuickerSort
*
* Parameters: The Data Array (passed by Reference),
*			  first element, array size n
*
* Return: None
*
* Purpose: Sorts an array using QuickSort Algorithm
*
************************************************************/
template <typename T>
void QuickerSort(T & the_array, int first, int last)
{
	int lower = first +1;
	int upper = last;
	swap(the_array[first], the_array[(first+last)/2]);
	int bound = the_array[first];
	
	while(lower <= upper)
	{
		while(the_array[lower] < bound)
		{
			lower++;
		}
		while(bound < the_array[upper])
		{
			upper--;
		}
		if(lower < upper)
		{
			swap(the_array[lower++], the_array[upper--]);
		}
		else
		{
			lower++;
		}
	}
	swap(the_array[upper], the_array[first]);
	if(first < upper -1)
	{
		QuickerSort(the_array, first, upper-1);
	}
	if(upper+1 < last)
	{
		QuickerSort(the_array, upper+1, last);
	}
}
/***********************************************************
* Name: QuickSort
*
* Parameters: The Data Array (passed by Reference),
*			  array size n
*
* Return: None
*
* Purpose: Sorts an array using QuickSort Algorithm
*
************************************************************/
template <typename T>
void QuickSort(T & the_array, int n)
{
	int i, max;

	if(n >= 2)
	{
		for(i = 1, max = 0; i < n; i++)
		{
			if(the_array[max] < the_array[i])
			{
				max = i;
			}
		}
		swap(the_array[n-1], the_array[max]);
		QuickerSort(the_array, 0, n-2);
	}
	else
	{
		cout << "N must be > 2" << endl;
	}
}

/***********************************************************
* Name: ShakerSort
*
* Parameters: The Data Array, int n (size of array)
*
* Return: None
*
* Purpose: Sorts an array using the ShakerSort algorithm
************************************************************/
template <typename T>
void ShakerSort(T & the_array, int n)
{
	for(int i = 1; i <= n/2; i++)
	{
		for(int j = i -1; j < n - i; j++)
		{
			if(the_array[j] > the_array[j+1])
			{
				swap(the_array[j], the_array[j+1]);
			}

		}

		for(int x = n - i - 1; x >= i; x--)
		{
			if(the_array[x] < the_array[x-1])
			{
				swap(the_array[x], the_array[x-1]);
			}
		}
	}
}
/***********************************************************
* Name: BinaryInsertionSort
*
* Parameters: The Data Array, int n (size of array)
*
* Return: None
*
* Purpose: Sorts an array using the Binary 
*		   insertion algorithm
************************************************************/
template <typename T>
void BinaryInsertionSort(T & the_array, int n)
{
	for(int i = 0; i < n; i++)
	{
		int temp = the_array[i];
		int left = 0;
		int right = i;

		while(left < right)
		{
			int middle = (left+right)/2;

			if(temp > the_array[middle])
			{
				left = middle + 1;
			}
			else
			{
				right = middle;
			}
		}
		for(int j = i; j > left; j--)
		{
			swap(the_array[j-1], the_array[j]);
		}
	}
}
/***********************************************************
* Name: DisplayArray
*
* Parameters: The Data Array, char * message, int time
*
* Return: None
*
* Purpose: Displays the name, execution time, and 1000th
*		   element of the array to the screen
************************************************************/
template <typename T>
void DisplayArray(T SortedArray, char * msg, int time)
{
	cout << endl;
	cout << msg << endl;
	cout << "ELEMENT 1000: " << SortedArray[1000] << endl;
	cout << "ELEMENT 2000: " << SortedArray[2000] << endl;
	cout << "ELEMENT 3000: " << SortedArray[3000] << endl;
	cout << "ELEMENT 4000: " << SortedArray[4000] << endl;
	cout << "ELEMENT 5000: " << SortedArray[4999] << endl;//change back to 1000
	cout << "EXECUTION TIME: " << time << " MILLISECONDS." << endl;
}
/***********************************************************
* Name: FillArray
*
* Parameters: The Data Array (passed by Reference),
*			  array size n
*
* Return: None
*
* Purpose: Fills the arrays with random integer values 
*			between 0 and 1000
************************************************************/
template <typename T>
void FillArray(T & EmptyArray, int n)
{
	srand (time(0));
	for(int i = 0; i < n; i++)
	{
		EmptyArray[i] = rand()%ELEMENT;
	}
}
/***********************************************************
* Name: WriteToFile
*
* Parameters: The Data Array (passed by Reference),
*			  char * message , time integer
*
* Return: None
*
* Purpose: Writes the Algorithm time report to a txt file
*
************************************************************/
template <typename T>
void WriteToFile(T & the_array, char * message, double time)
{
	ofstream Report("Data.txt", fstream::app);

	if(Report.is_open())
	{
		Report << endl << message << endl;
		Report << "ELEMENT 1000: " << the_array[1000] << endl;
		Report << "ELEMENT 2000: " << the_array[2000] << endl;
		Report << "ELEMENT 3000: " << the_array[3000] << endl;
		Report << "ELEMENT 4000: " << the_array[4000] << endl;
		Report << "ELEMENT 5000: " << the_array[4999] << endl;//change back to 1000
		Report << "Execution Time: " << time << " milliseconds." << endl;
		Report.close();
	}
	else
	{
		cout << "Error: could not open file." << endl;
	}
}
/***********************************************************
* Name: SetArray
*
* Parameters: The Data Array, the Random Array,
*			  array size n.
*			  
* Return: None
*
* Purpose: Sets the sorted array back to random
*		   values in the random array generated before
*
************************************************************/
template <typename T>
void SetArrays(T Rand_array, T & Sort_array, int n)
{
	for(int i = 0; i < n; i++)
	{
		Sort_array[i] = Rand_array[i];
	}
}