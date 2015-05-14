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


//Setting up for the real world example
struct action
{
	bool good;
	string description;
};

struct consequence
{
	bool blessing;
	string description;
};

//This method is used to compare actions with consequences
bool operator== (action & myaction, consequence & mycon)
{
	return (myaction.good == mycon.blessing);
}

/*
These next 3 functions are for the purpose of compiling error-free only.  Because of the way I designed my functions,
a subclass will be instantiated for the struct <action, consequence>, and must have these 3 operators defined,
for they are used in the GreaterThan, LessThan, and FactorOf subclasses
*/
bool operator > (action & myaction, consequence & mycon)
{
	return false;
}

bool operator < (action & myaction, consequence & mycon)
{
	return false;
}

bool operator % (action & myaction, consequence & mycon)
{
	return false;
}

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
class GreaterThan : public Predicate<T1, T2>
{
public:
   bool isTrue(T1 x, T2 y)
   {
      return (x > y);
   }

   bool isFalse(T1 x, T2 y)
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

template<typename T1, typename T2>
class LawOfRestoration : public Predicate<T1, T2>
{
public:
	bool isTrue(T1 myaction, T2 myconsequence)
	{
		return (myaction ==  myconsequence);
	}
	bool isFalse(T1 myaction, T2 myconsequence)
	{
		return !isTrue(myaction, myconsequence);
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
		<< "\n\tbooelans being inverted.  I found that to be lawing.  Again, to sum up, the most important"
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
template<typename T1, typename T2>
void runForAllForAll(string test, vector<T1> d1, vector<T2> d2, bool booleanExpected)
{
	cout << boolalpha;
	cout << test << ".forAllForAll(d1, d2)\n"
		<< "     expected to return " << booleanExpected << "; \n"
		<< " actual return value is ";

	//run the predicate test specified
	//Greater than
	if (test == "gt")
	{
		GreaterThan<T1, T2> gt;
		cout << gt.forAllForAll(d1, d2) << ".";
	}
	//Less than
	else if (test == "lt")
	{
		LessThan<T1, T2> lt;
		cout << lt.forAllForAll(d1, d2) << ".";
	}
	//Factor of
	else if (test == "fo")
	{
		FactorOf<T1, T2> fo;
		cout << fo.forAllForAll(d1, d2) << ".";
	}
	//Special
	else if (test == "sp")
	{
		LawOfRestoration<T1, T2> law;
		cout << law.forAllForAll(d1, d2) << ".";

		//Special comments (for fun)
		if (law.forAllForAll(d1, d2))
		{
			cout << "\nYou live your life perfectly!\n";
		}
		else
		{
			cout << "\nYou are quite a sinner!\n";
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
template<typename T1, typename T2>
void runForAllForSome(string test, vector<T1> d1, vector<T2> d2, bool booleanExpected)
{
	cout << boolalpha;
	cout << test << ".forAllForSome(d1, d2)\n"
		<< "     expected to return " << booleanExpected << "; \n"
		<< " actual return value is ";

	//run the predicate test specified
	//Greater than
	if (test == "gt")
	{
		GreaterThan<T1, T2> gt;
		cout << gt.forAllForSome(d1, d2) << ".";
	}
	//Less than
	else if (test == "lt")
	{
		LessThan<T1, T2> lt;
		cout << lt.forAllForSome(d1, d2) << ".";
	}
	//Factor of
	else if (test == "fo")
	{
		FactorOf<T1, T2> fo;
		cout << fo.forAllForSome(d1, d2) << ".";
	}
	//Special
	else if (test == "sp")
	{
		LawOfRestoration<T1, T2> law;
		cout << law.forAllForSome(d1, d2) << ".";

		//Special comments (for fun)
		if (law.forAllForSome(d1, d2))
		{
			cout << "\nFor every good deed, there is a blessing in store.!\n";
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
template<typename T1, typename T2>
void runForSomeForAll(string test, vector<T1> d1, vector<T2> d2, bool booleanExpected)
{
	cout << boolalpha;
	cout << test << ".forSomeForAll(d1, d2)\n"
		<< "     expected to return " << booleanExpected << "; \n"
		<< " actual return value is ";

	//run the predicate test specified
	//Greater than
	if (test == "gt")
	{
		GreaterThan<T1, T2> gt;
		cout << gt.forSomeForAll(d1, d2) << ".";
	}
	//Less than
	else if (test == "lt")
	{
		LessThan<T1, T2> lt;
		cout << lt.forSomeForAll(d1, d2) << ".";
	}
	//Factor of
	else if (test == "fo")
	{
		FactorOf<T1, T2> fo;
		cout << fo.forSomeForAll(d1, d2) << ".";
	}
	//Special
	else if (test == "sp")
	{
		LawOfRestoration<T1, T2> law;
		cout << law.forSomeForAll(d1, d2) << ".";
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
template<typename T1, typename T2>
void runForSomeForSome(string test, vector<T1> d1, vector<T2> d2, bool booleanExpected)
{
	cout << boolalpha;
	cout << test << ".forSomeForSome(d1, d2)\n"
		<< "     expected to return " << booleanExpected << "; \n"
		<< " actual return value is ";

	//run the predicate test specified
	//Greater than
	if (test == "gt")
	{
		GreaterThan<T1, T2> gt;
		cout << gt.forSomeForSome(d1, d2) << ".";
	}
	//Less than
	else if (test == "lt")
	{
		LessThan<T1, T2> lt;
		cout << lt.forSomeForSome(d1, d2) << ".";
	}
	//Factor of
	else if (test == "fo")
	{
		FactorOf<T1, T2> fo;
		cout << fo.forSomeForSome(d1, d2) << ".";
	}
	//Special
	else if (test == "sp")
	{
		LawOfRestoration<T1, T2> law;
		cout << law.forSomeForSome(d1, d2) << ".";

		//Special comments (for fun)
		if (law.forSomeForSome(d1, d2))
		{
			cout << "\n\nThere is a blessing for a good deed.\n";
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

	//Good actions only
	vector<action> actions1;
	actions1.push_back(action{ true, "Helped old lady across the street" });
	actions1.push_back(action{ true, "Raked the leaves in the yard" });
	actions1.push_back(action{ true, "Read my scriptures" });
	actions1.push_back(action{ true, "Prayed in the morning" });
	actions1.push_back(action{ true, "Exercised" });
	actions1.push_back(action{ true, "Cleaned the house" });

	//Blessings only
	vector<consequence> cons1;
	cons1.push_back(consequence{ true, "Wisdom" });
	cons1.push_back(consequence{ true, "Peace" });
	cons1.push_back(consequence{ true, "Forgiveness" });
	cons1.push_back(consequence{ true, "Mercy" });
	cons1.push_back(consequence{ true, "Grace" });

	//Mixed actions - for some for some
	vector<action> actions2;
	actions2.push_back(action{ true, "Made cookies for neighbors" });
	actions2.push_back(action{ true, "Cleaned the church" });
	actions2.push_back(action{ true, "Missionary work" });
	actions2.push_back(action{ false, "Stole a popsicle" });
	actions2.push_back(action{ false, "Vandalized the school" });

	//Mixed consequences - for some for some
	vector<consequence> cons2;
	cons2.push_back(consequence{ true, "Happiness" });
	cons2.push_back(consequence{ true, "Love" });
	cons2.push_back(consequence{ false, "Guilt" });
	cons2.push_back(consequence{ false, "Shame" });
	cons2.push_back(consequence{ false, "Confusion" });

	//Sins only
	vector<action> actions3;
	actions3.push_back(action{ false, "Steal a care" });
	actions3.push_back(action{ false, "Eat junk food" });
	actions3.push_back(action{ false, "View pornography" });
	actions3.push_back(action{ false, "Lie" });

	//Curses only
	vector<consequence> cons3;
	cons3.push_back(consequence{ false, "Hellfire" });
	cons3.push_back(consequence{ false, "Sadness" });
	cons3.push_back(consequence{ false, "Misery" });
	cons3.push_back(consequence{ false, "Damnation" });

   cout << "\nRunning test " << test << "\n\n";
   if (test == "TAA")
   {
	   runForAllForAll("gt", bigNums, smallNums, true);
	   runForAllForAll("lt", smallNums, bigNums, true);
	   runForAllForAll("fo", factorables, factors, true);
	   runForAllForAll("sp", actions1, cons1, true);
   }
   else if (test == "FAA")
   {
	   runForAllForAll("gt", smallNums, bigNums, false);
	   runForAllForAll("lt", bigNums, smallNums, false);
	   runForAllForAll("fo", factors, factorables, false);
	   runForAllForAll("sp", actions1, cons3, false);
   }
   else if (test == "TAS")
   {
	   runForAllForSome("gt", bigNums, smallNums, true);
	   runForAllForSome("lt", smallNums, bigNums, true);
	   runForAllForSome("fo", factorables, factors, true);
	   runForAllForSome("sp", actions1, cons2, true);
   }
   else if (test == "FAS")
   {
	   runForAllForSome("gt", smallNums, bigNums, false);
	   runForAllForSome("lt", bigNums, smallNums, false);
	   runForAllForSome("fo", factors, factorables, false);
	   runForAllForSome("sp", actions1, cons3, false);
   }
   else if (test == "TSA")
   {
	   runForSomeForAll("gt", bigNums, smallNums, true);
	   runForSomeForAll("lt", smallNums, bigNums, true);
	   runForSomeForAll("fo", factorables, factors, true);
	   runForSomeForAll("sp", actions2, cons1, true);
   }
   else if (test == "FSA")
   {
	   runForSomeForAll("gt", smallNums, bigNums, false);
	   runForSomeForAll("lt", bigNums, smallNums, false);
	   runForSomeForAll("fo", factors, factorables, false);
	   runForSomeForAll("sp", actions1, cons2, false);
   }
   else if (test == "TSS")
   {
	   runForSomeForSome("gt", bigNums, smallNums, true);
	   runForSomeForSome("lt", smallNums, bigNums, true);
	   runForSomeForSome("fo", factorables, factors, true);
	   runForSomeForSome("sp", actions2, cons2, true);
   }
   else if (test == "FSS")
   {
	   runForSomeForSome("gt", smallNums, bigNums, false);
	   runForSomeForSome("lt", bigNums, smallNums, false);
	   runForSomeForSome("fo", factors, factorables, false);
	   runForSomeForSome("sp", actions1, cons3, false);
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
