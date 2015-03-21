/***********************************************************************
 * Module:
 *    Lesson 10, Sort Merge
 *    Brother Helfrich, CS 235
 * Author:
 *    Clint Goodman and Parker Hubbard
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/
using namespace std;

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/*****************************************************
 * SORT MERGE
 * Perform the merge sort

 Create a function template representing the Merge Sort. There are several variations to the merge sort. The merge sort can be done in memory or in files. 
 You are to follow a file implementation. This means that you do not have to have the entire array in memory, you can work with a sub-set of the array at a 
 time. It does not mean that you have to write the array to a file. The merge sort can be done with arrays or with linked lists. You are to follow an array 
 implementation. There are binary merge sorts (requiring the array size to be a power of 2) or natural merge sorts (can be any size and takes advantage of 
 sub lists that are already sorted). You are to follow a natural implementation. Note that there is no pseudocode in the textbook for an array, memory, 
 natural merge sort. Please do not blindly copy one off of the Internet. If you use an external source, make sure to cite it and make sure you understand 
 what every variable does. The filename needs to be sortMerge.h, and the function name needs to be sortMerge().
 -Natural
 -File
 -Array
 -Don't write arrary to a file
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{
	string fn1 = "f1.txt";
	string fn2 = "f2.txt";
	string fn = "f.txt";
	ofstream f(fn.c_str(), ios::trunc);
	for (int i = 0; i < num; i++)
	{
		f << array[i] << " ";
	}
	f.close();
	sortMerge_split(array, num, fn1, fn2);
	convertFileToArray(array);
}

template <class T>
void sortMerge_split(T array[], int num, string fn1, string fn2)
{
	int index = 1;
	bool isSorted = true;
	ofstream f1, f2;
	ofstream * currentFile;
	f1.open(fn1.c_str(), ios::trunc);
	f2.open(fn2.c_str(), ios::trunc);
	
	ifstream f("f.txt");
	if (f.is_open())
	{
		T data;
		string line;
		getline(f, line);
		stringstream  linestream(line);
		linestream >> data;
		T pivot = data;
		currentFile = &f1;
		*currentFile << data << " ";
		while (linestream >> data)
		{
			if (pivot > data)
			{
				isSorted = false;
				if (currentFile == &f1)
				{
					currentFile = &f2;
				}
				else
				{
					currentFile = &f1;
				}
			}
			*currentFile << data << " ";
			pivot = data;
			index++;
		}
	}
	if (isSorted)
	{
		return;
	}
	f1.close();
	f2.close();
	sortMerge_merge(array, num, fn1, fn2);
}

template <class T>
void convertFileToArray(T array[])
{
	int i = 0;
	ifstream fin("f.txt");
	if (fin.is_open())
	{
		string line;
		while (getline(fin, line))
		{
			T data;
			stringstream  linestream(line);
			while (linestream >> data)
			{
				array[i++] = data;
			}
		}
		fin.close();
	}
}

template <class T>
void sortMerge_merge(T array[], int num, string fn1, string fn2)
{
	string f1line, f2line;
	bool outer1, outer2 = false;
	bool first = true;
	T object1, object2;
	ofstream f("f.txt", ios::trunc);
	ifstream f1(fn1.c_str());
	ifstream f2(fn2.c_str());
	int counter = 0;
	if (f1.is_open() && f2.is_open())
	{
		if (getline(f1, f1line) && getline(f2, f2line))
		{
			stringstream  linestream1(f1line);
			stringstream  linestream2(f2line);
			if (linestream1 >> object1)
			{
				outer1 = true;
			}
			if (linestream2 >> object2)
			{
				outer2 = true;
			}
			while (true)
			{
				if (outer1 && outer2)
				{
					if (object1 < object2)
					{
						f << object1 << " ";
						if (linestream1 >> object1)
						{
							outer1 = true;
						}
						else
						{
							outer1 = false;
						}
					}
					else
					{
						f << object2 << " ";
						if (linestream2 >> object2)
						{
							outer2 = true;
						}
						else
						{
							outer2 = false;
						}
					}
				}
				else if (!outer1 && !outer2)
				{
					break;
				}
				else if (!outer2)
				{
					f << object1 << " ";
					while (linestream1 >> object1)
					{
						f << object1 << " ";
					}
					break;
				}
				else if (!outer1)
				{
					f << object2 << " ";
					while (linestream2 >> object2)
					{
						f << object2 << " ";
					}
					break;
				}
				//Been sorted all the way
				if (first && !outer1 && !outer2)
				{
					f1.close();
					f2.close();
					f.close();
					return;
				}
				first = false;
				counter++;
			}
		}
	}
	f.close();
	sortMerge_split(array, num, fn1, fn2);
}



#endif // SORT_MERGE_H
