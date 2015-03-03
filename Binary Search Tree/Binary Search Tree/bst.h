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
	  BST()
	  {
	  }
	  BST(const BST & rhs)
	  {
		  this->masterTree = new BinaryNode <T>();
		  BinaryNode <T> * currentNodeRHS = rhs.masterTree;
		  BinaryNode <T> * currentNodeLHS = this->masterTree;
		  this->masterTree->data = rhs.masterTree->data;
		  deepCopy(currentNodeLHS, currentNodeRHS);
	  }
	  //Recusive function to copy all nodes in tree
	  void deepCopy(BinaryNode <T> * currentNodeLHS, BinaryNode <T> * currentNodeRHS)
	  {
		  if (currentNodeRHS->pLeft)
		  {
			  currentNodeLHS->addLeft(currentNodeRHS->pLeft);
			  deepCopy(currentNodeLHS->pLeft, currentNodeRHS->pLeft);
		  }
		  if (currentNodeRHS->pRight)
		  {
			  currentNodeLHS->addRight(currentNodeRHS->pRight);
			  deepCopy(currentNodeLHS->pRight, currentNodeRHS->pRight);
		  }
	  }
	  ~BST() {}
	  bool empty();
	  void insert(T data)
	  {
		  //If this is the first time inserting into tree, make the root head this data
		  if (!this->masterTree)
		  {
			  this->masterTree = new BinaryNode <T>();
			  this->masterTree->data = data;
			  return;
		  }
		  //Else, find the appropriate spot
		  insert(data, this->masterTree);
	  }
	  //Recursive function, descending the nodes and inserting where appropriate (pLeft < data < pRight)
	  void insert(T data, BinaryNode <T> * currentNode)
	  {
		  if (data < currentNode->data)
		  {
			  if (!currentNode->pLeft)
			  {
				  currentNode->addLeft(data);
			  }
			  else
			  {
				  insert(data, currentNode->pLeft);
			  }
		  }
		  if (data > currentNode->data)
		  {
			  if (!currentNode->pRight)
			  {
				  currentNode->addRight(data);
			  }
			  {
				  insert(data, currentNode->pRight);
			  }
		  }

	  }
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
