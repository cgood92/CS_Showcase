/***********************************************************************
 * Module:
 *    Lesson 09, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
void readFile(Map <string, int> & counts, const string & fileName)
{
	try
	{
		ifstream fin;
		fin.open(fileName.c_str());

		string line;
		while (getline(fin, line))
		{
			stringstream  linestream(line);
			string thisWord;
			while (linestream >> thisWord)
			{
				if (counts[thisWord].second != 0)
				{
					counts[thisWord].second = counts[thisWord].second + 1;
				}
				else
				{
					counts[thisWord] = 1;
				}
			}
		}
		fin.close();
	}
	catch (const char * error)
	{
		cout << error << endl;
	}
}

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
	//map for: 1) item to find, 2) number of times found
	Map <string, int> countMap;
	//iterator to go through the items on the map
	MapIterator <string, int> it;

	string fileName;
	string searchedWord;
	cout << "What is the filename to be counted? ";
	cin >> fileName;
	readFile(countMap, fileName);
	cout << "What word whose frequency is to be found. Type ! when done\n";

	do
	{
		cout << ">";
		cin >> searchedWord;
		cout << "\t" << searchedWord << " : " << countMap[searchedWord] << endl;
	} while (searchedWord != "!");
}