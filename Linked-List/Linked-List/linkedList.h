/***********************************************************************
 * Program:
 *    Lesson 5, Linked-List
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

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
};

/**********************************************************************
 ***********************************************************************/
template <class T>
class LinkedList
{
private:
    
public:
	//Default constructor
    LinkedList() : {}
    // copy constructor : copy details of another indicated
    LinkedList(const LinkedList<T> & rhs)
    {

    }
	//Destructor
    ~LinkedList()
    {
    }
};

#endif
