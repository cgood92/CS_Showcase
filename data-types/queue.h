/***********************************************************************
 * Program: Queue
 * Authors: Clint Goodman and Parker Hubbard
 ************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

template <class T>
class Queue
{
  private:
     T * data;
     int frontSpot;
     int backSpot;
     int current_size;
     int capacity_size;
     void resize(int newCapacity) throw (bad_alloc);
  public:
     // default constructor
     Queue() : data(NULL), current_size(0), capacity_size(0),
        frontSpot(-1), backSpot(-1){}
     // copy constructor
	 Queue(const Queue<T> & rhs) : current_size(0), data(NULL)
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
     // destructor
     ~Queue()
     {
        if (NULL != data)
        {
           delete[] data;
        }
     }
     
     bool empty() const { return backSpot == frontSpot; }
     int size()        const{ return current_size; }
     int capacity()    const{ return capacity_size; }
     
     Queue<T> & operator = (const Queue<T> & rhs) throw (bad_alloc);

     void push(const T & item);
     T & back()   throw(const char *);
     T & front()  throw(const char *);
     void pop()   throw(const char *);
     
};

template <class T>
void Queue<T> ::resize(int newCapacity) throw (bad_alloc)
{
   //allocate new array
   T * pNew;
   pNew = new T[newCapacity];
   //copy data from old array
   for (int i = 0; current_size > 0 && i <= backSpot; i++)
   {
      pNew[i] = data[i];
   }
   //delete old and assign the new
   delete[] data;
   data = pNew;
   capacity_size = newCapacity;
}

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
