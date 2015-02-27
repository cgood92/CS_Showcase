/***********************************************************************
 * Module:
 *    Lesson 07, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "pair.h"
#include "bnode.h"
#include <cassert>
#include <iostream>
#include <string>

/**********************************************************************
 * The HuffmanTree
 ***********************************************************************/
class HuffmanTree
{
  private:
  public:
	   BinaryNode < Pair<string, float> >  miniTree;
};
void huffman();

#endif // HUFFMAN_h
	