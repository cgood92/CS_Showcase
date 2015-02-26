/***********************************************************************
 * Program:
 *    Lesson 3, Dequeue
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
        frontSpot(-1), backSpot(-1){}
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
         capacity_size(0), frontSpot(-1), backSpot(-1)
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
     bool empty() const { return current_size == 0; }
     //size:    Return the current_size of the Deque
     int size()        const{ return current_size; }
     //capacity:Return the capacity_size of the Deque
     int capacity()    const{ return capacity_size; }
     //clear:   Removes all items from Deque
	 void clear()
	 { 
		frontSpot = -1;
		backSpot = -1; 
		current_size = 0; 
	 }

     Deque<T> & operator = (const Deque<T> & rhs) throw (bad_alloc);

     //from 0 to 10 items
     //push_front():  Adds an item to the front/bottom of the Deque. //0///
     void push_front(const T & item);
     //push_back():  Adds an item to the back/top of the Deque       //10//
     void push_back(const T & item);

     //front(): Returns the item currently at the bottom/front of the Deque
     T & front()  throw(const char *);
     //back():  Returns the item currently at the top/back of the Deque
     T & back()   throw(const char *);

     //pop(): Removes an item from the front/bottom of the Deque   //0///
     void pop_front()   throw(const char *);
     //pop(): Removes an item from the back/top of the Deque       //10//
	 void pop_back()   throw(const char *);
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
   //This will copy everything starting from the back of the array (frontSpot) until the frontish of the array (backSpot)
   //Note: this works because current_size has not been changed yet
   //
   if (current_size > 0)
   {
	   // The logic in the for loops could possibly give bad results if this is the first time through.  If this is first time through loop, we want to run no matter what.
	   bool firstTime = true;
	   for (int i = frontSpot, buffer = capacity_size; (i != backSpot + 1 || firstTime); i++)
	   {
		   //Loop back towards the beginning
		   if (i == capacity_size)
		   {
			   i = -1;
			   buffer = 0; //From here on out put things at the beginning, not at the tail end
		   }
		   else
		   {
			   pNew[i + buffer] = data[i]; //Put at back
		   }
		   firstTime = false;
	   }
	   frontSpot = frontSpot + capacity_size;
   }
   //delete old and assign the new
   delete[] data;
   data = pNew;
   capacity_size = newCapacity;
}

/**********************************************************************
 * (2)Deque-push_front
 *  -Adds an item to the front/bottom of the stack. //0//
 ***********************************************************************/
template <class T>
void Deque<T> ::push_front(const T & item)
{
	//First resize, let's allocate default 1's
   if (current_size == 0 && capacity_size == 0)
   {
      //both barriers start at 0 and converted to 1
      capacity_size = 1;
      resize(1);
   }
   else if (((capacity_size - current_size) == 0) && (capacity_size != 0))
   {
	   resize(capacity_size * 2);
   }
   //At the beginning, let's loop towards the back of the array
   else if (frontSpot <= 0)
   {
	   frontSpot = capacity_size;
   }

    data[--frontSpot] = item;
	current_size++;
}

/**********************************************************************
 * (2)Deque-push_back
 *  -Adds an item to the top/back of the stack.  //10//
 ***********************************************************************/
template <class T>
void Deque<T> ::push_back(const T & item)
{ 
	//First resize, let's allocate default 1's
	if (current_size == 0 && capacity_size == 0)
	{
		resize(1);
	}
	else if (((capacity_size - current_size) == 0) && (capacity_size != 0))
	{
		resize(capacity_size * 2);
	}
	//We're now at the end, let's loop towards the front of the array
	else if (backSpot >= (capacity_size - 1)) 
	{
		backSpot = -1;
	}

	data[++backSpot] = item;
	current_size++;
}

/**********************************************************************
 * (4)Deque-front
 *  -Returns the item currently at the front/bottom of the Deque.
 ***********************************************************************/
template <class T>
T & Deque<T> ::front()throw(const char *)
{
	//tempFrontSpot is for a special case for the loop around of the array 
	int tempFrontSpot;
	if (frontSpot == -1)
	{
		tempFrontSpot = 0;
	}
	else
	{
		tempFrontSpot = frontSpot;
	}
   if (!empty())
   {
	   return data[tempFrontSpot];
   }
   else
   {
	   throw "ERROR: unable to access data from an empty deque";
   }
}

/**********************************************************************
 * (3)Deque-back
 *  -Returns the item currently at the back/top of the stack.
 ***********************************************************************/
template <class T>
T & Deque<T> ::back()throw(const char *)
{
	//tempBackSpot is for a special case for the loop around of the array 
	int tempBackSpot;
	if (frontSpot == capacity_size)
	{
		tempBackSpot = capacity_size - 1;
	}
	else
	{
		tempBackSpot = backSpot;
	}
	if (!empty())
	{
		return data[tempBackSpot];
	}
   else
   {
	   throw "ERROR: unable to access data from an empty deque";
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
		//Loop around
		if (frontSpot == capacity_size - 1)
		{
			frontSpot = 0;
		}
		else
		{
			frontSpot++;
		}
		current_size--;
	}
	else
	{
		//if the stack is already empty, the
		//following c-string exception will be thrown:
		throw "ERROR: unable to pop from the front of empty deque";
	}
}

/**********************************************************************
* (5)Stack-pop
*  -Removes the item from the tail
***********************************************************************/
template <class T>
void Deque<T> ::pop_back() throw(const char *)
{
	if (!empty())
	{
		//Loop around
		if (backSpot == 0)
		{
			backSpot = capacity_size;
		}
		else
		{
			backSpot--;
		}
		current_size--;
	}
	else
	{
		//if the stack is already empty, the
		//following c-string exception will be thrown:
		throw "ERROR: unable to pop from the back of empty deque";
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
