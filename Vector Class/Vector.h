#include <iostream>       // for CIN and COUT

template <class T>
class Vector
{
public:
	Vector() //Default constructor
	{
		Vector(0);
	}
	Vector(int capacity_size) : data(NULL), current_size(0), capacity_size(capacity_size) {} //Non-default constructor
	~Vector()  //Destructor
	{
		data = NULL;
		delete [] data;
	} 
	Vector(const Vector<T> & lhs); //Copy constructor
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
		if (capacity_size == 0)
		{
			capacity_size = 1;
		}
		//Array has not been created yet
		if (current_size == 0)
		{
			data = new T[capacity_size];
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
	T & operator [](int index) throw()
	{
		if (index < 0 || index >= capacity_size)
		{
			throw "ERROR: Invalid index";
		}
		return data[index];
	}
	void begin(); //TODO: not void
	void end(); //TODO: not void
private:
	T * data;
	int current_size;
	int capacity_size;
};