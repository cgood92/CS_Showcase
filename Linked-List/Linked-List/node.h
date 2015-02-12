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
     
     // destructor : free everything that was previously used
     ~Node()
     {
     }
};


/**********************************************************************
 * Copy
 * //Copy a linked-list.
 * Takes a pointer to a Node as a parameter and returns a newly created
 * linked-list containing a copy of all the nodes below the list
 * represented by the parameter
 ***********************************************************************/
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

/**********************************************************************
 * freeData
 * Release all the memory contained in a given linked-list. The one 
 * parameter is a pointer to the head of the list
 ***********************************************************************/
template <class T>
void freeData(Node <T> * rhs)
{

   //We'll need to imrpvoe this function later to actually
   //release all memory
   delete rhs;
}

/**********************************************************************
 * insert():
 * //Insert a new Node into the current linked-list. The first parameter
 * is the value to be placed in the new Node. The second parameter is the
 * Node preceding the new Node in the list. An optional third parameter is
 * set to true if the new item is to be at the head of the list. 
 ***********************************************************************/
//   Node <int> * n = NULL;
//   insert(10, n);
template <class T>
void insert(T data, Node<T> * & pPrev)
{
   if (pPrev != NULL)
   {
	   // 1. allocate and initialize create a new nod
	   Node<T> * pNew = new Node<T>;   // allocate the node
	   pNew->data = data;        // set the data member variable

	   // 2. fix the pNext pointer from pNew to the spot after it in the list
	   pNew->pNext = pPrev->pNext;

	   // 3. finally get pNode->pNext to point to pNew instead of the old node
	   pPrev->pNext = pNew;
   }
   //New linked list - empty
   else
   {
	   Node<T> * pNew = new Node<T>;
	   pNew->data = data;
	   pPrev = pNew;
   }
}

template <class T>
void insert(T data, Node<T> * & pHead, bool head)
{
	if (head)
	{
		// 1. allocate and initialize create a new node
		Node<T> * pNew = new Node<T>;               // allocate the node
		pNew->data = data;                    // set the data member variable

		// 2. put pHead in line after the new node
		pNew->pNext = pHead;                  // set pNext, the old head of the list

		// 3. finally, pNew is the new head
		pHead = pNew;                         // pNew is the new head.  Note that
	}
	else
	{
		insert(data, pHead);
	}
}

/*****************************************
 * DISPLAY
 * Display the contents of a linked list
 ****************************************/
template <class T>
ostream & operator << (ostream & out, const Node<T> * pHead)
{
   for (const Node<T> * p = pHead; p; p = p->pNext)
      out << p->data << ' ';
   return out;
}


#endif
