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

private:
	List<int> data;
};

// the interactive fibonacci program
void fibonacci();

#endif // FIBONACCI_H

