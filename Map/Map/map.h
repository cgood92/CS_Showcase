/***********************************************************************
 * Program:
 *    Lesson 8, Map
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef MAP_H
#define MAP_H

#include <cassert>
#include <iostream>
#include <string>
#include "pair.h"
#include "bst.h"
#include "bnode.h"
using namespace std;

template <class T1, class T2>
class MapIterator;
/**********************************************************************
 * Map
 ***********************************************************************/
template <class T1, class T2>
class Map
{
private:
	BST < Pair <T1, T2> > masterTree;
public:
	Map()
	{

	}
	~Map()
	{

	}
	Map <T1, T2> & operator = (const Map <T1, T2> & rhs)
	{
		return *this;
	}
	T2 & operator [] (const T1 & key)
	{
		return *this;
	}
	bool empty()
	{
		return false;
	}
	int size()
	{
		return 0;
	}
	void clear()
	{

	}
	MapIterator<T1, T2> find(const T1 & key)
	{
		return MapIterator < T1, T2 >;
	}
	MapIterator<T1, T2> begin()
	{
		return MapIterator < T1, T2 > ;
	}
	MapIterator<T1, T2> end()
	{
		return MapIterator < T1, T2 >;
	}
};

/**********************************************************************
* MapIterator
***********************************************************************/
template <class T1, class T2>
class MapIterator
{
private:
public:
	MapIterator()
	{
	}
	MapIterator(const MapIterator & rhs)
	{
	}
	MapIterator & operator = (const MapIterator & rhs)
	{
		return *this;
	}
	bool operator != (const MapIterator & rhs) const
	{
		return false;
	}
	bool operator == (const MapIterator & rhs) const
	{
		return false;
	}
	MapIterator <T1, T2> & operator -- ()
	{
		return *this;
	}
	MapIterator <T1, T2> operator--(int prefix)
	{
		MapIterator tmp(*this);
		return tmp;
	}
	MapIterator <T1, T2> & operator ++ ()
	{
		return *this;
	}
	MapIterator <T1, T2> operator++(int postfix)
	{
		MapIterator tmp(*this);
		return tmp;
	}
	template <class T1, class T2>
	friend class Map;
};

#endif
