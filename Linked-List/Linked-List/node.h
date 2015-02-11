/***********************************************************************
 * Program:
 *    Lesson 5, Node
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef NODE_H
#define NODE_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

/**********************************************************************
 * Node
 * //creating the class for Node
 ***********************************************************************/
template <class T>
class Node
{
  private:
  public:
     T data;
     Node <T> * pNext;
	 Node() : data(NULL), pNext(NULL)
	 {
	 }
	 
	 // Non-default
	 Node(T headData) : data(headData), pNext(NULL)
	 {
	 }

     // copy constructor
     Node(const Node<T> & rhs)
     {
     }
     
     Node(Node<T> * & pHead)
     {
     }
     // destructor : free everything that was previously used
     ~Node()
     {
     }
};

template <class T>
Node <T> * copy(Node <T> * rhs)
{
	Node <T> * current = new Node<T>();
	Node <T> * pHead = current;
	for (Node <T> * p = rhs; p; p = p->pNext)
	{
		Node <T> * prev = current;
		prev->data = p->data;
		if (p->pNext != NULL)
		{
			Node <T> * next = new Node<T>();
			prev->pNext = next;
			current = next;
		}
		else
		{
			prev->pNext = NULL;
		}
	}
	return pHead;
}

template <class T>
void freeData(Node <T> * rhs)
{
	//We'll need to imrpvoe this function later to actually release all memory
	delete rhs;
}


#endif
