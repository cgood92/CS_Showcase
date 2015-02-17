/***********************************************************************
 * Program:
 *    Lesson 6, List
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef LIST_H
#define LIST_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

template <class T>
class ListIterator;

/**********************************************************************
 * Node
 ***********************************************************************/
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
	// destructor : free everything that was previously used
	~Node()
	{
	}
};

template <class T>
class List
{
public:
	List()
	{
		emptyListInit();
	}
	// copy constructor
	List(const List<T> & rhs);
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
	void clear()
	{
		emptyListInit();
	}

	// return an iterator to the beginning of the list
	ListIterator <T> begin()   { return ListIterator <T>(pHead->pNext); }
	// return an iterator to the end of the list
	ListIterator <T> end()     { return ListIterator <T>(pTail); }

	// return an iterator to the beginning of the list
	ListIterator <T> rbegin()   { return ListIterator <T>(pTail->pPrev); }
	// return an iterator to the end of the list
	ListIterator <T> rend()     { return ListIterator <T>(pHead); }

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
};


/**********************************************************************
 * Copy
 ***********************************************************************/
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

/**********************************************************************
* ListIterator
* //creating the class of the ListIterator
***********************************************************************/
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
	// assignment operator
	ListIterator & operator = (const ListIterator & rhs)
	{
		this->p = rhs.p;
		return *this;
	}
	// not equals operator
	bool operator != (const ListIterator & rhs) const
	{
		return rhs.p != this->p;
	}
	// equals operator
	bool operator == (const ListIterator & rhs) const
	{
		return rhs.p == this->p;
	}
	// dereference operator
	T & operator * ()
	{
		return p->data;
	}
	// prefix decrement
	ListIterator <T> & operator -- ()
	{
		p = p->pPrev;
		return *this;
	}
	// postfix decrement
	ListIterator <T> operator--(int prefix)
	{
		ListIterator tmp(*this);
		p = p->pPrev;
		return tmp;
	}
	// prefix increment
	ListIterator <T> & operator ++ ()
	{
		p = p->pNext;
		return *this;
	}
	// postfix increment
	ListIterator <T> operator++(int postfix)
	{
		ListIterator tmp(*this);
		p = p->pNext;
		return tmp;
	}
};


#endif
