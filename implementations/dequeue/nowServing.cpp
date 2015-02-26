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
	bool emergency;
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

	try
	{
		Deque<Student> helpDequeue(8);
		string line;
		string className;
		string name;
		string action;
		int timeNeeded;
		Student currentHelpedStudent;
		currentHelpedStudent.className = "";
		currentHelpedStudent.name = "";
		currentHelpedStudent.minutes = 0;
		currentHelpedStudent.emergency = false;

		//Clear buffer (from previous cin's)
		cin.ignore(1000, '\n');
		for (int index = 0; true; index++)
		{
			//get user input
			cout << "<" << index << "> ";
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
					goto afterPushes; //Skip this for loop for getting more info
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
				Student newHomework;
				newHomework.className = className;
				newHomework.minutes = timeNeeded;
				newHomework.name = name;
				newHomework.emergency = false;
				if (currentHelpedStudent.name == "")
				{
					currentHelpedStudent = newHomework;
				}
				else
				{
					helpDequeue.push_back(newHomework);
				}
			}
			else if (action == "pushToFront")
			{
				Student newHomework;
				newHomework.className = className;
				newHomework.minutes = timeNeeded;
				newHomework.name = name;
				newHomework.emergency = true;
				if (currentHelpedStudent.name == "")
				{
					currentHelpedStudent = newHomework;
				}
				else
				{
					helpDequeue.push_front(newHomework);
				}
			}
		afterPushes:
			{
				if (currentHelpedStudent.minutes <= 0) //possibly pop whoever is next if time is up
				{
					if (!helpDequeue.empty())
					{
						currentHelpedStudent = helpDequeue.front();
						helpDequeue.pop_front();
					}
					else
					{
						currentHelpedStudent.name = "";
						currentHelpedStudent.className = "";
						currentHelpedStudent.minutes = 0;
						currentHelpedStudent.emergency = false;
					}
				}
				//Here is where we want to output
				if (currentHelpedStudent.name != "") //change to real conditional statement
				{
					if (currentHelpedStudent.emergency)
					{
						cout << "\tEmergency for ";
					}
					else
					{
						cout << "\tCurrently serving ";
					}
					cout << currentHelpedStudent.name << " for class "
						<< currentHelpedStudent.className << ". Time left: "
						<< currentHelpedStudent.minutes << "\n";
					currentHelpedStudent.minutes--;
				}
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


