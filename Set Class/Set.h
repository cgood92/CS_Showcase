/***********************************************************************
* Program:
*    Lesson 01, Sets
*    Brother Sloan, CS 235
* Author:
*	Clint Goodman and Parker Hubbard
* Summary:
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
	int size;          //the current Set size, or number of items
	//currently within the vector
	int capacity;      // how many items can I put on the Set before full?
	void resize(int newcapacity) throw (bad_alloc);

public:
	/////////constructors///////////////////
	// default constructor : empty and kinda useless
	Set() : data(NULL), size(0), capacity(0) {}
	// copy constructor : copy it
	Set(const Set<T> & rhs) : data(NULL), size(0), capacity(0)
	{
		if (rhs.size())   { *this = rhs; }
	}
	// non-default constructor : pre-allocate
	Set(int capacity) : data(NULL), size(0), capacity(0)
	{
		if (capacity > 0) { resize(capacity); }
	}
	// destructor : free everything that was previously used
	~Set()
	{
		if (NULL != data)//(capacity)
		{  //assert(capacity);
			delete[] data;
		}
	}
	//operator=
	Set<T> & operator = (const Set<T> & rhs) throw (bad_alloc);

	//operator[]
	Set<T> & operator [] (const Set<T> & rhs) throw (bool);

	//operator()//return-by-value
	T operator () (int index) throw (bool)
	{
		return (*this)[index];
	}

	//Return the Setsize
	int size()        const{ return size; }

	//Test whether the set is empty
	bool empty()      const { return size == 0; }

	//returns the capacity size
	int capacity()    const{ return capacity; }

	// remove all the items from the container
	void clear()      { size = 0; }

	// return an iterator to the beginning of the list
	SetIterator <T> begin()   { return SetIterator<T>(data); }

	// return an iterator to the end of the list
	SetIterator <T> end()     { return SetIterator<T>(data + size); }

	//not int, but return the type of variable being used (char, int, float..)
	SetIterator<T> & find(T element);

	void insert(const T & item);
	void erase(const SetIterator <T> & tIterator);

	Set<T> operator || (const Set<T> & rhs);
	Set<T> operator && (const Set<T> & rhs);
};


/**********************************************************************
***********************************************************************/
template <class T>
void Set<T> ::insert(const T & item)
{
	SetIterator<T> iter_find = find(item);
	/* If iterator returned is the same as the end, but the item is not the last,
	this means that the item was not found, so we can insert it */
	if (*iter_find == data[size - 1] && data[size - 1] != item)
	{
		//If full, increase capacity
		if (size == capacity)
		{
			resize(capacity * 2);
		}
		//"i" is pulled out to this scope so we can use it a few lines down
		int i;
		for (i = this->size + 1; data[i] > item; i--)
		{
			data[i] = data[i + 1];
		}
		data[i] = item;
		this->size++;
	}
}


/**********************************************************************
***********************************************************************/
template <class T>
SetIterator<T> & Set<T> ::find(T element)
{
	int iBegin = 0;
	int iEnd = size - 1;
	while ((iBegin == iEnd) || (iBegin < iEnd))
	{
		int iMiddle = (iBegin + iEnd) / 2;
		if (element == data[iMiddle])
		{
			return SetIterator<T>(data, iMiddle);
		}
		if (element < data[iMiddle])
		{
			iEnd = iMiddle - 1;
		}
		else
		{
			iBegin = iMiddle + 1;
		}
	}
	return SetIterator<T>(data, size);
}



/**********************************************************************
***********************************************************************/
template <class T>
void Set<T> ::erase(const SetIterator<T> & tIterator)
{

}

/**********************************************************************
***********************************************************************/
template <class T>
Set<T> Set<T> ::operator && (const Set<T> & rhs)
{
	//TODO
	return rhs;
}

/**********************************************************************

***********************************************************************/
template <class T>
Set<T> Set<T> ::operator || (const Set<T> & rhs)
{
	//TODO
	return rhs;
}

/**********************************************************************
* Set-resize
* //creating the steps for resizing the Set
***********************************************************************/
template <class T>
void Set<T> ::resize(int newcapacity) throw (bad_alloc)
{
	//allocate new array
	T * pNew;
	pNew = new T[newcapacity];
	//copy data from old array
	for (int i = 0; i < size; i++)
	{
		pNew[i] = data[i];
	}
	//delete old and assign the new
	delete[] data;
	data = pNew;
	capacity = newcapacity;
}

/**********************************************************************
* Set-operator equals
* //creating the steps for equaling the Set
***********************************************************************/
template <class T>
Set<T> & Set<T> :: operator = (const Set<T> & rhs) throw (bad_alloc)
{
	size = 0; //remove all previously in the data
	//make sure we are big enough for the data
	if (rhs.size > capacity)
	{
		resize(rhs.size);
	}
	assert(capacity >= rhs.size);

	//copy the data from the other size
	size = rhs.size;
	for (int i = 0; i < rhs.size; i++)
	{
		data[i] = rhs.data[i];
	}
	//return itself
	return *this;
}
/**********************************************************************
* Set-operator brackets
* //creating the steps for partitioning the Set
***********************************************************************/
template <class T>
Set<T> & Set<T> :: operator [] (const Set<T> & rhs) throw (bool)
{
	if ((rhs < 0) || (rhs > size))
	{
		throw true;
	}
	return data[rhs]; //return-by-reference
}
/**********************************************************************
* SetIterator
* //creating the class of the SetIterator
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
	SetIterator(T * p, int index) : p(p)
	{
		for (int i = 0; i < index; i++)
			p++;
	}
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
	SetIterator <T> operator--(int prefix)
	{
		SetIterator tmp(*this);
		p--;
		return tmp;
	}
	// prefix increment
	SetIterator <T> & operator ++ ()
	{
		p++;
		return *this;
	}
	// postfix increment
	SetIterator <T> operator++(int postfix)
	{
		SetIterator tmp(*this);
		p++;
		return tmp;
	}
};
#endif