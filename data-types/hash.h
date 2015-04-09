/***********************************************************************
 * Program: Hash
 * Authors: Clint Goodman and Parker Hubbard
 ************************************************************************/
#ifndef HASH_H
#define HASH_H

#include <cassert>
#include <iostream>
#include <string>
#include "list.h"
using namespace std;

template <class T>
class Hash
{
public:
	Hash() : sizeInt(0), bucketSize(0)
	{
		table = new List <T> *[1];
		table[0] = NULL;
	}

	Hash(int buckets) : sizeInt(0), bucketSize(buckets)
	{
		table = new List <T> * [buckets];
		for (int i = 0; i < buckets; i++)
		{
			table[i] = NULL;
		}
	}

	~Hash()
	{

	}

	Hash(const Hash & rhs)
	{
		this->sizeInt = rhs.sizeInt;
		this->bucketSize = rhs.bucketSize;
		List<T> ** newTable = new List <T> *[bucketSize];
		for (int i = 0; i < bucketSize; i++)
		{
			if (rhs.table[i])
			{
				List<T> * newListPtr = new List < T >(*rhs.table[i]);
				*newTable[i] = *newListPtr;
			}
			else
			{
				newTable[i] = NULL;
			}
		}
		this->table = newTable;
	}

	bool empty() const
	{
		return (sizeInt == 0);
	}

	int size() const
	{
		return sizeInt;
	}

	int capacity() const
	{
		return bucketSize;
	}

	//The parameter is the value to be found. Returns true if the value is found, false otherwise.
	bool find(const T & data) const
	{
		int arrayLoc = hash(data);
		if (table[arrayLoc])
		{
			ListIterator <T> it = table[arrayLoc]->begin();
			for (; it != table[arrayLoc]->end(); ++it)
			{
				if (*it == data)
				{
					return true;
				}
			}
		}
		return false;
	}

	//Places a new instance of a value in the Hash. The parameter is the item to be inserted; there is no return value.
	void insert(T value)
	{
		int hashValue = hash(value);
		if (!table[hashValue])
		{
			table[hashValue] = new List<T>;
		}
		table[hashValue]->push_back(value);
		sizeInt++;
	}

	//This is a pure virtual function taking an element as a parameter and returning an index into the underlying array.
	virtual int hash(const T & value) const = 0;

private:
	int sizeInt;
	int bucketSize;
	List<T> ** table;
};

#endif
