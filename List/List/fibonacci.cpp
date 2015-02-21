/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
using namespace std;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   for (int i = 1, a = 0, b = 1, temp = 0; i <= number; i++)
   {
	   if (i == 1)
	   {
		  cout << "1" << endl;
		  continue;
	   }
	   temp = a + b;
	   a = b;
	   b = temp;
	   cout << b << endl;
   }


   //prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;
   WholeNumber aa; 
   WholeNumber bb;
   WholeNumber temptemp;
   WholeNumber cc;
   aa = 3;
   bb = 3;
   cc = 3;
   temptemp = 0;
   cout << "Got here";
   //cout << a << b << c << endl;
   //cout << a + b << endl;
   cout << "Got here2" << endl;
   temptemp = aa + bb;

   cout << temptemp;
   cout << "next!\n";
   temptemp = temptemp + cc;
   cout << temptemp;
   //cout << "\nNumber1: " << temp << endl;
   //temp = b + b;
   //cout << "\nNumber2:" << temp << endl;
   //c = b + a;
   //cout << "\nNumberb:" << c << endl;
   //temp = c + b;
   //cout << "\nNumber3:" << temp << endl;
   /*for (int i = 1; i <= number; i++)
   {
	   if (i == 1)
	   {
		   continue;
	   }
	   temp = a + b;
	   a = b;
	   b = temp;
	   cout << b << endl;
   }*/
}

