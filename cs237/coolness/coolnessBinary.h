/*************************************************************************
 * Sample code (binary Predicate)
 *************************************************************************/
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

/*************************************************************************
* Binary predicate class declaration.
*
* Add to this if desired, but do NOT change the functions already in it.
*
* This is an abstract base class with pure virtual functions
* (per the =0 suffix).
*************************************************************************/
template<typename T1, typename T2>
class Predicate
{
public:
	/***********************************************************
	* Is this Predicate true for the given x and y?
	***********************************************************/
	virtual bool isTrue(T1 x, T2 y) = 0;

	/***********************************************************
	* Is this Predicate false for the given x and y?
	***********************************************************/
	virtual bool isFalse(T1 x, T2 y) = 0;

	/***********************************************************
	* Is this Predicate true for all x for all y
	* in the supplied domains?
	***********************************************************/
	bool forAllForAll(vector<T1> domain1, vector<T2> domain2)
	{
		for (int i = 0; i < domain1.size(); i++)
		{
			for (int j = 0; j < domain2.size(); j++)
			{
				if (isFalse(domain1[i], domain2[j]))
				{
					return false;
				}
			}
		}
		return true;
	}

	/***********************************************************
	* Is this Predicate true for all x for some y
	* in the supplied domains?
	***********************************************************/
	bool forAllForSome(vector<T1> domain1, vector<T2> domain2)
	{
		for (int i = 0; i < domain1.size(); i++)
		{
			bool exist = false;
			for (int j = 0; j < domain2.size(); j++)
			{
				if (isTrue(domain1[i], domain2[j]))
				{
					exist = true;
					break;
				}
			}
			if (!exist)
			{
				return false;
			}
		}
		return true;
	}

	/***********************************************************
	* Is this Predicate true for some x for all y
	* in the supplied domains?
	***********************************************************/
	bool forSomeForAll(vector<T1> domain1, vector<T2> domain2)
	{
		for (int i = 0; i < domain1.size(); i++)
		{
			bool exist = false;
			for (int j = 0; j < domain2.size(); j++)
			{
				if (isFalse(domain1[i], domain2[j]))
				{
					exist = true;
					break;
				}
			}
			if (!exist)
			{
				return true;
			}
		}
		return false;
	}

	/***********************************************************
	* Is this Predicate true for some x for some y
	* in the supplied domains?
	***********************************************************/
	bool forSomeForSome(vector<T1> domain1, vector<T2> domain2)
	{
		for (int i = 0; i < domain1.size(); i++)
		{
			for (int j = 0; j < domain2.size(); j++)
			{
				if (isTrue(domain1[i], domain2[j]))
				{
					return true;
				}
			}
		}
		return false;
	}
};

template<typename T1, typename T2>
class GreaterThan : public Predicate<T1, T2>
{
public:
	bool isTrue(T1 one, T2 two)
	{
		return (one > two);
	}
	bool isFalse(T1 one, T2 two)
	{
		return !isTrue(one, two);
	}
};


template<typename T1, typename T2>
class LessThan : public Predicate<T1, T2>
{
public:
	bool isTrue(T1 one, T2 two)
	{
		return (one < two);
	}
	bool isFalse(T1 one, T2 two)
	{
		return !isTrue(one, two);
	}
};


/***************************************************************
* Runs one test, identified by its string argument.
***************************************************************/
template<typename T1, typename T2>
bool runOne(GreaterThan<int, int> test, string testName, vector<T1> v1, vector<T2> v2)
{
	if (testName == "forAllForAll")
	{
		return test.forAllForAll(v1, v2);
	}
	else if (testName == "forAllForSome")
	{
		return test.forAllForSome(v1, v2);
	}
	else if (testName == "forSomeForAll")
	{
		return test.forSomeForAll(v1, v2);
	}
	else if (testName == "forSomeForSome")
	{
		return test.forSomeForSome(v1, v2);
	}

	//Default
	return false;
}


template<typename T1, typename T2>
void runOne(GreaterThan<T1, T2> test, string testName, vector<T1> v1, string v1Name, vector<T2> v2, string v2Name, bool expected)
{
	cout << testName.c_str() << "(" << v1Name.c_str() << ", " << v2Name.c_str() << ")\n"
		<< "     expected to return " << expected << ";\n"
		<< " actual return value is ";
	cout << runOne<T1, T2>(test, testName, v1, v2);
	cout << endl;
}

/***************************************************************
* Runs all tests.
***************************************************************/
template<typename T1, typename T2>
void runAll(GreaterThan<T1, T2> test, vector<T1> v1, vector<T2> v2)
{
	cout << "Running all tests.\n";

	runOne<int, int>(test, "forAllForAll", v1, "expenses", v2, "incomes", true);
	runOne<int, int>(test, "forAllForSome", v1, "expenses", v2, "incomes", true);
	runOne<int, int>(test, "forSomeForSome", v1, "expenses", v2, "incomes", true);
	runOne<int, int>(test, "forSomeForAll", v1, "expenses", v2, "incomes", true);

	cout << "--------------------------" << endl;

	runOne<int, int>(test, "forAllForAll", v2, "incomes", v1, "expenses", true);
	runOne<int, int>(test, "forAllForSome", v2, "incomes", v1, "expenses", true);
	runOne<int, int>(test, "forSomeForSome", v2, "incomes", v1, "expenses", true);
	runOne<int, int>(test, "forSomeForAll", v2, "incomes", v1, "expenses", true);
}



/*************************************************************************
* learned
*
* Tells interested parties what you learned.
*
* Use one or more calls to out(...), or else see the whatIlearned
* script and do the following:
*
*   Words words = {
*   #include "whatIlearned.inc"
*   nl};
*   cout << words;
*************************************************************************/
void learned()
{
	cout << "I worked with a tutor on this assignment, and we focused on learning on the 4 combinations of 'for all' and 'for some'.  First of all, the order in which the two occur "
		<< "is important.  ForAllForSome is NOT equivalent to forSomeForAll.The former will go through the entire first set, and all it must need find is at least one truth from the "
		<< "other set for each time in the first set to be considered true overall.  The latter does not care that every item in the first set has at least one truth in the alternate "
		<< "set; rather it cares that at least one of the elements in the second set is true when matched against every element in the first set.  Their logic is completely different "
		<< "in some perspectives.  Yet the code looks remarkably similar, with only the booelans being inverted.  I found that to be interesting.  Again, to sum up, the most important "
		<< "thing that I learned was that the order in which these two quantifiers occur changes the entire meaning."
		<< "\nOther things that I learned included templated functions (not just templated classes), vectors, exposure to lisp, etc. " << endl;
}

/*************************************************************************
* usage
*
* Tells the user how to use the program.
*************************************************************************/
void usage(const char * programName)
{
	cout << "This is the usage" << endl;
}

