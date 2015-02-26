/***********************************************************************
 * Program: Stack
 * Authors: Clint Goodman and Parker Hubbard
 ************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

template <class T>
class Stack
{
  private:
   T * data;
   int current_size;
   int capacity_size;
   int topSpot;
   void resize(int newCapacity) throw (bad_alloc);
  public:
   // default constructor
  Stack() : data(NULL), current_size(0), capacity_size(0), topSpot(-1) {}
   // copy constructor
  Stack(const Stack<T> & rhs) : data(NULL), current_size(0), capacity_size(0), topSpot(-1)
   {
      if (rhs.size())   { *this = rhs; }
   }
   // non-default constructor : pre-allocate
  Stack(int capacity) : data(NULL), current_size(0), capacity_size(0), topSpot(-1)
   {
      if (capacity > 0) { resize(capacity); }
   }
   // destructor
   ~Stack()
   {
      if (NULL != data)
      {
         delete[] data;
      }
   }

   int size() const{ return current_size; }
   bool empty() const { return topSpot == -1; }

   void push(const T & item);
   T & top() throw(const char *);
   void pop() throw(const char *)
   {
      //if the stack is already empty, the
      //following c-string exception will be thrown:
      if (!empty())
      {
         topSpot = topSpot - 1;
         current_size = current_size - 1;
      }
      else
      {
         throw "ERROR: Unable to pop from an empty Stack";
      }
   }

   Stack<T> & operator = (const Stack<T> & rhs) throw (bad_alloc);
};

template <class T>
void Stack<T> ::push(const T & item)
{
   if (topSpot <= (capacity_size - 1))
   {
      if (capacity_size == 0)
      {
         capacity_size = 1;
      }
      resize(capacity_size * 2);
      current_size++;
      topSpot = topSpot + 1;
      data[topSpot] = item;
   }
   else
   {}
}

template <class T>
T & Stack<T> ::top()throw(const char *)
{
   if (!empty())
   {
      return data[topSpot];
   }
   else
   {
      throw "ERROR: Unable to reference the element from an empty Stack";
   }
}

template <class T>
void Stack<T> ::resize(int newCapacity) throw (bad_alloc)
{
   //allocate new array
   T * pNew;
   pNew = new T[newCapacity];
   //copy data from old array
   for (int i = 0; i < current_size; i++)
   {
      pNew[i] = data[i];
   }
   //delete old and assign the new
   delete[] data;
   data = pNew;
   capacity_size = newCapacity;
}

template <class T>
Stack<T> & Stack<T> :: operator = (const Stack<T> & rhs) throw (bad_alloc)
{
   current_size = 0;
   if (rhs.current_size > capacity_size)
   {
      resize(rhs.current_size);
   }
   assert(capacity_size >= rhs.current_size);

   current_size = rhs.current_size;
   for (int i = 0; i < rhs.current_size; i++)
   {
      data[i] = rhs.data[i];
   }
   return *this;
}
#endif
   
