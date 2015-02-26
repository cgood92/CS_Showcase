/***********************************************************************
 * Program: Linked-list node
 * Authors: Clint Goodman and Parker Hubbard
 ************************************************************************/

#ifndef NODE_H
#define NODE_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

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
     // destructor
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
void freeData(Node <T> * & rhs)
{
   rhs = NULL; 
   delete rhs;
}

template <class T>
void insert(const T & data, Node<T> * & pPrev)
{
   Node<T> * pNew = new Node<T>(data);
   if (pPrev != NULL)
   {
      pNew->pNext = pPrev->pNext;
      pPrev->pNext = pNew;
   }
   else
   {
      pPrev = pNew;
   }
}

template <class T>
void insert(const T & data, Node<T> * & pHead, bool head)
{
   if (head)
   {
      Node<T> * pNew = new Node<T>(data);
      if (pHead != NULL)
      {
         pNew->pNext = pHead;
         pHead = pNew;
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

template <class T>
Node<T> * find(Node<T> * & pHead, const T & data)
{
   for (Node<T> * p = pHead; p; p = p->pNext)
   {
      if (p->data == data)
      {
         return p;
      }
   }

   return NULL;
}

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
