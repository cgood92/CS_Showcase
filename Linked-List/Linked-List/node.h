/***********************************************************************
 * Program:
 *    Lesson 5, Node
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef NODE_H
#define NODE_H

#include <cassert>
#include <iostream>
using namespace std;

template <class T>
class Node
{
private:
public:
	Node()
	{

	}
	~Node()
	{

	}
	Node(const Node<T> & rhs)
	{

	}
	void copy();
	void insert();
	void find();
};


#endif
