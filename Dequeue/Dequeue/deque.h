/***********************************************************************
 * Program:
 *    Lesson 3, Deque
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

/**********************************************************************
 * Stack
 * //creating the class for Stacks
 ***********************************************************************/
template <class T>
class Deque
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
     Deque() : data(NULL), current_size(0), capacity_size(0),
        frontSpot(50), backSpot(50){}
     // copy constructor : copy details of another indicated
     Deque(const Deque<T> & rhs) : current_size(0), data(NULL)
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
     Deque(int capacity) : data(NULL), current_size(0),
         capacity_size(0), frontSpot(50), backSpot(50)
     {
        if (capacity > 0) { resize(capacity); }
     }
     // destructor : free everything that was previously used
     ~Deque()
     {
        if (NULL != data)//(capacity)
        {  //assert(capacity);
           delete[] data;
        }
     }

     /////////COMMANDS///////////////////
     //empty(): Test whether the set is empty
     bool empty() const { return backSpot == frontSpot; }
     //size:    Return the current_size of the Deque
     int size()        const{ return current_size; }
     //capacity:Return the capacity_size of the Deque
     int capacity()    const{ return capacity_size; }
     //clear:   Removes all items from Deque
     void clear(){}

     Deque<T> & operator = (const Deque<T> & rhs) throw (bad_alloc);

     //push_front():  Adds an item to the top/back of the Deque.
     void push_front(const T & item);
     //push_back():  Adds an item to the back/top of the Deque
     void push_back(const T & item){}

     //front(): Returns the item currently at the bottom/front of the Deque
     T & front()  throw(const char *);
     //back():  Returns the item currently at the top/back of the Deque
     T & back()   throw(const char *);

     //pop(): Removes an item from the front/bottom of the Deque
     void pop_front()   throw(const char *);
     //pop(): Removes an item from the back/top of the Deque
     void pop_back()   throw(const char *){}
};

/**********************************************************************
 * (1)//creating the steps for resizing the Deque
 ***********************************************************************/
template <class T>
void Deque<T> ::resize(int newCapacity) throw (bad_alloc)
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

/**********************************************************************
 * (2)Deque-push_back
 *  -Adds an item to the top of the stack.
 ***********************************************************************/
template <class T>
void Deque<T> ::push_front(const T & item)
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
 * (4)Deque-front
 *  -Returns the item currently at the front/bottom of the Deque.
 ***********************************************************************/
template <class T>
T & Deque<T> ::front()throw(const char *)
{
   if (!empty())
   {
      return data[frontSpot+1];
   }
   else
   {
      throw "ERROR: attempting to access an item in an empty Deque";
   }
}

/**********************************************************************
 * (3)Deque-back
 *  -Returns the item currently at the back/top of the stack.
 ***********************************************************************/
template <class T>
T & Deque<T> ::back()throw(const char *)
{
   if (!empty())
   {
      return data[backSpot];
   }
   else
   {
      throw "ERROR: attempting to access an item in an empty Deque";
   }
}

/**********************************************************************
 * (5)Stack-pop
 *  -Removes the item from the head
 ***********************************************************************/
template <class T>
void Deque<T> ::pop_front() throw(const char *)
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
      throw "ERROR: attempting to pop from an empty Deque";
   }
}

/**********************************************************************
 * Deque-operator equals
 * //creating the steps for equaling the Deque
 ***********************************************************************/
template <class T>
Deque<T> & Deque<T> :: operator = (const Deque<T> & rhs) throw (bad_alloc)
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
