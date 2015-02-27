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

   int num_items_to_visit = huffCodes.size() - 1;

   bool exchange_made = false;
   do
   {
	   int last_marker = num_items_to_visit - 1;
	   for (int i = 0; i <= last_marker; i++)

		   if (huffCodes[i].getSecond() > huffCodes[i + 1].getSecond())
		   {
			   Pair<string, float> temp = huffCodes[i];
			   huffCodes[i] = huffCodes[i + 1];
			   huffCodes[i + 1] = temp;
			   exchange_made = true;
		   }
	   num_items_to_visit--;

   } while (exchange_made && (num_items_to_visit > 0));

   VectorIterator <Pair<string, float>> it;
   cout << "Sorted:\n";
   for (it = huffCodes.begin(); it != huffCodes.end(); ++it)
	   cout << "\t" << *it << endl;

   HuffmanTree current;
   current.miniTree.addLeft(huffCodes[0]);
   current.miniTree.addRight(huffCodes[1]);
   current.miniTree.data = Pair<string, float>("", huffCodes[0].getSecond() + huffCodes[1].getSecond());

   return;
}


