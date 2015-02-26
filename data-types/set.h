/***********************************************************************
 * Program: Set
 * Authors: Clint Goodman and Parker Hubbard
 ************************************************************************/


#ifndef SET_H
#define SET_H
#include <cassert>

#include <iostream>
#include <string>
using namespace std;

template <class T>
class SetIterator;

template <class T>
class Set
{
private:
	T * data;
	int current_size;
	int capacity_size;
	void resize(int newCapacity) throw (bad_alloc);

public:
	// default constructor
	Set() : data(NULL), current_size(0), capacity_size(0) {}
	// copy constructor
	Set(const Set<T> & rhs) : data(NULL), current_size(0), capacity_size(0)
	{
		if (rhs.size())   { *this = rhs; }
	}
	// non-default constructor : pre-allocate
	Set(int capacity) : data(NULL), current_size(0), capacity_size(0)
	{
		if (capacity > 0) { resize(capacity); }
	}
	// destructor
	~Set()
	{
		if (NULL != data)
		{
			delete[] data;
		}
	}

	int size()        const{ return current_size; }
	bool empty()      const { return current_size == 0; }
	int capacity()    const{ return capacity_size; }
	void clear()      { current_size = 0; }

	Set<T> & operator = (const Set<T> & rhs) throw (bad_alloc);
	Set<T> & operator [] (const Set<T> & rhs) throw (bool);
	T operator () (int index) throw (bool)
	{
		return (*this)[index];
	}
	Set<T> operator || (Set<T> & rhs);
	Set<T> operator && (Set<T> & rhs);

	SetIterator <T> begin()   { return SetIterator<T>(data); }
	SetIterator <T> end()     { return SetIterator<T>(data + current_size); }
	SetIterator <T> find(T element);

	void insert(const T & item);
	void erase(SetIterator<T> & iteratorInput);
};

template <class T>
void Set<T> ::insert(const T & item)
{
	if (current_size == 0)
	{
		resize(1);
		data[0] = item;
		current_size++;
		return;
	}

	SetIterator<T> iter_find = find(item);

	/* if iterator returned is the same as the end, but the item is not the last,
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
	return *this;
}

template <class T>
Set<T> & Set<T> :: operator [] (const Set<T> & rhs) throw (bool)
{
	if ((rhs < 0) || (rhs > current_size))
	{
		throw true;
	}
	return data[rhs];
}

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

template <class T>
class SetIterator
{
private:
	T * p;
public:
	SetIterator() : p(0x00000000)  {}
	SetIterator(T * p) : p(p)      {}
	SetIterator(const SetIterator & rhs)
	{
		*this = rhs;
	}
	SetIterator & operator = (const SetIterator & rhs)
	{
		this->p = rhs.p;
		return *this;
	}
	bool operator != (const SetIterator & rhs) const
	{
		return rhs.p != this->p;
	}
	bool operator == (const SetIterator & rhs) const
	{
		return rhs.p == this->p;
	}
	T & operator * ()
	{
		return *p;
	}
	SetIterator <T> & operator -- ()
	{
		p--;
		return *this;
	}
	SetIterator <T> operator--(int prefix)
	{
		SetIterator tmp(*this);
		p--;
		return tmp;
	}
	SetIterator <T> & operator ++ ()
	{
		p++;
		return *this;
	}
	SetIterator <T> operator++(int postfix)
	{
		SetIterator tmp(*this);
		p++;
		return tmp;
	}
};
#endif


