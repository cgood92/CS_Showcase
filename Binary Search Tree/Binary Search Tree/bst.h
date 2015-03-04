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
#include <stack>
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
	  BST() : masterTree(NULL)
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
		  else
		  {
			  insert(data, this->masterTree);
		  }
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
	  void remove()
	  {

	  }
	  void clear()
	  {

	  }
	  //BSTIterator <T> & find()
	  //{

	  //}
	  BSTIterator <T> begin()
	  {
		  BSTIterator <T> myIt;
		  myIt = BSTIterator <T>(this->masterTree);
		  return myIt;
	  }
	  BSTIterator <T> end()
	  {
		  BSTIterator <T> myIt;
		  myIt = BSTIterator <T>(this->masterTree);
		  myIt.stackOfNodes = NULL;
		  return myIt;
	  }
	  BSTIterator <T> rbegin()
	  {
		  BSTIterator <T> myIt;
		  myIt = BSTIterator <T>(this->masterTree);
		  myIt.reverse();
		  return myIt;
	  }
	  BSTIterator <T> rend()
	  {
		  BSTIterator <T> myIt;
		  myIt = BSTIterator <T>(this->masterTree);
		  myIt.stackOfNodes = NULL;
		  return myIt;
	  }
};



/**********************************************************************
* BSTIterator
***********************************************************************/
template <class T>
class BSTIterator
{
private:
	BinaryNode <T> * masterTree;
	stack < BinaryNode <T> * > * stackOfNodes;
	//Goes through the tree in RVL order, and creates a stack containing all values in the tree
	void fillStack(BinaryNode <T> * pTree)
	{
		BinaryNode <T> * pLeft = pTree->pLeft;
		BinaryNode <T> * pRight = pTree->pRight;
		if (pRight)
		{
			fillStack(pRight);
		}
		stackOfNodes->push(pTree);
		if (pLeft)
		{
			fillStack(pLeft);
		}
	}
	//This is for reverse iterators - reverse the stack
	void reverse()
	{
		stack < BinaryNode <T> * > * stackOfNodesNew = new stack < BinaryNode <T> * >();
		while (stackOfNodes->size() > 0)
		{
			stackOfNodesNew->push(stackOfNodes->top());
			stackOfNodes->pop();
		}
		stackOfNodes = stackOfNodesNew;
	}
public:
	BSTIterator() : masterTree(NULL), stackOfNodes(NULL)
	{
	}
	//Non-default constructor - accept a masterTree as argument, and construct a stack from the node values
	BSTIterator(BinaryNode <T> * masterTree) : masterTree(NULL), stackOfNodes(NULL)
	{
		if (masterTree)
		{
			this->stackOfNodes = new stack < BinaryNode <T> * >();
			this->masterTree = masterTree;
			if (masterTree)
			{
				fillStack(masterTree);
			}
		}
	}
	BSTIterator(const BSTIterator & rhs) : masterTree(NULL), stackOfNodes(NULL)
	{
		*this = rhs;
	}
	BSTIterator & operator = (const BSTIterator & rhs)
	{
		this->masterTree = rhs.masterTree;
		this->stackOfNodes = rhs.stackOfNodes;
		return *this;
	}
	//In the end, this will result in a pointerLocation vs. NULL condition
	bool operator != (const BSTIterator & rhs) const
	{
		return rhs.stackOfNodes != this->stackOfNodes;
	}
	//In the end, this will result in a pointerLocation vs. NULL condition
	bool operator == (const BSTIterator & rhs) const
	{
		return rhs.stackOfNodes == this->stackOfNodes;
	}
	//Return what is next on the stack
	T & operator * ()
	{
		return this->stackOfNodes->top()->data;
	}
	//Pop the stack by one
	BSTIterator <T> & operator -- ()
	{
		if (this->stackOfNodes->size() > 1)
		{
			this->stackOfNodes->pop();
		}
		else
		{
			this->stackOfNodes = NULL;
		}
		return *this;
	}
	//Pop the stack by one
	BSTIterator <T> operator--(int prefix)
	{
		BSTIterator tmp(*this);
		if (this->stackOfNodes->size() > 0)
		{
			this->stackOfNodes->pop();
		}
		else
		{
			this->stackOfNodes = NULL;
		}
		return tmp;
	}
	//Pop the stack by one
	BSTIterator <T> & operator ++ ()
	{
		if (this->stackOfNodes->size() > 1)
		{
			this->stackOfNodes->pop();
		}
		else
		{
			this->stackOfNodes = NULL;
		}
		return *this;
	}
	//Pop the stack by one
	BSTIterator <T> operator++(int postfix)
	{
		BSTIterator tmp(*this);
		if (this->stackOfNodes->size() > 0)
		{
			this->stackOfNodes->pop();
		}
		else
		{
			this->stackOfNodes = NULL;
		}
		return tmp;
	}
	template <class TT>
	friend class BST;
};


#endif
