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
 * (BST) Binary Node
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
	~BST() {}
	BST(const BST & rhs)
	{
		this->masterTree = new BinaryNode <T>();
		BinaryNode <T> * currentNodeRHS = rhs.masterTree;
		BinaryNode <T> * currentNodeLHS = this->masterTree;
		this->masterTree->data = rhs.masterTree->data;
		deepCopy(currentNodeLHS, currentNodeRHS);
	}
	//Recursive function to copy all nodes in tree
	void deepCopy(BinaryNode <T> * currentNodeLHS,
		BinaryNode <T> * currentNodeRHS)
	{
		//if left pointer doesnt equal NULL...
		if (currentNodeRHS->pLeft)
		{
			currentNodeLHS->addLeft(currentNodeRHS->pLeft->data);
			deepCopy(currentNodeLHS->pLeft, currentNodeRHS->pLeft);
		}
		//if right pointer doesnt equal NULL...
		if (currentNodeRHS->pRight)
		{
			currentNodeLHS->addRight(currentNodeRHS->pRight->data);
			deepCopy(currentNodeLHS->pRight, currentNodeRHS->pRight);
		}
	}
	BinaryNode <T> * getRoot()
	{
		return masterTree;
	}

	//check if the tree is empty...
	bool empty()
	{
		return (masterTree->data == NULL);
	}
	//insert a node onto the tree
	void insert(T data); //throw(const char *);
	void insert(T data, BinaryNode <T> * currentNode);
	void handleBalancing(BinaryNode <T> * currentNode, bool insertAtLeft);
	//removes all items from the tree
	void clear()
	{
		void deleteBinaryTree(BinaryNode <T> * masterTree);
	}
	//returning the iterator value referring to the leftmost element in the BST
	BSTIterator <T> begin()
	{
		BSTIterator <T> myIt;
		myIt = BSTIterator <T>(this->masterTree);
		return myIt;
	}
	//the return value is an iterator referring to no element in the BST.
	//By convention, this is the NULL iterator.
	BSTIterator <T> end()
	{
		BSTIterator <T> myIt;
		myIt = BSTIterator <T>(this->masterTree);
		myIt.stackOfNodes = NULL;
		return myIt;
	}
	//returning the iterator value referring to the rightmost element in the BST
	BSTIterator <T> rbegin()
	{
		BSTIterator <T> myIt;
		myIt = BSTIterator <T>(this->masterTree);
		myIt.reverse();
		return myIt;
	}
	//the return value is an iterator referring to no element in the BST.
	//By convention, this is the NULL iterator.
	BSTIterator <T> rend()
	{
		BSTIterator <T> myIt;
		myIt = BSTIterator <T>(this->masterTree);
		myIt.stackOfNodes = NULL;
		return myIt;
	}

	/**********************************************************************
	 * Removing an item with "X" children
	 ***********************************************************************/
	void noChild(BinaryNode <T> * currentNode)
	{
		//if on the left of the parent node
		if (currentNode->data == currentNode->pParent->pLeft->data)
		{
			currentNode->pParent->pLeft = NULL;
		}
		//if on the right of the parent node
		else
		{
			currentNode->pParent->pRight = NULL;
		}
		currentNode->pParent = NULL;
		currentNode->pRight = NULL;
		currentNode->pLeft = NULL;
		delete currentNode;
	}
	void oneChild(BinaryNode <T> * currentNode)
	{
		//if current is on the left of the parent node
		if (currentNode == currentNode->pParent->pLeft)
		{
			//if child is on left of the current
			if (currentNode->pLeft)
			{
				currentNode->pLeft->pParent = currentNode->pParent;
				currentNode->pParent->pLeft = currentNode->pLeft;
			}
			//if child is on right of the current
			else
			{
				currentNode->pRight->pParent = currentNode->pParent;
				currentNode->pParent->pLeft = currentNode->pRight;
			}
		}
		//if current on the right of the parent node
		else
		{
			//if child is on left of the current
			if (currentNode->pLeft)
			{
				currentNode->pLeft->pParent = currentNode->pParent;
				currentNode->pParent->pRight = currentNode->pLeft;
			}
			//if child is on right of the current
			else
			{
				currentNode->pRight->pParent = currentNode->pParent;
				currentNode->pParent->pRight = currentNode->pRight;
			}
		}
		//remove the currentNode
		currentNode->pParent = NULL;
		currentNode->pRight = NULL;
		currentNode->pLeft = NULL;
		delete currentNode;

	}
	void twoChild(BinaryNode <T> * nodeToDelete, BinaryNode <T> * currentNode)
	{
		if (currentNode->pLeft)
		{
			twoChild(nodeToDelete, currentNode->pLeft);
		}
		else
		{
			nodeToDelete->data = currentNode->data;
			remove(currentNode);
		}
	}

	void remove(BSTIterator <T> myIt)
	{
		BinaryNode <T> * currentNode = myIt.stackOfNodes->top();
		remove(currentNode);
	}

	void remove(BinaryNode <T> * currentNode)
	{
		//1) if the nodes a leaf, having no children
		if (!currentNode->pLeft && !currentNode->pRight)
		{
			noChild(currentNode);
		}
		//2) if the node has 2 children
		else if (currentNode->pLeft && currentNode->pRight)
		{
			twoChild(currentNode, currentNode->pRight);
		}
		//3) if the node has 1 child
		else
		{
			oneChild(currentNode);
		}
	}

	/**********************************************************************
	 * Find the spot equal to "data"
	 ***********************************************************************/
	//iterator functions of this class
	BSTIterator <T> find(T data)
	{
		BSTIterator <T> it = BSTIterator <T>(this->masterTree);
		for (; it != this->end(); ++it)
			if (it.stackOfNodes->size() && (*it).first == data.first)
			{
				return it;
			}
		return this->end();
	}
};

/**********************************************************************
 * insert- first insert
 ***********************************************************************/
template <class T>
void BST<T>::insert(T data)
{
	//If this is the first time inserting into tree,
	//make the root head this data
	if (!this->masterTree)
	{
		this->masterTree = new BinaryNode <T>();
		this->masterTree->data = data;
		this->masterTree->isRed = false; //Root nodes are black
		return;
	}
	//Else, find the appropriate spot
	else
	{
		insert(data, this->masterTree);
	}
}

template <class T>
void BST<T>::handleBalancing(BinaryNode <T> * currentNode, bool insertAtLeft)
{
	//parent is red
	if (currentNode->isRed)
	{
		//grandparent is black
		if (!currentNode->pParent->isRed)
		{
			//Get aunt
			BinaryNode <T> * aunt;
			if (insertAtLeft)
			{
				aunt = currentNode->pParent->pRight;
			}
			else
			{
				aunt = currentNode->pParent->pLeft;
			}
			//Aunt is red
			if (aunt && aunt->isRed)
			{
				currentNode->isRed = false; //Parent to black
				if (currentNode->pParent != masterTree)
				{
					currentNode->pParent->isRed = true; //Grandparent to red
				}
				aunt->isRed = false; //Aunt to black
			}
			//Aunt is black
			else
			{
				//Step 4 goes here
			}
		}
	}
}

/**********************************************************************
 * insert - all other inserts
 ***********************************************************************/
template <class T>
void BST<T>::insert(T data, BinaryNode <T> * currentNode)
{
	//if "data" is less then the current spots data
	if (data < currentNode->data)
	{
		if (!currentNode->pLeft)
		{
			//add to the left
			currentNode->addLeft(data);
			handleBalancing(currentNode, true);
		}
		else
		{
			//call "insert" again with item left of current node
			insert(data, currentNode->pLeft);
		}
	}
	//if "data" is more then the current spots data
	else if (data >= currentNode->data)
	{
		if (!currentNode->pRight)
		{
			//add to the right
			currentNode->addRight(data);
			handleBalancing(currentNode, false);
		}
		else
		{
			//call "insert" again with item left of current node
			insert(data, currentNode->pRight);
		}
	}
}

/**********************************************************************
* BSTIterator
***********************************************************************/
template <class T>
class BSTIterator
{
public:
	stack < BinaryNode <T> * > * stackOfNodes;
private:
	BinaryNode <T> * masterTree;
	//Goes through the tree in RVL order, and creates a stack containing
	//all values in the tree
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
	//Non-default constructor - accept a masterTree as argument, and
	//construct a stack from the node values
	BSTIterator(BinaryNode <T> * masterTree) : masterTree(NULL),
		stackOfNodes(NULL)
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
	BSTIterator(const BSTIterator & rhs) : masterTree(NULL),
		stackOfNodes(NULL)
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
		if (this->stackOfNodes && this->stackOfNodes->size() > 0)
		{
			return this->stackOfNodes->top()->data;
		}
	}
	//Pop the stack by one
	BSTIterator <T> & operator -- ()
	{
		if (this->stackOfNodes && this->stackOfNodes->size() > 1)
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
		if (this->stackOfNodes && this->stackOfNodes->size() > 1)
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
		if (this->stackOfNodes && this->stackOfNodes->size() > 1)
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
		if (this->stackOfNodes && this->stackOfNodes->size() > 1)
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
