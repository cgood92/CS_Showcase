/***********************************************************************
 * Module:
 *    Lesson 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
/*
In addition to passing the four test functions for the Stack class, you will also need to use the Stack class to implement a program to convert an infix expression (4 + 8 * 3) into a postfix expression (4 8 3 * +). There is a discussion on this in chapter 7.5 of the textbook. Note that you will need to handle the following operators:

() The parentheses are the highest level of the order of operations.
^ The exponent operator comes immediately after the parentheses. Note that the algorithm in the textbook cannot handle the exponent operator properly. You will need to handle this case.
* / % Multiplication, division, and modulus are after the exponent operator. They are at the same level of the order of operations.
+ - Addition and subtraction are after multiplication, division, and modulus.

*/
string convertInfixToPostfix(const string & infix)
{
   string postfix;
   Stack<char> operators;

   bool notAnOperator;
   char c;
   for (std::string::size_type i = 0; i < infix.size(); ++i)
   {
	   c = infix[i];
	   notAnOperator = false;
	   
	   //Check for operators
	   switch (c)
	   {
	   case '(':
		   operators.push(c);
		   break;
	   case ')':
		   for (char oper = operators.top(); !operators.empty() && oper != '('; operators.pop(), oper = operators.top())
		   {
			   postfix += ' ';
			   postfix += oper;
		   }
		   operators.pop(); // Get rid of left paranthesis
		   break;
	   case '^':
		   operators.push(c);
		   break;
	   case '*':
	   case '/':
	   case '%':
		   if (operators.empty() || operators.top() == '(')
		   {
			   operators.push(c);
		   }
		   else if (operators.top() == '+' || operators.top() == '-') //Greater precedence
		   {
			   operators.push(c);
		   }
		   else if (operators.top() == '*' || operators.top() == '*' || operators.top() == '/')
		   {
			   postfix += ' ';
			   postfix += operators.top();
			   operators.pop();
			   operators.push(c);
		   }
		   else //Less precedence
		   {
			   for (char oper = operators.top(); !operators.empty() && oper == '^'; operators.pop())
			   {
				   postfix += ' ';
				   postfix += oper;
			   }
		   }
		   break;
		case '+':
		case '-':
			if (operators.empty() || operators.top() == '(') //Empty or equal precedence
			{
				operators.push(c);
			}
			else if (operators.top() == '+' || operators.top() == '-')
			{
				postfix += ' ';
				postfix += operators.top();
				operators.pop();
				operators.push(c);
			}
			else //Lowest precedence
			{
				for (char oper = operators.top(); !operators.empty() && (oper == '^' || oper == '*' || oper == '/' || oper == '%'); operators.pop())
				{
					postfix += ' ';
					postfix += operators.top();
				}
				operators.push(c);
			}
		   break;
		default:
			notAnOperator = true;
			break;
	   }

	   //Skip if it was an operator (performance)
	   if (!notAnOperator)
		   continue;

	   postfix += c;
   }

   if (!operators.empty())
   {
	   for (; !operators.empty(); operators.pop())
	   {
		   postfix += ' ';
		   postfix += operators.top();
	   }
   }

   //Print out the operators

   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;


   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
