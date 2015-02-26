/***********************************************************************
 * Program: Dequeue
 * Authors: Clint Goodman and Parker Hubbard
 ************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

template <class T>
class Deque
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
     Deque() : data(NULL), current_size(0), capacity_size(0),
        frontSpot(-1), backSpot(-1){}
     // copy constructor
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
     // non-default constructor
     Deque(int capacity) : data(NULL), current_size(0),
         capacity_size(0), frontSpot(-1), backSpot(-1)
     {
        if (capacity > 0) { resize(capacity); }
     }
     // destructor
     ~Deque()
     {
        if (NULL != data)
        {
           delete[] data;
        }
     }

     bool empty() const { return current_size == 0; }
     int size()        const{ return current_size; }
     int capacity()    const{ return capacity_size; }
	 void clear()
	 { 
		frontSpot = -1;
		backSpot = -1; 
		current_size = 0; 
	 }

     Deque<T> & operator = (const Deque<T> & rhs) throw (bad_alloc);

     void push_front(const T & item);
     void push_back(const T & item);

     T & front()  throw(const char *);
     T & back()   throw(const char *);

     void pop_front()   throw(const char *);
	 void pop_back()   throw(const char *);
};

template <class T>
void Deque<T> ::resize(int newCapacity) throw (bad_alloc)
{
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
   delete[] data;
   data = pNew;
   capacity_size = newCapacity;
}

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

template <class T>
T & Deque<T> ::back()throw(const char *)
{
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

template <class T>
void Deque<T> ::pop_front() throw(const char *)
{
	if (!empty())
	{
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
		throw "ERROR: unable to pop from the front of empty deque";
	}
}

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
		throw "ERROR: unable to pop from the back of empty deque";
	}
}

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
   return *this;
}

#endif
