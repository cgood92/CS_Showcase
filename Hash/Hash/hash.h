/***********************************************************************
 * Program:
 *    Lesson 11, Hash
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef HASH_H
#define HASH_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

/**********************************************************************
 * Hash
 ***********************************************************************/
template <class T>
class Hash
{
public:
	Hash()
	{

	}

	Hash(int buckets)
	{

	}

	~Hash()
	{

	}

	Hash(const Hash & rhs)
	{

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
		return sizeInt;
	}

	//The parameter is the value to be found. Returns true if the value is found, false otherwise.
	bool find() const
	{
		return false;
	}

	//Places a new instance of a value in the Hash. The parameter is the item to be inserted; there is no return value.
	bool insert() const
	{
		sizeInt++;
		return false;
	}

	//This is a pure virtual function taking an element as a parameter and returning an index into the underlying array.
	virtual int hash(const T & value) const = 0;

private:
	int sizeInt;
};

#endif
