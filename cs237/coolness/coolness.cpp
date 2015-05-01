/*************************************************************************
* Binary Predicates and Nested Quantifiers Implementation
*************************************************************************/
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
#include "words.h"
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
}

/*************************************************************************
 * usage
 *
 * Tells the user how to use the program.
 *************************************************************************/
void usage(const char * programName)
{
}

/***************************************************************
 * Runs one test, identified by its string argument.
 ***************************************************************/
void runOne(string test)
{
   cout << "\nRunning test " << test << endl;
}

/***************************************************************
 * Runs all tests.
 ***************************************************************/
void runAll()
{
   cout << "Running all tests.\n";
}

