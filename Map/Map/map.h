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
	BST < Pair <T1, T2> > * masterTree;
	int sizeInt;
public:
	Map() : masterTree(NULL), sizeInt(0)
	{
		masterTree = new BST < Pair <T1, T2> >();
	}
	~Map()
	{

	}
	Map <T1, T2> & operator = (const Map <T1, T2> & rhs)
	{
		masterTree = new BST < Pair <T1, T2> >(*rhs.masterTree);
		sizeInt = rhs.sizeInt;
		return *this;
	}
	Pair<T1, T2> & operator [] (const T1 & key)
	{
		BSTIterator < Pair<T1, T2> > it = masterTree->find(Pair<T1, T2>(key, T2()));
		if (it != masterTree->end())
		{
			return *it;
		}
		else
		{
			masterTree->insert(Pair<T1,T2>(key, T2()));
			it = masterTree->find(Pair<T1, T2>(key, T2()));
			sizeInt++;
			return *it;
		}
	}
	bool empty()
	{
		return (sizeInt == 0);
	}
	int size()
	{
		return sizeInt;
	}
	void clear()
	{
		this->masterTree->clear();
		sizeInt = 0;
	}
	MapIterator<T1, T2> find(const T1 & key)
	{
		return MapIterator < T1, T2 >();
	}
	MapIterator<T1, T2> begin()
	{
		return MapIterator < T1, T2 >();
	}
	MapIterator<T1, T2> end()
	{
		return MapIterator < T1, T2 >();
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
	template <class TT1, class TT2>
	friend class Map;
};

#endif