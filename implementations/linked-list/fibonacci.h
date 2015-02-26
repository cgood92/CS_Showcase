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
		this->data = new List < int > ;
		this->data->copyFromPointer(rhs.data->head());
		return *this;
	}


	WholeNumber operator + (WholeNumber & rhs)
	{
		int carryOver = 0;
		WholeNumber sum;
		for (ListIterator<int> rhsIt = rhs.data->rbegin(), lhsIt = this->data->rbegin(); (*rhsIt && rhsIt != rhs.data->rend()) || (*lhsIt && lhsIt != this->data->rend()) || carryOver;)
		{
			if ((rhsIt.isBegin() && !lhsIt.isBegin()) || (!rhsIt.isBegin() && lhsIt.isBegin()))
			{
				int coeff = (*rhsIt) ? *rhsIt : *lhsIt;
				sum.data->push_front(carryOver + coeff);
				carryOver = 0;
				break;
			}

			//No more in either list, so add 1 to the front
			if (carryOver && (rhsIt.isBegin() && lhsIt.isBegin()))
			{
				sum.data->push_front(1);
				break;
			}
			int newInt = *rhsIt + *lhsIt + carryOver;
			if (newInt >= 1000)
			{
				*lhsIt = newInt - 1000;
				sum.data->push_front(newInt - 1000);
				carryOver = 1;
			}
			else
			{
				carryOver = 0;
				sum.data->push_front(newInt);
			}
			if (!lhsIt.isBegin())
			{
				--lhsIt;
			}
			if (!rhsIt.isBegin())
			{
				--rhsIt;
			}
		}
		return sum;
	}


	// input and output
	friend std::ostream & operator << (std::ostream & out, WholeNumber & rhs)
	{
		for (ListIterator<int> it = rhs.data->begin(); !it.isEnd(); ++it)
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

