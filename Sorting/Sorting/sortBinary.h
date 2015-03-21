/***********************************************************************
 * Module:
 *    Lesson 10, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Clint Goodman and Parker Hubbard
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <cassert>
#include <iostream>   // for COUT, CIN, CERR
#include <string>
using namespace std;


/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   BST <T> tree2;
   for (int i = 0; i < num; i++)
   {
      tree2.insert(array[i]);
   }

   int i = 0;
   BSTIterator <T> it;
   for (it = tree2.begin(); it != tree2.end(); ++it)
   {
      array[i++] = *it;
   }
   
}


#endif // SORT_BINARY_H
