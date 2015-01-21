/***********************************************************************
* Program:
*    Lesson 02, Stacks
*    Brother Sloan, CS 235
* Author:
*	Clint Goodman and Parker Hubbard
* Summary:
************************************************************************/

#ifndef STACK_H
#define STACK_H
#include <cassert>

//#include <vector>
#include <iostream>
#include <string>
using namespace std;


/**********************************************************************
* Stack
* //creating the class for stacks
***********************************************************************/
template <class T>
class Stack
{
private:
	T * data;         
	int current_size; 
	int capacity_size;
	void resize(int newCapacity) throw (bad_alloc);

public:
	Stack() : data(NULL), current_size(0), capacity_size(0) {}
	Stack(int capacity) : data(NULL), current_size(0), capacity_size(0)
	{
		if (capacity > 0) { resize(capacity); }
	}
	Stack(const Stack<T> & rhs) : data(NULL), current_size(0), capacity_size(0)
	{
		if (rhs.size())   { *this = rhs; }
	}
	~Stack()
	{
		if (NULL != data)
		{
			delete[] data;
		}
	}

	int size()        const{ return current_size; }
	bool empty()      const { return current_size == 0; }
	T & top() throw(const char *);
	//TODO
	void pop() {}
	void push(const T & item);

	Stack<T> & operator = (const Stack<T> & rhs) throw (bad_alloc);
};

/**********************************************************************
* Stack-push
* //creating the steps for inserting a unit/value to the last spot
***********************************************************************/
template <class T>
void Stack<T> ::push(const T & item)
{
	if (current_size >= capacity_size)
	{
		if (capacity_size == 0)
		{
			capacity_size = 1;
		}
		resize(capacity_size * 2);
	}
	//Add the data
	data[current_size] = item;
	current_size++;
}

/**********************************************************************
* Stack-top
***********************************************************************/
template <class T>
T & Stack<T> ::top() throw(const char *)
{
	if (current_size == 0)
	{
		throw "ERROR: Unable to reference the element from an empty Stack";
	}
	return data[current_size];
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


