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
class List;
template <class T>
class ListIterator;

/**********************************************************************
 * Node
 * //creating the class for Node
 ***********************************************************************/
template <class T>
class Node
{
  private:
   //friend class List;
   //friend class ListIterator;
  public:   
     T data;           //data held in that node
     Node <T> * pNext; //pointer to next node
     Node <T> * pPrev; //pointer to previous node
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
  template <class TT>
  friend class List;
  template <class TT>
  class ListIterator;
};

/**********************************************************************
 * List
 ***********************************************************************/
template <class T>
class List
{
  private:
     Node<T> * pHead; //pointer to next node
     Node<T> * pTail; //pointer to previous node
     void emptyListInit()
     {
        //Head
        //create a new Headnode where phead points
        this->pHead = new Node<T>();
        //have the heads "pPrev" point NULL 
        pHead->pPrev = NULL;          

        //Tail
        this->pTail = new Node<T>(); 
        pTail->pNext = NULL;

        //Link them together
        //have the 2 previous "NULL" spots point to each other, the head to
        //the back node, the tail to the head node
        pTail->pPrev = pHead;
        pHead->pNext = pTail;
     } 
  public:
     //typedef ListIterator<Node <T> > iterator;
     //typedef T value_Type;
     List()
     {
        emptyListInit();
     }
     // copy constructor
     List(const List<T> & rhs);
     // destructor : free everything that was previously used
     ~List()
     { 
     }
     //Test whether the list is empty
     bool empty()
     {
        return pHead->pNext->pNext == NULL;
     }
     //Adds an item to the back/front of the list
     void push_back(const T & data);
     void push_front(const T & data);
     //returns the item currently at the front/back of the list
	 T & front()
	 {
		 return pHead->pNext->data;
	 }
     T & back()
     {
        //the spot where the pTail's pPrev is pointing
        return pTail->pPrev->data;
     }
	 Node<T> * head()
	 {
		 return pHead;
	 }
     //Empties the list of all items
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
		 //a node pointer "current" points to a new node
		 Node <int> * current = new Node<int>();
		 //a node pointer "pHead" points to where "current" points, currently
		 //the new node
		 Node <int> * pHead = current;
		 //pointer "p" points to where pointer "rhs" is at. continues while "p"
		 //is true, or doesnt equal NULL. "p" now points to where "p's" current
		 //pNext is pointing to
		 for (Node <int> * p = pParam; p; p = p->pNext)
		 {
			 //1)first carry out these attaching steps for the "pPrev" of each
			 //"prev" points to where "current" currently points
			 Node <int> * prev = current;
			 //the value/data at "prev" equals the value/data at "p"
			 prev->data = p->data;
			 //if the pointer the "pPrev" that "p" points to doesnt equal NULL...
			 if (p->pPrev != NULL)
			 {
				 //the node pointer "pPrev" that "prev" is pointing to, now points to
				 //the node "current" is pointing to
				 prev->pPrev = current;
			 }
			 else
			 {
				 //the pointer "pPrev" that "prev" is pointing to, points/equals NULL
				 prev->pPrev = NULL;
			 }
			 //2)now carry out the same steps for "pNext" of each
			 //if the pointer the "pNext" that "p" points to doesnt equal NULL...
			 if (p->pNext != NULL)
			 {
				 //the pointer "next" points to a new node
				 Node <int> * next = new Node<int>();
				 //the node pointer "pNext" that "prev" is pointing to, now points to
				 //the node "next" is pointing to
				 prev->pNext = next;
				 //the pointer "current" points currently to what "next" is pointing to
				 current = next;
			 }
			 else
			 {
				 this->pTail = p;
			 }
		 }
		 this->pHead = pHead;
	 }
   
     // return an iterator to the beginning of the list
     ListIterator <T> begin()   { return ListIterator <T>(pHead->pNext); }
     // return an iterator to the end of the list
     ListIterator <T> end()     { return ListIterator <T>(pTail); }
   
     // return an iterator to the beginning of the list
     ListIterator <T> rbegin()   { return ListIterator <T>(pTail->pPrev); }
     // return an iterator to the end of the list
     ListIterator <T> rend()     { return ListIterator <T>(pHead); }

     //insert/remove from a certain spot in the body of the list     
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

/**********************************************************************
 * Copy
 * copy the nodes of another list
 ***********************************************************************/
template <class T>
List<T>::List(const List <T> & rhs)
{
   //a node pointer "current" points to a new node
   Node <T> * current = new Node<T>();
   //a node pointer "pHead" points to where "current" points, currently
   //the new node
   Node <T> * pHead = current;
   //pointer "p" points to where pointer "rhs" is at. continues while "p"
   //is true, or doesnt equal NULL. "p" now points to where "p's" current
   //pNext is pointing to
   for (Node <T> * p = rhs.pHead; p; p = p->pNext)
   {
      //1)first carry out these attaching steps for the "pPrev" of each
      //"prev" points to where "current" currently points
      Node <T> * prev = current;
      //the value/data at "prev" equals the value/data at "p"
      prev->data = p->data;
      //if the pointer the "pPrev" that "p" points to doesnt equal NULL...
      if (p->pPrev != NULL)
      {
         //the node pointer "pPrev" that "prev" is pointing to, now points to
         //the node "current" is pointing to
         prev->pPrev = current;
      }
      else
      {
         //the pointer "pPrev" that "prev" is pointing to, points/equals NULL
         prev->pPrev = NULL;
      }
	  //2)now carry out the same steps for "pNext" of each
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
         this->pTail = p;
      }
   }
   this->pHead = pHead;
}

/**********************************************************************
 * push_back
 * Adds an item to the back of the list
 ***********************************************************************/
template <class T>
void List<T>::push_back(const T & data)
{
   // 1. allocate and initialize create a new node
   Node <T> * newNode = new Node<T>(data);
   // 2. 
   newNode->pPrev = pTail->pPrev;
   // 3. 
   newNode->pNext = pTail;
   pTail->pPrev->pNext = newNode;
   pTail->pPrev = newNode;
}

/**********************************************************************
 * push_front
 * Adds an item to the front of the list
 ***********************************************************************/
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
 * insert():
 * Inserts an item in the middle of a list. There are two parameters: the data
 * item to be inserted, and a ListIterator pointing to the location in the list
 * where the new item will be inserted before. 
 ***********************************************************************/
//   insert(10, n);
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
   if (before == NULL) /* insert at beginning */
   {
      pHead = newnode;
   }
   else
   {
      before->pNext = newnode;
   }
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
  template <class TT>
  friend class List;
};

#endif
