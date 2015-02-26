/***********************************************************************
 * Program: Linked-list
 * Authors: Clint Goodman and Parker Hubbard
 ************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

template <class T>
class List;
template <class T>
class ListIterator;

template <class T>
class Node
{
  private:
  public:   
     T data;
     Node <T> * pNext;
     Node <T> * pPrev;
     //default constructor
     Node() : pNext(NULL), pPrev(NULL)
     {
     }
     // Non-default
     Node(T headData) : data(headData), pNext(NULL), pPrev(NULL)
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
  template <class TT>
  friend class List;
  template <class TT>
  class ListIterator;
};

template <class T>
class List
{
  private:
     Node<T> * pHead;
     Node<T> * pTail;
     void emptyListInit()
     {
        //Head
        this->pHead = new Node<T>();
        pHead->pPrev = NULL;          

        //Tail
        this->pTail = new Node<T>(); 
        pTail->pNext = NULL;

        //Link them together
        pTail->pPrev = pHead;
        pHead->pNext = pTail;
     } 
  public:
     List()
     {
        emptyListInit();
     }
     // copy constructor
     List(const List<T> & rhs);
     // destructor 
     ~List()
     { 
     }
     bool empty()
     {
        return pHead->pNext->pNext == NULL;
     }
     void push_back(const T & data);
     void push_front(const T & data);
    T & front()
    {
     return pHead->pNext->data;
    }
     T & back()
     {
        return pTail->pPrev->data;
     }
	 Node<T> * head()
	 {
		 return pHead;
	 }
     void clear()
     {
        emptyListInit();
     }

	 List<T> operator = (const List & rhs)
	 {
		 List <T> newList(rhs);
		 return newList;
	 }

	 void copyFromPointer(Node <int> * pParam)
	 {
		 Node <int> * current = new Node<int>();
		 Node <int> * pHead = current;
		 Node <int> * prev = NULL;
		 for (Node <int> * p = pParam; p; p = p->pNext)
		 {
			 if (p->pPrev != NULL)
			 {
				 current->pPrev = prev;
			 }
			 else
			 {
				 current->pPrev = NULL;
			 }
			 prev = current;
			 prev->data = p->data;
			 if (p->pNext != NULL)
			 {
				 Node <int> * next = new Node<int>();
				 prev->pNext = next;
				 current = next;
			 }
			 else
			 {
				 this->pTail = p;
			 }
		 }
		 this->pHead = pHead;
	 }
   
     ListIterator <T> begin()   { return ListIterator <T>(pHead->pNext); }
     ListIterator <T> end()     { return ListIterator <T>(pTail); }
     ListIterator <T> rbegin()   { return ListIterator <T>(pTail->pPrev); }
     ListIterator <T> rend()     { return ListIterator <T>(pHead); }

     void insert(ListIterator<T> & spot, const T & data);
     
     ListIterator <T> remove(ListIterator<T> & spot)
     {
        ListIterator <T> iter = spot;
        Node <T> * remove = iter.p;
        Node <T> * before = remove->pPrev;
        Node <T> * after = remove->pNext;
        
        if (remove == pHead)
           pHead = after;
        else
           before->pNext = after;
        if (remove == pTail)
           pTail = before;
        else
           after->pPrev = before;
        iter.p = after;
        delete remove;
        return iter;
     }
};

template <class T>
List<T>::List(const List <T> & rhs)
{
   Node <T> * current = new Node<T>();
   Node <T> * pHead = current;
   for (Node <T> * p = rhs.pHead; p; p = p->pNext)
   {
      Node <T> * prev = current;
      prev->data = p->data;
      if (p->pPrev != NULL)
      {
         prev->pPrev = current;
      }
      else
      {
         prev->pPrev = NULL;
      }
      if (p->pNext != NULL)
      {
         Node <T> * next = new Node<T>();
         prev->pNext = next;
         current = next;
      }
      else
      {
         this->pTail = p;
      }
   }
   this->pHead = pHead;
}

template <class T>
void List<T>::push_back(const T & data)
{
   Node <T> * newNode = new Node<T>(data);
   newNode->pPrev = pTail->pPrev;
   newNode->pNext = pTail;
   pTail->pPrev->pNext = newNode;
   pTail->pPrev = newNode;
}

template <class T>
void List<T>::push_front(const T & data)
{
   Node <T> * newNode = new Node<T>(data);
   newNode->pNext = pHead->pNext;
   newNode->pPrev = pHead;
   pHead->pNext->pPrev = newNode;
   pHead->pNext = newNode;
}

template <class T>
void List<T>::insert(ListIterator<T> & spot, const T & data)
{
   if (spot.p == NULL)
   {
      push_back(data);
      return;
   }

   Node <T> * after = spot.p;
   Node <T> * before = after->pPrev;
   Node <T> * newnode = new Node<T>(data);
   newnode->pPrev = before;
   newnode->pNext  = after;
   after->pPrev = newnode;
   if (before == NULL)
   {
      pHead = newnode;
   }
   else
   {
      before->pNext = newnode;
   }
}

template <class T>
class ListIterator
{
  private:
     Node<T> * p;
  public:
     // default constructor - set value to "0"?
     ListIterator() : p(NULL)  {}
     // initialize to direct the private variable "t" to some item
     ListIterator(Node<T> * p) : p(p)      {}
     //copy constructor
     ListIterator(const ListIterator & rhs)
     {
        *this = rhs;
     }
     ListIterator & operator = (const ListIterator & rhs)
        {
           this->p = rhs.p;
           return *this;
        }
     bool operator != (const ListIterator & rhs) const
     {
        return rhs.p != this->p;
     }
     bool operator == (const ListIterator & rhs) const
     {
        return rhs.p == this->p;
     }
	 bool isBegin() const
	 {
		 return (p->pPrev == NULL);
	 }
	 bool isEnd() const
	 {
		 return (p->pNext == NULL);
	 }
     T & operator * ()
     {
        return p->data;
     }
     ListIterator <T> & operator -- ()
     {
        p = p->pPrev;
        return *this;
     }
     ListIterator <T> operator--(int prefix)
     {
        ListIterator tmp(*this);
        p = p->pPrev;
        return tmp;
     }
     ListIterator <T> & operator ++ ()
     {
        p = p->pNext;
        return *this;
     }
     ListIterator <T> operator++(int postfix)
     {
        ListIterator tmp(*this);
        p = p->pNext;
        return tmp;
     }
  template <class TT>
  friend class List;
};

#endif
