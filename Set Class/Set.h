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
	int current_size;          //the current Set size, or number of items
	//currently within the vector
	int capacity_size;      // how many items can I put on the Set before full?
	void resize(int newCapacity) throw (bad_alloc);

public:
	/////////constructors///////////////////
	// default constructor : empty and kinda useless
	Set() : data(NULL), current_size(0), capacity_size(0) {}
	// copy constructor : copy it
	Set(const Set<T> & rhs) : data(NULL), current_size(0), capacity_size(0)
	{
		if (rhs.size())   { *this = rhs; }
	}
	// non-default constructor : pre-allocate
	Set(int capacity) : data(NULL), current_size(0), capacity_size(0)
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

	//Return the Setsize
	int size()        const{ return current_size; }
	//Test whether the set is empty
	bool empty()      const { return current_size == 0; }
	//returns the Capacity size
	int capacity()    const{ return capacity_size; }
	// remove all the items from the container
	void clear()      { current_size = 0; }

	//operator=
	Set<T> & operator = (const Set<T> & rhs) throw (bad_alloc);
	//operator[]
	Set<T> & operator [] (const Set<T> & rhs) throw (bool);
	//operator()//return-by-value
	T operator () (int index) throw (bool)
	{
		return (*this)[index];
	}
	Set<T> operator || (Set<T> & rhs);
	Set<T> operator && (Set<T> & rhs);

	// return an iterator to the beginning of the list
	SetIterator <T> begin()   { return SetIterator<T>(data); }
	// return an iterator to the end of the list
	SetIterator <T> end()     { return SetIterator<T>(data + current_size); }
	//return the iterator if it exists in the list
	SetIterator <T> find(T element);

	//inserts a value into the set
	void insert(const T & item);
	//remove a value from the set
	//void erase(const SetIterator <T> & tIterator);
	void erase(SetIterator<T> & iteratorInput);
};

/**********************************************************************
* Set-insert
* //creating the steps for inserting a unit/value to a certain spot
***********************************************************************/
template <class T>
void Set<T> ::insert(const T & item)
{
	//If this is first insert, allocate some space, insert it, and quit
	if (current_size == 0)
	{
		resize(1);
		data[0] = item;
		current_size++;
		return;
	}

	SetIterator<T> iter_find = find(item);

	/* If iterator returned is the same as the end, but the item is not the last,
	this means that the item was not found, so we can insert it */
	if (iter_find == this->end())
	{
		//If full, increase capacity
		if (current_size == capacity_size)
		{
			resize(capacity_size * 2);
		}
		//"i" is pulled out to this scope so we can use it a few lines down
		int i;
		for (i = this->current_size - 1; i >= 0 && data[i] > item; i--)
		{
			data[i + 1] = data[i];
		}
		data[i + 1] = item;
		this->current_size++;
	}
}

/**********************************************************************
* Set-find
* //creating the steps for finding a certain value and location
***********************************************************************/
template <class T>
SetIterator<T> Set<T> ::find(T element)
{
	int iBegin = 0;
	int iEnd = current_size - 1;
	while ((iBegin == iEnd) || (iBegin < iEnd))
	{
		int iMiddle = (iBegin + iEnd) / 2;
		if (element == data[iMiddle])
		{
			return SetIterator<T>(data + iMiddle);
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
	return this->end();
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
* Set-operator equals
* //creating the steps for equaling the Set
***********************************************************************/
template <class T>
Set<T> & Set<T> :: operator = (const Set<T> & rhs) throw (bad_alloc)
{
	current_size = 0; //remove all previously in the data
	//make sure we are big enough for the data
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
/**********************************************************************
* Set-operator brackets
* //creating the steps for partitioning the Set
***********************************************************************/
template <class T>
Set<T> & Set<T> :: operator [] (const Set<T> & rhs) throw (bool)
{
	if ((rhs < 0) || (rhs > current_size))
	{
		throw true;
	}
	return data[rhs]; //return-by-reference
}

/**********************************************************************
***********************************************************************/
template <class T>
void Set<T> ::erase(SetIterator<T> & iteratorInput)
{
	/* If iterator returned is the same as the end, but the item is not the last,
	this means that the item was not found, so we can't delete it - it does
	not exist */
	int i = this->current_size - 1;
	for (; ; i--)
	{
		if (data[i] == *iteratorInput)
		{
			for (; i < current_size - 1; i++)
			{
				data[i] = data[i + 1];
			}
			this->current_size--;
			return;
		}
	}
}

/**********************************************************************
***********************************************************************/
template <class T>
Set<T> Set<T> ::operator || (Set<T> & rhs)
{
	Set<T> setUnion;
	SetIterator<T> iSet1 = this->begin();
	SetIterator<T> iSet2 = rhs.begin();
	while (*iSet1 != *this->end() || *iSet2 != *rhs.end())
	{
		if (*iSet1 == *this->end())
		{
			setUnion.insert(*iSet2++);
		}
		else if (*iSet2 == *rhs.end())
		{
			setUnion.insert(*iSet1++);
		}
		else if (*iSet1 == *iSet2)
		{
			setUnion.insert(*iSet1);
			iSet1++;
			iSet2++;
		}
		else if (*iSet1 < *iSet2)
		{
			setUnion.insert(*iSet1++);
		}
		else
		{
			setUnion.insert(*iSet2++);
		}
	}
	return setUnion;
}

/**********************************************************************

***********************************************************************/
template <class T>
Set<T> Set<T> ::operator && (Set<T> & rhs)
{
	Set<T> setIntersect;
	SetIterator<T> iSet1 = this->begin();
	SetIterator<T> iSet2 = rhs.begin();
	while (*iSet1 != *this->end() || *iSet2 != *rhs.end())
	{
		if (*iSet1 == *this->end() || *iSet2 == *rhs.end())
		{
			return setIntersect;
		}
		else if (*iSet1 == *iSet2)
		{
			setIntersect.insert(*iSet1);
			iSet1++;
			iSet2++;
		}
		else if (*iSet1 < *iSet2)
		{
			iSet1++;
		}
		else
		{
			iSet2++;
		}
	}
	return setIntersect;
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


