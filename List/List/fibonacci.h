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

	}
	~WholeNumber()
	{

	}
	// copy constructor
	WholeNumber(const WholeNumber & rhs)
	{
	}
	// operators
	WholeNumber & operator = (int WholeNumber)
	{
		data.push_front(WholeNumber);
		return *this;
	}
	WholeNumber & operator = (WholeNumber & rhs)
	{
		this->data = List<int>(rhs.data);
		return *this;
	}
	//WholeNumber operator - (const WholeNumber & rhs) const
	//{
	//	return WholeNumber(cents - rhs.cents);
	//}
	//WholeNumber operator * (int value) const
	//{
	//	return WholeNumber(cents * value);
	//}

	WholeNumber & operator + (WholeNumber & rhs)
	{
		int carryOver = 0;

		for (ListIterator<int> rhsIt = rhs.data.rbegin(), lhsIt = this->data.rbegin(); rhsIt != rhs.data.rend() || lhsIt != this->data.rend() || carryOver; --rhsIt)
		{
			cout << " Stop 1" << endl;
			if (lhsIt == this->data.rend() && rhsIt != rhs.data.rend())
			{
				cout << " Stop 2" << endl;
				this->data.push_front(*rhsIt + carryOver);
				continue;
			}
			if (carryOver && (rhsIt == rhs.data.rend() && lhsIt == this->data.rend()))
			{
				cout << " Stop 5" << endl;
				this->data.push_front(1);
				break;
			}
			int newInt = *rhsIt + *lhsIt + carryOver;
			if (newInt >= 1000)
			{
				*lhsIt = newInt - 1000;
				cout << " Stop 3 :" << *lhsIt << endl;
				carryOver = 1;
			}
			else
			{
				cout << " Stop 4 :" << newInt << endl;
				carryOver = 0;
				*lhsIt = newInt;
			}
			--lhsIt;
		}
		return *this;
	}
	/*bool operator == (const WholeNumber & rhs) const
	{
		return this->cents == rhs.cents;
	}
	bool operator != (const WholeNumber & rhs) const
	{
		return !(*this == rhs);
	}
	bool operator > (const WholeNumber & rhs) const
	{
		return this->cents > rhs.cents;
	}
	bool operator >= (const WholeNumber & rhs) const
	{
		return *this > rhs || *this == rhs;
	}
	bool operator < (const WholeNumber & rhs) const
	{
		return !(*this >= rhs);
	}
	bool operator <= (const WholeNumber & rhs) const
	{
		return !(*this > rhs);
	}*/

	// input and output
	friend std::ostream & operator << (std::ostream & out, WholeNumber & rhs)
	{
		for (ListIterator<int> it = rhs.data.begin(); it != rhs.data.end(); ++it)
		{
			if (it != rhs.data.begin())
			{
				out << ",";
			}
			out << *it;
		}
		return out;
	}
	friend std::istream & operator >> (std::istream & in, WholeNumber & rhs);

private:
	List<int> data;
};


// the interactive fibonacci program
void fibonacci();

#endif // FIBONACCI_H

