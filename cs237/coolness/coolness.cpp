/*************************************************************************
 * Binary Predicates and Nested Quantifiers Implementation
 *
 * coolnessFTIAGPA =
 * coolness For The Inexperienced At Gersy Principle Application
 *************************************************************************/
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
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
   virtual bool isTrue(T1 x, T2 y)=0;

   /***********************************************************
    * Is this Predicate false for the given x and y?
    ***********************************************************/
   virtual bool isFalse(T1 x, T2 y)=0;

   /***********************************************************
    * Is this Predicate true for all x for all y
    * in the supplied domains?
    ***********************************************************/
   bool forAllForAll(vector<T1> domain1, vector<T2> domain2);

   /***********************************************************
    * Is this Predicate true for all x for some y
    * in the supplied domains?
    ***********************************************************/
   bool forAllForSome(vector<T1> domain1, vector<T2> domain2);

   /***********************************************************
    * Is this Predicate true for some x for all y
    * in the supplied domains?
    ***********************************************************/
   bool forSomeForAll(vector<T1> domain1, vector<T2> domain2);

   /***********************************************************
    * Is this Predicate true for some x for some y
    * in the supplied domains?
    ***********************************************************/
   bool forSomeForSome(vector<T1> domain1, vector<T2> domain2);
};


template<typename T1, typename T2>
bool Predicate<T1, T2>::forAllForAll(vector<T1> domain1, vector<T2> domain2)
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
};

template<typename T1, typename T2>
bool Predicate<T1, T2>::forAllForSome(vector<T1> domain1, vector<T2> domain2)
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
};

template<typename T1, typename T2>
bool Predicate<T1, T2>::forSomeForAll(vector<T1> domain1, vector<T2> domain2)
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
};

template<typename T1, typename T2>
bool Predicate<T1, T2>::forSomeForSome(vector<T1> domain1, vector<T2> domain2)
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
};


template <typename T1, typename T2>
class GreaterThan : public Predicate<int, int>
{
public:
   bool isTrue(int x, int y)
   {
      return (x > y);
   }

   bool isFalse(int x, int y)
   {
      return !isTrue(x, y);
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
 * Reports on what was learned.
 ***************************************************************/
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

void usage()
{
   cout << "Run the program with the following test keywords in any\n"
        << "combination:\n\n"
        << "TAA, FAA, TAS, FAS, TSA, FSA, TSS, FSS;\n\n"
        << "or, to run all eight:\n\ncoolness all\n\n";
}

/**************************************************************
 * runTrueForAllForAll tests the true return value for the
 * forAllForAll function, with the GreaterThan Predicate subclass.
 ***************************************************************/
void runTrueForAllForAll()
{
   GreaterThan<int, int> gt;

   vector<int> domain1;
   domain1.push_back(6);
   domain1.push_back(7);
   domain1.push_back(8);
   domain1.push_back(9);
   domain1.push_back(10);

   vector<int> domain2;
   domain2.push_back(1);
   domain2.push_back(2);
   domain2.push_back(3);
   domain2.push_back(4);
   domain2.push_back(5);

   cout << boolalpha; // so 1 displays as true, and 0 false.
   cout << "gt.forAllForAll(domain1, domain2)\n"
        << "     expected to return true;\n"
        << " actual return value is "
        << gt.forAllForAll(domain1, domain2) << ".\n\n";
}

/**************************************************************
 * runOne runs one test.
 * Contains a multi-way if statement to dispatch to different
 * tests of both true and false return values for each of
 * the four functions forAllForAll, forAllForSome, forSomeForAll
 * and forSomeForSome, given some Predicate subclasses and
 * vectors of data forming the domains of these Predicates.
 ***************************************************************/
void runOne(string test)
{
   cout << "\nRunning test " << test << endl;
   if (test == "TAA") // T for True, A for All, A for All
   {
      runTrueForAllForAll();
   }
   else if (test == "FAA")
   {
      ; // etc.
   }
}

/**************************************************************
 * runAll runs all eight tests for the true and false return
 * values from the four functions forAllForAll, forAllForSome,
 * forSomeForAll and forSomeForSome, by calling runOne eight
 * times with the obvious test keywords.
 ***************************************************************/
void runAll()
{
   cout << "Running all tests...\n";
   runOne("TAA");
   runOne("FAA");
   runOne("TAS");
   runOne("FAS");
   runOne("TSA");
   runOne("FSA");
   runOne("TSS");
   runOne("FSS");
}
