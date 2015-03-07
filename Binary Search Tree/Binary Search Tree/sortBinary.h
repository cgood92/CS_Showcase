/***********************************************************************
 * Module:
 *    Lesson 08, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Clint Goodman and Parker Hubbard
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T inArray[], int num)
{
	BST <T> tree;
	for (int i = 0; i < num; i++)
	{
		tree.insert(inArray[i]);
	}

	int i = 0;
	BSTIterator <T> it;
	for (it = tree.begin(); it != tree.end(); ++it)
		inArray[i++] = *it;
}


#endif // SORT_BINARY_H
