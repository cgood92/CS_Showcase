/***********************************************************************
* Program:
*    Lesson 01, Set
*    Brother Sloan, CS 235
* Author:
*    Clint Goodman and Parker Hubbard
* Summary:
*    This is a header file that implements a data structure acting
*	just like a Set.
************************************************************************/

#include <iostream>       // for CIN and COUT

// declare prototype
template <class T>
class SetIterator;


template <class T>
class Set
{
public:
	//Default constructor
	Set() : data(NULL), current_size(0), capacity_size(0)
	{
		Set(0);
	}
	//Non-default constructor
	Set(int capacity_size) : data(NULL), current_size(0), capacity_size(capacity_size) {}
	~Set()  //Destructor
	{
		data = NULL;
		delete[] data;
	}
	//Copy constructor
	Set(const Set<T> & rhs)
	{
		capacity_size = rhs.capacity_size;
		current_size = rhs.current_size;
		data = new T[capacity_size];
		for (int i = 0; i < rhs.current_size; i++)
		{
			this->data[i] = rhs.data[i];
		}
	}
	bool empty()
	{
		return (current_size == 0);
	}
	int size()
	{
		return current_size;
	}
	int capacity()
	{
		return capacity_size;
	}
	void clear()
	{
		data = NULL;
		current_size = 0;
	}
	void push_back(T item)
	{
		//Capacity has to be more than one
		if (data == NULL)
		{
			initFromZero();
		}
		//If the capactiy is full, double the capactiy
		if (current_size >= capacity_size)
		{
			extendSize();
		}
		//Add the data
		data[current_size] = item;
		current_size++;
	}
	T & operator [](int index) throw(const char *)
	{
		//Check the range of the index
		if (index < 0 || index >= current_size)
		{
			throw "ERROR: Invalid index";
		}
		return data[index];
	}
	Set operator = (const Set & rhs)
	{
		this->pSet = rhs.pSet;
		return *this;
	}
	SetIterator <T> begin()
	{
		return SetIterator <T>(data);
	}
	SetIterator <T> end()
	{
		return SetIterator <T>(data + current_size);
	}
	SetIterator <T> find()
	{
		//TODO
	}
	Set operator && (const Set & rhs)
	{
		//TODO
	}
	Set operator || (const Set & rhs)
	{
		//TODO
	}
private:
	T * data;
	int current_size;
	int capacity_size;
	void initFromZero()
	{
		if (capacity_size == 0)
		{
			capacity_size = 1;
		}
		data = new T[capacity_size];
	}
	void extendSize()
	{
		capacity_size *= 2;
		*this = Set(*this);
	}
};

template <class T>
class SetIterator
{
public:
	SetIterator() : pSet(NULL) {}
	SetIterator(T * pSetInput) : pSet(pSetInput) {}
	SetIterator(const SetIterator & rhs)  { *this = rhs; }
	bool operator != (const SetIterator & rhs) const
	{
		return rhs.pSet != this->pSet;
	}

	bool operator == (const SetIterator & rhs) const
	{
		return rhs.pSet == this->pSet;
	}

	SetIterator & operator = (const SetIterator & rhs)
	{
		this->pSet = rhs.pSet;
		return *this;
	}
	T & operator * ()
	{
		return *pSet;
	}
	SetIterator<T> & operator ++ ()
	{
		pSet++;
		return *this;
	}
	SetIterator<T> & operator -- ()
	{
		pSet--;
		return *this;
	}
	SetIterator<T> & operator ++ (int postfix)
	{
		SetIterator tmp(*this);
		pSet++;
		return tmp;
	}
private:
	//Pointer of generic type
	T * pSet;
};