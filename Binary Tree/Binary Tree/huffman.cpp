/***********************************************************************
 * Module:
 *    Lesson 07, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include "huffman.h"       // for HUFFMAN() prototype
#include "pair.h"
#include "vector.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "bnode.h"     // your BinaryNode class should be in bnode.h

#include <fstream>         // needed for all file I/O programs
using namespace std;
/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
//template <typename T>
void huffman()
{
   char fileName[256];
   //create the tree
   Vector <Pair<string, float>> huffCodes;

   //get the filename
   cout << "Enter the filename containing the value frequencies: ";
   cin >> fileName;

   string line;
   ifstream myfile("C:\\Users\\cgood92\\Documents\\CS 235\\Binary Tree\\Binary Tree\\huffman1.txt");
   if (myfile.is_open())
   {
	   while (getline(myfile, line))
	   {
		   Pair<string, float> thisPair; //String: token, float: frequency
		   istringstream(line) >> thisPair;
		   huffCodes.push_back(thisPair);
	   }
	   myfile.close();
   }
   else
   {
	   cout << "Error opening file";
   }

   VectorIterator <Pair<string, float>> it;
   for (it = huffCodes.begin(); it != huffCodes.end(); ++it)
	   cout << "\t" << *it << endl;
   
   return;
}


