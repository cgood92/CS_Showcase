/***********************************************************************
 * Program:
 *    Lesson 7, Binary Search Tree
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef BST_H
#define BST_H

#include <cassert>
#include <iostream>
#include <string>
#include "bnode.h"
using namespace std;

template <class T>
class BSTIterator;


/**********************************************************************
 * Binary Node
 ***********************************************************************/
template <class T>
class BST
{
  private:
	  BinaryNode <T> * masterTree;
  public:
	  BST() {}
	  ~BST() {}
	  BST(const BST & rhs) {}
	  bool empty();
	  void insert() throw(const char *);
	  void remove();
	  void clear();
	  BSTIterator <T> & find();
	  BSTIterator <T> & begin();
	  BSTIterator <T> & end();
	  BSTIterator <T> & rbegin();
	  BSTIterator <T> & rend();
};



/**********************************************************************
* BSTIterator
***********************************************************************/
template <class T>
class BSTIterator
{
private:
	BinaryNode <T> * masterTree;
public:
	BSTIterator() {}
	BSTIterator(const BSTIterator & rhs)
	{
		*this = rhs;
	}
	BSTIterator & operator = (const BSTIterator & rhs)
	{
		this->masterTree = rhs.masterTree;
		return *this;
	}
	bool operator != (const BSTIterator & rhs) const
	{
		return rhs.masterTree != this->masterTree;
	}
	bool operator == (const BSTIterator & rhs) const
	{
		return rhs.masterTree == this->masterTree;
	}
	T & operator * ()
	{
		return masterTree->data;
	}
	BSTIterator <T> & operator -- ()
	{
		//masterTree = masterTree->pPrev;
		return *this;
	}
	BSTIterator <T> operator--(int prefix)
	{
		BSTIterator tmp(*this);
		//masterTree = masterTree->pPrev;
		return tmp;
	}
	BSTIterator <T> & operator ++ ()
	{
		//masterTree = masterTree->pNext;
		return *this;
	}
	BSTIterator <T> operator++(int postfix)
	{
		BSTIterator tmp(*this);
		//masterTree = masterTree->pNext;
		return tmp;
	}
	template <class TT>
	friend class BST;
};


#endif
