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
	 BinaryNode(BinaryNode<T> & data) : pRight(NULL), pLeft(NULL), pParent(NULL), data(data)
	 {
	 }
     // copy constructor
	 BinaryNode(const BinaryNode<T> & rhs)
     {
     }
     // destructor : free everything that was previously used
     ~Node()
     {
     }
	 BinaryNode<T> * addLeft(BinaryNode<T> * pBNode);
	 BinaryNode<T> * addLeft(BinaryNode<T> & data);
	 BinaryNode<T> * addRight(BinaryNode<T> * pBNode);
	 BinaryNode<T> * addRight(BinaryNode<T> & data);
};

#endif
