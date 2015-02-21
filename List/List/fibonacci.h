/***********************************************************************
 * Header:
 *    FIBONACCI
 * Summary:
 *    This will contain just the prototype for fibonacci(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Clint Goodman and Parker Hubbard
 ************************************************************************/

#include "list.h"
using namespace std;

#ifndef FIBONACCI_H
#define FIBONACCI_H

class WholeNumber
{
public:
	WholeNumber()
	{
		data = new List <int>;
	}
	~WholeNumber()
	{

	}
	WholeNumber & operator = (int initValue)
	{
		this->data = new List <int>;
		this->data->push_front(initValue);
		return *this;
	}
	WholeNumber & operator = (const WholeNumber & rhs)
	{
		data = new List <int>;
		cout << "Assigning via copy\n";
		List<int> newData(*rhs.data);
		//this->data = &newData;
		WholeNumber test;
		//test.data = new List <int> ;
		for (ListIterator<int> it = rhs.data->begin(); *it && it != rhs.data->end(); ++it)
		{
			//test.data->push_back(*it);
			cout << "\n\t-" << *it;
		}
		this->data = new List < int > ;
		this->data->copyFromPointer(rhs.data->head());
		cout << *this;
		cout << "done assigning\n";
		return *this;
	}


	WholeNumber operator + (WholeNumber & rhs)
	{
		int carryOver = 0;
		cout << "\nAdding\n";
		WholeNumber sum;
		sum = 0;
		for (ListIterator<int> rhsIt = rhs.data->rbegin(), lhsIt = this->data->rbegin(); (*rhsIt && rhsIt != rhs.data->rend()) || (*lhsIt && lhsIt != this->data->rend()) || carryOver; --rhsIt)
		{
			cout << " Stop 1" << endl;
			if (lhsIt == this->data->rend() && rhsIt != rhs.data->rend())
			{
				cout << " Stop 2" << endl;
				sum.data->push_front(*rhsIt + carryOver);
				continue;
			}
			if (carryOver && (rhsIt == rhs.data->rend() && lhsIt == this->data->rend()))
			{
				cout << " Stop 5" << endl;
				sum.data->push_front(1);
				break;
			}
			int newInt = *rhsIt + *lhsIt + carryOver;
			if (newInt >= 1000)
			{
				*lhsIt = newInt - 1000;
				sum.data->push_front(newInt - 1000);
				cout << " Stop 3 :" << *lhsIt << endl;
				carryOver = 1;
			}
			else
			{
				cout << " Stop 4 " << *lhsIt << ":" << newInt;
				carryOver = 0;
				sum.data->push_front(newInt);
				cout << ":" << *lhsIt << endl;
			}
			if (lhsIt != this->data->end())
			{
				--lhsIt;
			}
		}

		cout << "\n=================\n";
		for (ListIterator<int> it = sum.data->begin(); *it && it != sum.data->end(); ++it)
		{
			cout << *it << endl;
		}
		cout << "\n================= \n";
		
		return sum;
	}


	// input and output
	friend std::ostream & operator << (std::ostream & out, WholeNumber & rhs)
	{
		for (ListIterator<int> it = rhs.data->begin(); *it && it != rhs.data->end(); ++it)
		{
			if (it != rhs.data->begin())
			{
				out << ",";
				if (*it < 10)
				{
					out << "00";
				}
				else if (*it < 100)
				{
					out << "0";
				}
			}
			out << *it;
		}
		return out;
	}
	friend std::istream & operator >> (std::istream & in, WholeNumber & rhs);

private:
	List<int> * data;
};


// the interactive fibonacci program
void fibonacci();

#endif // FIBONACCI_H

