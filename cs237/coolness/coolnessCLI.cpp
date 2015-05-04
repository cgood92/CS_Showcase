/***************************************************************
 * Binary Predicates and Nested Quantifiers Implementation
 ***************************************************************/
#include <cstdlib>
#include <string>
#include <iostream>
#include "coolnessBinary.h"
using namespace std;


/***************************************************************
 * main looks at its command-line parameters.
 * If none, it calls two functions in order, namely
 *   learned
 *   usage
 * Otherwise it calls runOne with each parameter, with "all" as
 * a special case. If there is only "all" then it calls runAll.
 ***************************************************************/
int main(int argc, const char* argv[])
{
	vector<int> incomes;
	vector<int> expenses;

	//Bigger
	incomes.push_back(31);
	incomes.push_back(47);
	incomes.push_back(13);
	incomes.push_back(24);
	incomes.push_back(25);
	incomes.push_back(67);
	incomes.push_back(68);
	incomes.push_back(79);

	//Lower except for one
	expenses.push_back(1);
	expenses.push_back(2);
	expenses.push_back(79);
	expenses.push_back(3);
	expenses.push_back(12);
	expenses.push_back(11);
	expenses.push_back(10);

	GreaterThan<int, int> test1;
	cout << boolalpha;

   if (argc == 1)
   {
      learned();
      usage(argv[0]);
   }
   else if ((argc == 2) &&
            ("all" == string(argv[1])))
   {
      runAll(test1, expenses, incomes);
   }
   else
   {
      for (int i = 1; i < argc; i++)
      {
		 runOne<int, int>(test1, string(argv[i]), expenses, incomes);
      }
   }
   runAll(test1, expenses, incomes);
   return 0;
}   
