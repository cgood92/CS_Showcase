/***********************************************************************
 * Program:
 *    Lesson 0s, Infix to Postfix
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef STACK_H
#define STACK_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

/**********************************************************************
 * Stack
 * //creating the class for Stacks
 ***********************************************************************/
template <class T>
class Stack
{
  private:
   T * data;          //dynamically allocated array of T
   int current_size;  //the current Set size, or number of items
   int capacity_size; //how many items can I put on the Set before full?
   int topSpot;       //the "X" value of where the top item is found
   void resize(int newCapacity) throw (bad_alloc);
  public:
   /////////CONSTRUCTORS///////////////////
   // default constructor : empty and kinda useless
  Stack() : data(NULL), current_size(0), capacity_size(0), topSpot(-1) {}
   // copy constructor : copy it
  Stack(const Stack<T> & rhs) : data(NULL), current_size(0), capacity_size(0), topSpot(-1)
   {
      if (rhs.size())   { *this = rhs; }
   }
   // non-default constructor : pre-allocate
  Stack(int capacity) : data(NULL), current_size(0), capacity_size(0), topSpot(-1)
   {
      if (capacity > 0) { resize(capacity); }
   }
   // destructor : free everything that was previously used
   ~Stack()
   {
      if (NULL != data)//(capacity)
      {  //assert(capacity);
         delete[] data;
      }
   }

   /////////COMMANDS///////////////////
   //size(): Return the Setsize
   int size()        const{ return current_size; }
   //empty(): Test whether the set is empty
   bool empty()      //const { return current_size == 0; }
      const { return topSpot == -1; }

   //push(): Adds an item to the container.
   void push(const T & item);
   //top(): Returns the item currently at the top of the stack.
   T & top() throw(const char *);
   //pop(): Removes an item from the end of the stack,
   //serving to reduce the size by one.
   void pop() throw(const char *);
   
   //convert infix format to postfix format
   //void testInfixToPostfix();
   
   Stack<T> & operator = (const Stack<T> & rhs) throw (bad_alloc);
};

//template <class T>
//void Stack<T> :: testInfixToPostfix()
//{
//}
/**********************************************************************
 * Stack-push
 *  -Adds an item to the top of the stack.
 ***********************************************************************/
template <class T>
void Stack<T> ::push(const T & item)
{
   //Note that if the stack is full, then the capacity will be doubled.
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
/**********************************************************************
 * Stack-top
 *  -Returns the item currently at the top of the stack.
 ***********************************************************************/
template <class T>
T & Stack<T> ::top()throw(const char *)
{
   //   cout << "hi";
   if (!empty())
   {
      return data[topSpot];
      cout << "hi2";
   }
   else
   {
      throw "ERROR: Unable to reference the element from an empty Stack";
   }
}
/**********************************************************************
 * Stack-top
 *  -Returns the item currently at the top of the stack.
 ***********************************************************************/
template <class T>
void Stack<T> ::pop() throw(const char *)
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
/**********************************************************************
 * //creating the steps for resizing the Stack
 ***********************************************************************/
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

/**********************************************************************
 * Stack-operator equals
 * //creating the steps for equaling the Stack
 ***********************************************************************/
template <class T>
Stack<T> & Stack<T> :: operator = (const Stack<T> & rhs) throw (bad_alloc)
{
   current_size = 0;
   if (rhs.current_size > capacity_size)
   {
      resize(rhs.current_size);
   }
   assert(capacity_size >= rhs.current_size);


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
   
