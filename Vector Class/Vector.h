#include <iostream>       // for CIN and COUT

template <class T>
class Vector
{
public:
	Vector() : data(NULL), current_size(0), capacity_size(0) {} //Constructor
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
		if (current_size == 0)
		{
			data = new T[capacity_size];
		}
		if (current_size >= capacity_size)
		{
			capacity_size *= 2;
			//TODO: make a new array; copy all the old array into this array
		}
		data[current_size] = item;
		current_size++;
	}
	T & operator [](int index)
	{
		if (index < 0 || index >= capacity_size)
		{
			cout << "Excpetion thrown";
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