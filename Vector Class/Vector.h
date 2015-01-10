/***********************************************************************
* Program:
*    Lesson 00, Vector
*    Brother Sloan, CS 235
* Author:
*    Clint Goodman
* Summary:
*    This is a header file that implements a data structure acting
*	just like a vector.  
************************************************************************/

#include <iostream>       // for CIN and COUT

// declare prototype
template <class T>
class VectorIterator;


template <class T>
class Vector
{
public:
	Vector() : data(NULL), current_size(0), capacity_size(0) //Default constructor
	{
		Vector(0);
	}
	Vector(int capacity_size) : data(NULL), current_size(0), capacity_size(capacity_size) {} //Non-default constructor
	~Vector()  //Destructor
	{
		data = NULL;
		delete [] data;
	}
	Vector(const Vector<T> & rhs) //Copy constructor
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
			capacity_size *= 2;
			//TODO: make a new array; copy all the old array into this array
			T * tempData = new T[capacity_size];
			for (int i = 0; i < current_size; i++)
			{
				tempData[i] = data[i];
			}
			data = tempData;
		}
		//Add the data
		data[current_size] = item;
		current_size++;
	}
	T & operator [](int index) throw(const char *)
	{
		if (index < 0 || index >= capacity_size)
		{
			throw "ERROR: Invalid index";
		}
		return data[index];
	}
	VectorIterator <T> begin()
	{
		return VectorIterator <T>(data);
	}
	VectorIterator <T> end()
	{
		return VectorIterator <T>(data + current_size);
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
};

template <class T>
class VectorIterator
{
public:
	VectorIterator() : pVector(NULL) {}
	VectorIterator(T * pVectorInput) : pVector(pVectorInput) {}
	VectorIterator(const VectorIterator & rhs)  { *this = rhs; }
	bool operator != (const VectorIterator & rhs) const
	{
		return rhs.pVector != this->pVector;
	}

	bool operator == (const VectorIterator & rhs) const
	{
		return rhs.pVector == this->pVector;
	}
	
	VectorIterator & operator = (const VectorIterator & rhs)
	{
		this->pVector = rhs.pVector;
		return *this;
	}
	T & operator * ()
	{
		return *pVector;
	}
	VectorIterator<T> & operator ++ ()
	{
		pVector++;
		return *this;
	}
	VectorIterator<T> & operator -- ()
	{
		pVector--;
		return *this;
	}
	VectorIterator<T> & operator ++ (int postfix)
	{
		VectorIterator tmp(*this);
		pVector++;
		return tmp;
	}
private:
	T * pVector; //Pointer of generic type
};