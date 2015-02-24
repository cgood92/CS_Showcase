/***********************************************************************
 * Program:
 *    Lesson 7, Binary Tree
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef BNODE_H
#define BNODE_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;


/**********************************************************************
 * Binary Node
 ***********************************************************************/
template <class T>
class BinaryNode
{
  private:
  public:   
	 T data;
	 BinaryNode <T> * pRight;
	 BinaryNode <T> * pLeft; 
	 BinaryNode <T> * pParent; 
     //default constructor
	 BinaryNode() : pRight(NULL), pLeft(NULL), pParent(NULL)
	 {
	 }
	 //non-default constructor
	 BinaryNode(T data) : pRight(NULL), pLeft(NULL), pParent(NULL), data(data)
	 {
	 }
     // copy constructor
	 BinaryNode(const BinaryNode<T> & rhs)
     {
     }
     // destructor : free everything that was previously used
	 ~BinaryNode()
     {
		 //pRight = NULL;
		 //pLeft = NULL;
		 //pParent = NULL;
		 //delete pRight;
		 //delete pLeft;
		 //delete pParent;
     }
	 BinaryNode <T> * addLeft(BinaryNode <T> * pBNode)
	 {
		 this->pLeft = pBNode;
		 this->pLeft->pParent = this;
		 return this;
	 }
	 BinaryNode <T> * addLeft(T  data)
	 {
		 BinaryNode<T> * newNode = new BinaryNode<T>(data);
		 newNode->pParent = this;
		 this->pLeft = newNode;
		 return this;
	 }
	 BinaryNode <T> * addRight(BinaryNode <T> * pBNode)
	 {
		 this->pRight = pBNode;
		 this->pRight->pParent = this;
		 return this;
	 }
	 BinaryNode <T> * addRight(T  data)
	 {
		 BinaryNode<T> * newNode = new BinaryNode <T>(data);
		 this->pRight = newNode;
		 newNode->pParent = this;
		 return this;
	 }
};

template <class T>
void deleteBinaryTree(BinaryNode <T> * pBNode)
{
	BinaryNode <T> * pLeft = pBNode->pLeft;
	BinaryNode <T> * pRight = pBNode->pRight;
	for (BinaryNode <T> * pCurrent = pBNode; pLeft || pRight; )
	{
		pLeft = pCurrent->pLeft;
		pRight = pCurrent->pRight;
		deleteBinaryTree(pLeft);
		deleteBinaryTree(pRight);
		pCurrent = NULL;
		pLeft = NULL;
		pRight = NULL;
		delete pCurrent;
		delete pLeft;
		delete pRight;
	}
}

/*****************************************
* DISPLAY
* Display the contents of a binary tree
****************************************/
template <class T>
ostream & operator << (ostream & out, BinaryNode<T> * pTree)
{
	displayInorder(pTree);
	return out;
}

/*****************************************
* DISPLAY
* Display the contents of a binary tree
****************************************/
template <class T>
void displayInorder (BinaryNode<T> * pTree)
{
	BinaryNode <T> * pLeft = pTree->pLeft;
	BinaryNode <T> * pRight = pTree->pRight;
	if (pLeft)
	{
		displayInorder(pLeft);
	}
	cout << pTree->data << " ";
	if (pRight)
	{
		displayInorder(pRight);
	}
}


#endif
