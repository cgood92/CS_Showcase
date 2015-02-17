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
	Node <T> * pPrev;
	//default constructor
	Node() : data(NULL), pNext(NULL), pPrev(NULL)
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
		return pHead->pNext->data == NULL;
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
private:
	Node<T> * pHead;
	Node<T> * pTail;

	void emptyListInit()
	{
		//Head
		this->pHead = new Node<T>();
		pHead->data = NULL;
		pHead->pPrev = NULL;

		//Tail
		this->pTail = new Node<T>();
		pTail->data = NULL;
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


#endif
