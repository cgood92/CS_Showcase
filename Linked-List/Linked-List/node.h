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
     //default constructor
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
   //a node pointer "current" points to a new node
   Node <T> * current = new Node<T>();
   //a node pointer "pHead" points to where "current" points, currently
   //the new node
   Node <T> * pHead = current; 
   //pointer "p" points to where pointer "rhs" is at. continues while "p"
   //is true, or doesnt equal NULL. "p" now points to where "p's" current
   //pNext is pointing to
   for (Node <T> * p = rhs; p; p = p->pNext)
   {
   //"prev" points to where "current" currently points
      Node <T> * prev = current;
   //the value/data at "prev" equals the value/data at "p"
      prev->data = p->data;
   //if the pointer the "pNext" that "p" points to doesnt equal NULL...
      if (p->pNext != NULL)
      {
      //the pointer "next" points to a new node
         Node <T> * next = new Node<T>();
      //the node pointer "pNext" that "prev" is pointing to, now points to
      //the node "next" is pointing to
         prev->pNext = next;
      //the pointer "current" points currently to what "next" is pointing to
         current = next;
      }
      else
      {
         //the pointer "pNext" that "prev" is pointing to, points/equals NULL 
         prev->pNext = NULL;
      }
   }
   //return what pointer "pHead" is pointing to
   return pHead;
}

/**********************************************************************
 * freeData
 * Release all the memory contained in a given linked-list. The one 
 * parameter is a pointer to the head of the list
 ***********************************************************************/
template <class T>
void freeData(Node <T> * & rhs)
{
   //We'll need to imrpvoe this function later to actually
   //release all memory
   rhs = NULL; 
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
void insert(const T & data, Node<T> * & pPrev)
{
   // 1. allocate and initialize create a new node
   Node<T> * pNew = new Node<T>(data);   // allocate the node
   if (pPrev != NULL)
   {
      // 2. fix the pNext pointer from pNew to the spot after it in the list
      pNew->pNext = pPrev->pNext;

      // 3. finally get pNode->pNext to point to pNew instead of the old node
      pPrev->pNext = pNew;
   }
   //New linked list - empty
   else
   {
      pPrev = pNew;
   }
}
/////////////////Exact same, including a bool parameter as well////////////
template <class T>
void insert(const T & data, Node<T> * & pHead, bool head)
{
   if (head)
   {
      // 1. allocate and initialize create a new node
      Node<T> * pNew = new Node<T>(data);   // allocate the node

      if (pHead != NULL)
      {
         // 2. put pHead in line after the new node
         pNew->pNext = pHead;          // set pNext, the old head of the list

         // 3. finally, pNew is the new head
         pHead = pNew;                 // pNew is the new head.  Note that
      }
      else
      {
         pHead = pNew;
      }
   }
   else
   {
      insert(data, pHead);
   }
}

/**********************************************
 * FIND NODE
 * Looking for a node based on the index.  Note
 * that the index is 1's based.  If there are
 * six items, then the valid indicies are 1..6.
 * Return pHead if no node exists there
 **********************************************/
template <class T>
Node<T> * find(Node<T> * & pHead, const T & data)
{
   // search through the linked list
   for (Node<T> * p = pHead; p; p = p->pNext)
   {
      if (p->data == data)
      {
         return p;
      }
   }

   return NULL;        // return pHead if no node exists
}

/*****************************************
 * DISPLAY
 * Display the contents of a linked list
 ****************************************/
template <class T>
ostream & operator << (ostream & out, Node<T> * pHead)
{
   for (Node <T> * p = pHead; p; p = p->pNext)
   {
      out << p->data;
      if (p->pNext)
      {
         out << ", ";
      }
   }
   return out;
}

#endif
