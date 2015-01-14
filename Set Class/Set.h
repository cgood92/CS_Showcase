/***********************************************************************
* Program:
*    Lesson 00, set.h
*    Brother Helfrich, CS 235
* Author:
*	Clint Goodman and Paker Hubbard
* Summary:
*	
************************************************************************/
#ifndef SET_H
#define SET_H
#include <cassert>
//#include <vector>
#include <iostream>
#include <string>
using namespace std;


//early declaration of the "SetIterator" class for the "Vector" class
template <class T>
class SetIterator;
/**********************************************************************
* Set
* //creating the class for sets
***********************************************************************/
template <class T>
class Set
{
private:
	T * data;          // dynamically allocated array of T
	//I switched "size" for "numItems"
	int Size;          //the current Set size, or number of items
	//currently within the vector
	//int numItems;      // how many items are currently in the Set?
	int Capacity;      // how many items can I put on the Set before full?
	void resize(int newCapacity) throw (bad_alloc);
public:
	/////////constructors///////////////////
	// default constructor : empty and kinda useless
	Set() : data(NULL), Size(0), Capacity(0) {}
	// copy constructor : copy it
	Set(const Set<T> & rhs) : data(NULL), Size(0), Capacity(0)
	{
		if (rhs.size())
		{
			*this = rhs;
		}
	}
	// non-default constructor : pre-allocate
	//Vector(int capacity) throw (const char *)
	Set(int capacity) : data(NULL), Size(0), Capacity(0)
	{
		if (capacity > 0)
		{
			resize(capacity);
		}
	}
	// destructor : free everything that was previously used
	~Set()
	{
		if (NULL != data)//(capacity)
		{
			//assert(capacity);
			delete[] data;
		}
	}
	//operator=
	Set<T> & operator = (const Set<T> & rhs) throw (bad_alloc);
	//operator[]
	T & operator [] (int index) throw (bool)
	{
		if ((index < 0) || (index > Size))
		{
			throw true;
		}
		return data[index]; //return-by-reference
	}
	//operator()
	T operator () (int index) throw (bool)
	{
		return (*this)[index]; //return-by-value
	}
	//Return the Setsize
	int size() const
	{
		return Size;
	}
	//Test whether the set is empty
	bool empty() const
	{
		return Size == 0;
	}
	//returns the Capacity size
	int capacity() const
	{
		return Capacity;
	}
	// remove all the items from the container
	void clear()
	{
		Size = 0;
	}
	//push_back():     add and element to the end, if empty, capacity set to 1
	//                 doubles the capacity if the capacity is reached
	Set<T> & push_back(const T & t) throw (bad_alloc);
	// return an iterator to the beginning of the list
	SetIterator <T> begin()
	{
		return SetIterator<T>(data);
	}
	// return an iterator to the end of the list
	SetIterator <T> end()
	{
		return SetIterator<T>(data + Size);
	}

	SetIterator <T> find()
	{
		//TODO
	}
	Set operator && (const Set & rhs)
	{
		//TODO
	}
	Set operator || (const Set & rhs)
	{
		//TODO
	}
};

/**********************************************************************
* Set-resize
* //creating the steps for resizing the Set
***********************************************************************/
template <class T>
void Set<T> ::resize(int newCapacity) throw (bad_alloc)
{
	//assert((newCapacity > o) && newCapacity > capacity);
	//allocate new array
	T * pNew;
	pNew = new T[newCapacity];
	//copy data from old array
	for (int i = 0; i < Size; i++)
	{
		pNew[i] = data[i];
	}
	//delete old and assign the new
	delete[] data;
	data = pNew;
	Capacity = newCapacity;
}
/**********************************************************************
* Set-pushback
* //creating the steps for pushing back on the Set
***********************************************************************/
template <class T>
Set<T> & Set<T> ::push_back(const T & t) throw (bad_alloc)
{
	//assert(size <= capacity);
	//increase capacity if necessary
	if (Capacity == 0)
	{
		resize(1);
	}
	else if (Size == Capacity)
	{
		resize(Capacity * 2);
	}
	assert(Size < Capacity);
	//add to end of the list
	//add to end of the list
	data[Size++] = t;
	return *this;
}
/**********************************************************************
* Set-operator equals
* //creating the steps for equaling the Set
***********************************************************************/
template <class T>
Set<T> & Set<T> :: operator = (const Set<T> & rhs) throw (bad_alloc)
{
	Size = 0; //remove all previously in the data
	//make sure we are big enough for the data
	if (rhs.Size > Capacity)
	{
		resize(rhs.Size);
	}
	assert(Capacity >= rhs.Size);
	//copy the data from the other size
	Size = rhs.Size;
	for (int i = 0; i < rhs.Size; i++)
	{
		data[i] = rhs.data[i];
	}
	//return itself
	return *this;
}
/**********************************************************************
* SetIterator
* //creating the class of the Set =Iterator
***********************************************************************/
template <class T>
class SetIterator
{
private:
	T * p;
public:
	// default constructor - set value to "0"?
	SetIterator() : p(0x00000000)  {}
	// initialize to direct the private variable "t" to some item
	SetIterator(T * p) : p(p)      {}
	//copy constructor
	SetIterator(const SetIterator & rhs)
	{
		*this = rhs;
	}
	// assignment operator
	SetIterator & operator = (const SetIterator & rhs)
	{
		this->p = rhs.p;
		return *this;
	}
	// not equals operator
	bool operator != (const SetIterator & rhs) const
	{
		return rhs.p != this->p;
	}
	// equals operator
	bool operator == (const SetIterator & rhs) const
	{
		return rhs.p == this->p;
	}
	// dereference operator
	T & operator * ()
	{
		return *p;
	}
	// prefix decrement
	SetIterator <T> & operator -- ()
	{
		p--;
		return *this;
	}
	// postfix decrement
	SetIterator <T> operator++(int postfix)
	{
		SetIterator tmp(*this);
		p++;
		return tmp;
	}
};
#endif