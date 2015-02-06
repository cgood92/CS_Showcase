/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <sstream>
#include <string>      // for STRING
#include <cassert>     // for ASSERT

#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

struct Student
{
	string className;
   string name;
   int minutes;
};

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here

   try
   {
      Deque<Student> helpDequeue;
      string line;
      string className;
	  string name;
	  string action;
	  int timeNeeded;
      
      //Clear buffer (from previous cin's)
      cin.ignore(1000, '\n');
      getInput:while (true)
      {
         //get user input
         cout << "> ";
         getline(std::cin, line);

         //get the individual pieces from the line
         std::stringstream  linestream(line);
         string lineTemp;
		 action = "push"; //No action defined yet (default push).  Only action possible is pop
         for (int i = 0; i <= 2; i++)
         {
            linestream >> lineTemp;
			if (i == 0 && lineTemp == "!!")
			{
				action = "pushToFront";
				i--;
				continue; //Skip this pass through the foor loop and jump ahead
			}
			else if (i == 0 && lineTemp == "none")
			{
				break; //Skip this for loop for getting more info
			}
			else if (i == 0 && lineTemp == "finished")
			{
				cout << "End of simulation\n";
				return; //Return will end the entire function (aka close the function)
			}
			//This works for both pop and push
            switch (i)
            {
               case 0:
                  className = lineTemp;
                  break;
			   case 1:
				   name = lineTemp;
				   break;
               case 2:
                  istringstream(lineTemp) >> timeNeeded;
                  break;
            }
         }
         if (action == "push")
         {
			 //For testing only.  We don't want to output anything here, but down below
            cout << "push:" << className << ":" << name << ":" << timeNeeded << endl;
         }
         else if (action == "pushToFront")
         {
			 //For testing only.  We don't want to output anything here, but down below
			 cout << "pushToFront:" << className << ":" << name << ":" << timeNeeded << endl;
         }
		 else if (!helpDequeue.empty() && helpDequeue.front().minutes <= 0) //possibly pop whoever is next if time is up
		 {
			helpDequeue.pop_front();
		 }

		 //Here is where we want to output
		 if (!helpDequeue.empty()) //change to real conditional statement
		 {
			 //Minus the time
			 helpDequeue.front().minutes--;
			 cout << "\tCurrently serving " << helpDequeue.front().name << "for class " << helpDequeue.front().className << ".  Time left: " << helpDequeue.front().minutes << "\n";
		 }
		 else
		 {
			 cout << "None";
		 }
      }
   }
   // finished!
   catch (const char * error)
   {
      //Catch errors
      cout << error << endl;
   }
}


