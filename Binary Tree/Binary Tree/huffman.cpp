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

string findInTree(HuffmanTree * master, string searchedFor, string encode);
string findInTree(BinaryNode< Pair<string, float> > * pTree, string searchedFor, string encode);

void huffman()
{
   char fileName[256];
   //create the tree
   Vector < Pair<string, float> > huffCodes;

   //get the filename
   cout << "Enter the filename containing the value frequencies: ";
   cin >> fileName;

   string line;
   ifstream myfile(fileName);
   if (myfile.is_open())
   {
	   while (getline(myfile, line))
	   {
		   stringstream  linestream(line);
		   Pair<string, float> thisPair; //String: token, float: frequency
		   linestream >> thisPair;
		   huffCodes.push_back(thisPair);
	   }
	   myfile.close();
   }
   else
   {
	   cout << "Error opening file";
   }

   HuffmanTree master;
   Vector <HuffmanTree> dTreesUnused;
   for (int i = 0; i < huffCodes.size(); ++i)
   {
	   dTreesUnused.push_back(HuffmanTree(huffCodes[i]));
   }
   while(dTreesUnused.size() > 1)
   {
	   HuffmanTree * lowest = new  HuffmanTree();
	   lowest->miniTree.data = Pair<string, float>("", 10000);
	   HuffmanTree * secondLowest = new HuffmanTree();
	   secondLowest->miniTree.data = Pair<string, float>("", 10001);
	   VectorIterator <HuffmanTree> delOne;
	   VectorIterator <HuffmanTree> delTwo;
	   for (VectorIterator <HuffmanTree> it = dTreesUnused.begin(); it != dTreesUnused.end(); ++it)
	   {
		   if ((*it).miniTree.data.getSecond() < lowest->miniTree.data.getSecond())
		   {
			   if (secondLowest->miniTree.data.getSecond() == lowest->miniTree.data.getSecond())
			   {
				   *secondLowest = *lowest;
				   delTwo = delOne;
			   }
			   else
			   {
				   *secondLowest = *lowest;
				   delTwo = delOne;
			   }
			   *lowest = *it;
			   delOne = VectorIterator <HuffmanTree>(it);
		   }
		   else if ((*it).miniTree.data.getSecond() < secondLowest->miniTree.data.getSecond())
		   {
			   *secondLowest = *it;
			   delTwo = VectorIterator <HuffmanTree> (it);
		   }
	   }
	   HuffmanTree * combined = new HuffmanTree();
	   combined->miniTree.addLeft(&lowest->miniTree);
	   combined->miniTree.addRight(&secondLowest->miniTree);
	   combined->miniTree.data = Pair<string, float>("", lowest->miniTree.data.getSecond() + secondLowest->miniTree.data.getSecond());

	   (*delOne) = *combined;
	   HuffmanTree test;
	   test = (*dTreesUnused.end());
	   (*delTwo) = (*(--(dTreesUnused.end())));
	   dTreesUnused.erase(dTreesUnused.end());
   }
   master = dTreesUnused[0];

   for (VectorIterator < Pair<string, float> > it = huffCodes.begin(); it != huffCodes.end(); ++it)
	{
		cout << (*it).getFirst() << " = " << findInTree(&master, (*it).getFirst(), "") << endl;
	}
   return;
}


string findInTree(HuffmanTree * master, string searchedFor, string encode)
{
	string toReturn = "";
	BinaryNode < Pair<string, float> > * pLeft = master->miniTree.pLeft;
	BinaryNode < Pair<string, float> > * pRight = master->miniTree.pRight;
	if (pRight)
	{
		if (pRight->data.getFirst() == searchedFor)
		{
			return encode + string("1");
		}
		toReturn += findInTree(pRight, searchedFor, encode + "1");
	}
	if (pLeft)
	{
		if (pLeft->data.getFirst() == searchedFor)
		{
			return encode + string("0");
		}
		toReturn += findInTree(pLeft, searchedFor, encode + "0");
	}
	
	return string("") + toReturn;
}

string findInTree(BinaryNode< Pair<string, float> > * pTree, string searchedFor, string encode)
{
	string toReturn = "";
	BinaryNode < Pair<string, float> > * pLeft = pTree->pLeft;
	BinaryNode < Pair<string, float> > * pRight = pTree->pRight;
	if (pRight)
	{
		if (pRight->data.getFirst() == searchedFor)
		{
			return encode + string("1");
		}
		toReturn += findInTree(pRight, searchedFor, encode + "1");
	}
	if (pLeft)
	{
		if (pLeft->data.getFirst() == searchedFor)
		{
			return encode + string("0");
		}
		toReturn += findInTree(pLeft, searchedFor, encode + "0");
	}

	return string("") + toReturn;
}