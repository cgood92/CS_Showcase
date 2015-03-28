/***********************************************************************
 * Module:
 *    Lesson 11, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "list.h"
#include "spellCheck.h"
#include "hash.h"

using namespace std;

string StringToUpper(string strToConvert)
{
	for (std::string::iterator p = strToConvert.begin(); strToConvert.end() != p; ++p)
		*p = toupper(*p);

	return strToConvert;
}

/****************************************
 * S HASH
 * A simple hash of strings
 ****************************************/
class SHash : public Hash <string>
{
public:
   SHash(int numBuckets)    throw (const char *) : Hash <string> (numBuckets){}
   SHash(const SHash & rhs) throw (const char *) : Hash <string> (rhs)       {}

   // hash function for strings will add up all the ASCII values
   int hash(const string & s) const
   {
      int value = 0;
	  for (const char * p = s.c_str(); *p; p++)
         value += *p;
      return value % capacity();
   }
};

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
   //1) create the "Hash"
   SHash dictionary(26);
   string command;
   char dictionaryFile[256];
   string word;

   //2) read a file, enter each word into the hash
   ifstream fin;
   fin.open("dictionary.txt");
   while (fin >> word)
   {
      dictionary.insert(StringToUpper(word));
   }
   fin.close();

   //3) ask for the file we wish for the user to spellcheck
   cout << "What file do you want to check? ";
   char fileName[256];
   cin >> fileName;
   
   List<string> mispelled;
   //4) spellCheck the file
   fin.open(fileName);
   while (fin >> word)
   {
      if (!dictionary.find(StringToUpper(word)))
      {
		  mispelled.push_back(word);
      }
   }
   fin.close();

   //5) show the words that were not in the dictionary
   if (mispelled.empty())
   {
      cout << "File contains no spelling errors\n";
   }
   else
   {
      cout << "Misspelled: ";
	  for (ListIterator <string> it = mispelled.begin(); it != mispelled.end(); ++it)
	  {
		  if (it != mispelled.begin())
		  {
			  cout << ", ";
		  }
		  cout << *it;
	  }
   }
   cout << "\n";
}
