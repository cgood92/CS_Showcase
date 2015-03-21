/***********************************************************************
 * Module:
 *    Lesson 10, Sort Quick
 *    Brother Helfrich, CS 235
 * Author:
 *    <author>
 * Summary:
 *    This program will implement the Quick Sort
 ************************************************************************/

#ifndef SORT_QUICK_H
#define SORT_QUICK_H

#include <cassert>
#include <iostream>
using namespace std;

/*****************************************************
 * SORT QUICK
 * Perform the quick sort


 QUICK SORT
 In most situations, the quick sort is the fastest sort. The algorithm is inherently recursive in nature. The algorithm is presented and 
 discussed in Chapter 13.3 of the textbook. Note that there are many variations of the quick sort on the Internet. Some of these have bugs 
 or other quirks. Again, please do not blindly copy one off of the Internet. If you use an external source, make sure to cite it and make 
 sure you understand what every variable does. The filename needs to be sortQuick.h, and the function name needs to be sortQuick().
 ****************************************************/
//template<int> void sortQuick(int *& array, int low, int high);

//class SortValue;
//int partition(int *& array, int low, int high);
//void sortQuick(int *& array, int low, int high);
//int partition(SortValue *& array, int low, int high);
//void sortQuick(SortValue *& array, int low, int high);

//template <> void sortQuick<int>(int *& array, int low, int high);
//template <> int partition<int>(int *& array, int low, int high);
template <class T>
int partition(T *& array, int low, int high)
{
	T pivot = array[low];
	int left, right;
	for (left = low, right = high; left < right;)
	{
		for (; array[right] > pivot; right--) {}
		for (; right > left && (pivot > array[left] || pivot == array[left]); left++) {}
		if (right > left)
		{
			T swap = array[right];
			array[right] = array[left];
			array[left] = swap;
		}
	}
	array[low] = array[right];
	array[right] = pivot;
	return right;
}

template <class T>
void sortQuick(T *& array, int low, int high)
{
	if (low < high)
	{
		int part = partition(array, low, high);
		sortQuick(array, low, part - 1);
		sortQuick(array, part + 1, high);
	}
}


template <class T>
void sortQuick(T array[], int num)
{
	sortQuick(array, 0, num - 1);
}


#endif // SORT_QUICK_H
