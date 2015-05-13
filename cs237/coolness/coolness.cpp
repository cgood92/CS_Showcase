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

template<typename T1, typename T2>
class FactorOf : public Predicate<T1, T2>
{
public:
	bool isTrue(T1 one, T2 two)
	{
		return (one % two == 0);
	}
	bool isFalse(T1 one, T2 two)
	{
		return !isTrue(one, two);
	}
};


/*
	Simliar interests key
	1 = Hiking
	2 = Reading
	3 = Basketball
	4 = Biking
	5 = Movies
	6 = Tennis
	7 = Piano
	8 = Cooking
	9 = Horses
	10 = Travelling

	Girl1 likes
		Hiking (1)
		Reading (2)
		Piano (7)
		Cooking (8)
		Horses (9)

	Guy1 likes
		Basketball (3)
		Biking (4)
		Cooking (8)
		Travelling (0)

	Girl2 likes
		Biking (4)
		Reading (2)
		Movies (5)
		Piano (7)
		Horses (9)

	Guy2 likes
		Movies (5)
		Horses (9)
		Biking (4)
		Reading (2)
		Piano (7)

*/

template<typename T1, typename T2>
class HasSimilarInterests : public Predicate<T1, T2>
{
public:
	bool isTrue(T1 one, T2 two)
	{
		return (one == two);
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
	cout << "\tI worked with a tutor on this assignment, and we focused on learning on the 4 combinations"
		<< "\n\tof 'for all' and 'for some'.  First of all, the order in which the two occur is important."
		<< "\n\tForAllForSome is NOT equivalent to forSomeForAll.The former will go through the entire first"
		<< "\n\tset, and all it must need find is at least one truth from the other set for each time in the"
		<< "\n\tfirst set to be considered true overall.  The latter does not care that every item in the first"
		<< "\n\tset has at least one truth in the alternate set; rather it cares that at least one of the elements"
		<< "\n\tin the second set is true when matched against every element in the first set.  Their logic is"
		<< "\n\tcompletely different in some perspectives.  Yet the code looks remarkably similar, with only the"
		<< "\n\tbooelans being inverted.  I found that to be interesting.  Again, to sum up, the most important"
		<< "\n\tthing that I learned was that the order in which these two quantifiers occur changes the entire meaning."
		<< "\n\n\tOther things that I learned included templated functions (not just templated classes), vectors,"
		<< "\n\texposure to lisp, etc.\n\n" << endl;
}

void usage(const char * programName)
{
   cout << "Run the program with the following test keywords in any\n"
        << "combination:\n\n"
        << "TAA, FAA, TAS, FAS, TSA, FSA, TSS, FSS;\n\n"
        << "or, to run all eight:\n\ncoolness all\n\n";
}

/**************************************************************
* runForAllForAll tests the return value for the
* forAllForAll function, with the GreaterThan, LessThan, and 
* FactorOf, and special Predicate subclasses.
***************************************************************/
void runForAllForAll(string test, vector<int> d1, vector<int> d2, bool booleanExpected)
{
	cout << boolalpha;
	cout << test << ".forAllForAll(d1, d2)\n"
		<< "     expected to return " << booleanExpected << "; \n"
		<< " actual return value is ";

	//run the predicate test specified
	//Greater than
	if (test == "gt")
	{
		GreaterThan<int, int> gt;
		cout << gt.forAllForAll(d1, d2) << ".";
	}
	//Less than
	else if (test == "lt")
	{
		LessThan<int, int> lt;
		cout << lt.forAllForAll(d1, d2) << ".";
	}
	//Factor of
	else if (test == "fo")
	{
		FactorOf<int, int> fo;
		cout << fo.forAllForAll(d1, d2) << ".";
	}
	//Special
	else if (test == "sp")
	{
		HasSimilarInterests<int, int> interest;
		cout << interest.forAllForAll(d1, d2) << ".";

		//Special comments (for fun)
		if (interest.forAllForAll(d1, d2))
		{
			cout << "\nPerfect match!\n";
		}
	}
	else
	{
		cout << "Bad test\n";
	}
	cout << "\n\n";
}	

/**************************************************************
* runForAllForSome tests the return value for the
* forAllForSome function, with the GreaterThan, LessThan, and
* FactorOf, and special Predicate subclasses.
***************************************************************/
void runForAllForSome(string test, vector<int> d1, vector<int> d2, bool booleanExpected)
{
	cout << boolalpha;
	cout << test << ".forAllForSome(d1, d2)\n"
		<< "     expected to return " << booleanExpected << "; \n"
		<< " actual return value is ";

	//run the predicate test specified
	//Greater than
	if (test == "gt")
	{
		GreaterThan<int, int> gt;
		cout << gt.forAllForSome(d1, d2) << ".";
	}
	//Less than
	else if (test == "lt")
	{
		LessThan<int, int> lt;
		cout << lt.forAllForSome(d1, d2) << ".";
	}
	//Factor of
	else if (test == "fo")
	{
		FactorOf<int, int> fo;
		cout << fo.forAllForSome(d1, d2) << ".";
	}
	//Special
	else if (test == "sp")
	{
		HasSimilarInterests<int, int> interest;
		cout << interest.forAllForSome(d1, d2) << ".";

		//Special comments (for fun)
		if (interest.forAllForSome(d1, d2))
		{
			cout << "\nPerfect match!\n";
		}
	}
	else
	{
		cout << "Bad test\n";
	}
	cout << "\n\n";
}

/**************************************************************
* runForSomeForAll tests the return value for the
* forSomeForAll function, with the GreaterThan, LessThan, and
* FactorOf, and special Predicate subclasses.
***************************************************************/
void runForSomeForAll(string test, vector<int> d1, vector<int> d2, bool booleanExpected)
{
	cout << boolalpha;
	cout << test << ".forSomeForAll(d1, d2)\n"
		<< "     expected to return " << booleanExpected << "; \n"
		<< " actual return value is ";

	//run the predicate test specified
	//Greater than
	if (test == "gt")
	{
		GreaterThan<int, int> gt;
		cout << gt.forSomeForAll(d1, d2) << ".";
	}
	//Less than
	else if (test == "lt")
	{
		LessThan<int, int> lt;
		cout << lt.forSomeForAll(d1, d2) << ".";
	}
	//Factor of
	else if (test == "fo")
	{
		FactorOf<int, int> fo;
		cout << fo.forSomeForAll(d1, d2) << ".";
	}
	//Special
	else if (test == "sp")
	{
		HasSimilarInterests<int, int> interest;
		cout << interest.forSomeForAll(d1, d2) << ".";

		//Special comments (for fun)
		if (interest.forSomeForAll(d1, d2))
		{
			cout << "\nPerfect match!\n";
		}
	}
	else
	{
		cout << "Bad test\n";
	}
	cout << "\n\n";
}

/**************************************************************
* runForSomeForSome tests the return value for the
* forSomeForSome function, with the GreaterThan, LessThan, and
* FactorOf, and special Predicate subclasses.
***************************************************************/
void runForSomeForSome(string test, vector<int> d1, vector<int> d2, bool booleanExpected)
{
	cout << boolalpha;
	cout << test << ".forSomeForSome(d1, d2)\n"
		<< "     expected to return " << booleanExpected << "; \n"
		<< " actual return value is ";

	//run the predicate test specified
	//Greater than
	if (test == "gt")
	{
		GreaterThan<int, int> gt;
		cout << gt.forSomeForSome(d1, d2) << ".";
	}
	//Less than
	else if (test == "lt")
	{
		LessThan<int, int> lt;
		cout << lt.forSomeForSome(d1, d2) << ".";
	}
	//Factor of
	else if (test == "fo")
	{
		FactorOf<int, int> fo;
		cout << fo.forSomeForSome(d1, d2) << ".";
	}
	//Special
	else if (test == "sp")
	{
		HasSimilarInterests<int, int> interest;
		cout << interest.forSomeForSome(d1, d2) << ".";

		//Special comments (for fun)
		if (interest.forSomeForSome(d1, d2))
		{
			cout << "\n\nPerfect match!\n";
		}
	}
	else
	{
		cout << "Bad test\n";
	}
	cout << "\n\n";
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
	//Set that is bigger
	vector<int> bigNums;
	bigNums.push_back(6);
	bigNums.push_back(7);
	bigNums.push_back(8);
	bigNums.push_back(9);
	bigNums.push_back(10);

	//Set that is smaller
	vector<int> smallNums;
	smallNums.push_back(1);
	smallNums.push_back(2);
	smallNums.push_back(3);
	smallNums.push_back(4);
	smallNums.push_back(5);

	//Set that are factorABLE
	vector<int> factorables;
	factorables.push_back(30);
	factorables.push_back(60);
	factorables.push_back(120);
	factorables.push_back(180);
	factorables.push_back(240);

	//Set that are factors
	vector<int> factors;
	factors.push_back(2);
	factors.push_back(3);
	factors.push_back(5);
	factors.push_back(6);
	factors.push_back(10);

	//Simliar, but not exact - 1
	vector<int> girl1;
	girl1.push_back(1); //Hiking
	girl1.push_back(2); //Reading
	girl1.push_back(7); //Piano
	girl1.push_back(8); //Cooking
	girl1.push_back(9); //Horses

	//Simliar, but not exact - 1
	vector<int> guy1;
	guy1.push_back(3); //Basketball
	guy1.push_back(4); //Biking
	guy1.push_back(8); //Cooking
	guy1.push_back(10); //Travelling

	//Perfect Match - 2
	vector<int> girl2;
	girl2.push_back(4); //Biking
	girl2.push_back(2); //Reading
	girl2.push_back(5); //Movies
	girl2.push_back(7); //Piano
	girl2.push_back(9); //Horses

	//Perfect Match - 2
	vector<int> guy2;
	guy2.push_back(5); //Movies
	guy2.push_back(9); //Horses
	guy2.push_back(4); //Biking
	guy2.push_back(2); //Reading
	guy2.push_back(7); //Piano

   cout << "\nRunning test " << test << "\n\n";
   if (test == "TAA")
   {
	   runForAllForAll("gt", bigNums, smallNums, true);
	   runForAllForAll("lt", smallNums, bigNums, true);
	   runForAllForAll("fo", factorables, factors, true);
	   runForAllForAll("sp", girl2, guy2, true);
   }
   else if (test == "FAA")
   {
	   runForAllForAll("gt", smallNums, bigNums, false);
	   runForAllForAll("lt", bigNums, smallNums, false);
	   runForAllForAll("fo", factors, factorables, false);
	   runForAllForAll("sp", guy1, girl1, false);
   }
   else if (test == "TAS")
   {
	   runForAllForSome("gt", bigNums, smallNums, true);
	   runForAllForSome("lt", smallNums, bigNums, true);
	   runForAllForSome("fo", factorables, factors, true);
	   runForAllForSome("sp", girl2, guy2, true);
   }
   else if (test == "FAS")
   {
	   runForAllForSome("gt", smallNums, bigNums, false);
	   runForAllForSome("lt", bigNums, smallNums, false);
	   runForAllForSome("fo", factors, factorables, false);
	   runForAllForSome("sp", guy1, girl1, false);
   }
   else if (test == "TSA")
   {
	   runForSomeForAll("gt", bigNums, smallNums, true);
	   runForSomeForAll("lt", smallNums, bigNums, true);
	   runForSomeForAll("fo", factorables, factors, true);
	   runForSomeForAll("sp", girl2, guy2, true);
   }
   else if (test == "FSA")
   {
	   runForSomeForAll("gt", smallNums, bigNums, false);
	   runForSomeForAll("lt", bigNums, smallNums, false);
	   runForSomeForAll("fo", factors, factorables, false);
	   runForSomeForAll("sp", guy1, girl1, false);
   }
   else if (test == "TSS")
   {
	   runForSomeForSome("gt", bigNums, smallNums, true);
	   runForSomeForSome("lt", smallNums, bigNums, true);
	   runForSomeForSome("fo", factorables, factors, true);
	   runForSomeForSome("sp", girl2, guy2, true);
   }
   else if (test == "FSS")
   {
	   runForSomeForSome("gt", smallNums, bigNums, false);
	   runForSomeForSome("lt", bigNums, smallNums, false);
	   runForSomeForSome("fo", factors, factorables, false);
	   runForSomeForSome("sp", guy1, girl1, false);
   }
   else
   {
	   cout << "Bad test!";
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
