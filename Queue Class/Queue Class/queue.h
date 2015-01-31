/***********************************************************************
 * Program:
 *    Lesson 3, Queue
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

/**********************************************************************
 * Stack
 * //creating the class for Stacks
 ***********************************************************************/
template <class T>
class Queue
{
  private:
     T * data;      //dynamically allocated array of T
     int frontSpot; //the "X" value of where the bottom/front item is found
     int backSpot;  //the "X" value of where the top/back item is found
     int current_size;  //the current Set size, or number of items
     int capacity_size; //how many items can I put on the Set before full?
     void resize(int newCapacity) throw (bad_alloc);
  public:
     ////////////CLASS CONSTRUCTORS///////////////////
     // default constructor :
     Queue() : data(NULL), current_size(0), capacity_size(0),
        frontSpot(-1), backSpot(-1){}
     // copy constructor : copy details of another indicated
	 Queue(const Queue<T> & rhs) : current_size(0)
     {
		 resize(rhs.capacity_size);
		 current_size = rhs.current_size;
		 capacity_size = rhs.capacity_size;
		 frontSpot = rhs.frontSpot;
		 backSpot = rhs.backSpot;
		 for (int i = 0; i <= rhs.backSpot; i++)
			 data[i] = rhs.data[i];
     }
     // non-default constructor : pre-allocate
     Queue(int capacity) : data(NULL), current_size(0),
        capacity_size(0), frontSpot(-1), backSpot(-1)
     {
        if (capacity > 0) { resize(capacity); }
     }
     // destructor : free everything that was previously used
     ~Queue()
     {
        if (NULL != data)//(capacity)
        {  //assert(capacity);
           delete[] data;
        }
     }
     
     /////////COMMANDS///////////////////
     //empty(): Test whether the set is empty
     bool empty() const { return backSpot == frontSpot; }
     //size:    Return the current_size of the Queue
     int size()        const{ return current_size; }
     //capacity:Return the capacity_size of the Queue
     int capacity()    const{ return capacity_size; }
     
     Queue<T> & operator = (const Queue<T> & rhs) throw (bad_alloc);

     //push():  Adds an item to the top/back of the container.
     void push(const T & item);
     //back():  Returns the item currently at the top/back of the stack.
     T & back()   throw(const char *);
     //front(): Returns the item currently at the bottom/front of the stack.
     T & front()  throw(const char *);
     //pop(): Removes an item from the front/bottom of the stack
     void pop()   throw(const char *);
     
};
/**********************************************************************
 * (1)//creating the steps for resizing the Queue
 ***********************************************************************/
template <class T>
void Queue<T> ::resize(int newCapacity) throw (bad_alloc)
{
   //allocate new array
   T * pNew;
   pNew = new T[newCapacity];
   //copy data from old array
   for (int i = 0; current_size > 0 && i < current_size; i++)
   {
      pNew[i] = data[i];
   }
   //delete old and assign the new
   delete[] data;
   data = pNew;
   capacity_size = newCapacity;
}

/**********************************************************************
 * (2)Stack-push
 *  -Adds an item to the top of the stack.
 ***********************************************************************/
template <class T>
void Queue<T> ::push(const T & item)
{
   //Note that if the stack is full, then the capacity will be doubled.
   if (backSpot == (capacity_size - 1))
   {
      if (capacity_size == 0)
      {
         capacity_size = 1;
      }
      resize(capacity_size * 2);
      //add 1 to current number of items/positions, then place an item
      //at that spot
      current_size++;
      data[++backSpot] = item;
   }
   else
   {
      current_size++;
      data[++backSpot] = item;
   }
}

/**********************************************************************
 * (3)Queue-front
 *  -Returns the item currently at the back/top of the stack.
 ***********************************************************************/
template <class T>
T & Queue<T> ::back()throw(const char *)
{
   if (!empty())
   {
      return data[backSpot];
   }
   else
   {
      throw "ERROR: attempting to access an item in an empty queue";
   }
}

/**********************************************************************
 * (4)Queue-front
 *  -Returns the item currently at the front/bottom of the Queue.
 ***********************************************************************/
template <class T>
T & Queue<T> ::front()throw(const char *)
{
   if (!empty())
   {
      return data[frontSpot+1];
   }
   else
   {
	   throw "ERROR: attempting to access an item in an empty queue";
   }
}

/**********************************************************************
 * (5)Stack-pop
 *  -Removes the item from the head
 ***********************************************************************/
template <class T>
void Queue<T> ::pop() throw(const char *)
{
   if (!empty())
   {
      frontSpot++;
      current_size--;
   }
   else
   {
      //if the stack is already empty, the
      //following c-string exception will be thrown:
	   throw "ERROR: attempting to pop from an empty queue";
   }
}

/**********************************************************************
 * Queue-operator equals
 * //creating the steps for equaling the Queue
 ***********************************************************************/
template <class T>
Queue<T> & Queue<T> :: operator = (const Queue<T> & rhs) throw (bad_alloc)
{
   resize(rhs.current_size);

   //copy the data from the other size
   current_size = rhs.current_size;
   for (int i = 0; i < rhs.current_size; i++)
   {
      data[i] = rhs.data[i];
   }
   //return itself
   return *this;
}
   
#endif
