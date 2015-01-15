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
	int Size;          //the current Set size, or number of items
	//currently within the vector
	int Capacity;      // how many items can I put on the Set before full?
	void resize(int newCapacity) throw (bad_alloc);

public:
	/////////constructors///////////////////
	// default constructor : empty and kinda useless
	Set() : data(NULL), Size(0), Capacity(0) {}
	// copy constructor : copy it
	Set(const Set<T> & rhs) : data(NULL), Size(0), Capacity(0)
	{
		if (rhs.size())   { *this = rhs; }
	}
	// non-default constructor : pre-allocate
	Set(int capacity) : data(NULL), Size(0), Capacity(0)
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
	int size()        const{ return Size; }

	//Test whether the set is empty
	bool empty()      const { return Size == 0; }

	//returns the Capacity size
	int capacity()    const{ return Capacity; }

	// remove all the items from the container
	void clear()      { Size = 0; }

	// return an iterator to the beginning of the list
	SetIterator <T> begin()   { return SetIterator<T>(data); }

	// return an iterator to the end of the list
	SetIterator <T> end()     { return SetIterator<T>(data + Size); }

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
	if (*iter_find == data[Size - 1] && data[Size - 1] != item)
	{
		//If full, increase capacity
		if (Size == Capacity)
		{
			resize(Capacity * 2);
		}
		//"i" is pulled out to this scope so we can use it a few lines down
		int i;
		for (i = this->Size + 1; data[i] > item; i--)
		{
			data[i] = data[i + 1];
		}
		data[i] = item;
		this->Size++;
	}
}


/**********************************************************************
***********************************************************************/
template <class T>
SetIterator<T> & Set<T> ::find(T element)
{
	int iBegin = 0;
	int iEnd = Size - 1;
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
	return SetIterator<T>(data, Size);
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
void Set<T> ::resize(int newCapacity) throw (bad_alloc)
{
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
* Set-operator brackets
* //creating the steps for partitioning the Set
***********************************************************************/
template <class T>
Set<T> & Set<T> :: operator [] (const Set<T> & rhs) throw (bool)
{
	if ((rhs < 0) || (rhs > Size))
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