/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Sloan, CS 235
* Author:
*     Clint Goodman and Parker Hubbard
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include "set.h"
#include "card.h"
#include "goFish.h"
using namespace std;

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish::play()
{
	// Make a set to store the cards
	Set <Card> cards;
	// Make an input file stream
	ifstream fin("/home/cs235/lesson01/hand.txt");

	string line;
	while (std::getline(fin, line))
	{
		std::stringstream  linestream(line);
		Card thisCard;

		while (linestream >> thisCard)
		{
			cards.insert(thisCard);
		}
	}
	// Close the file
	fin.close();

	Card guessCard;
	int numMatches = 0;
	cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand\n";
		for (int n = 1; n <= 5; n++)
		{
			cout << "round " << n << ": ";
			cin >> guessCard;
			SetIterator<Card> cardIt;
			cardIt = cards.find(guessCard);
			if (cardIt != cards.end())
			{
				cout << "\tYou got a match!\n";
				cards.erase(cardIt);
				numMatches++;
			}
			else
			{
				cout << "\tGo Fish!" << endl;
			}
		}
	cout << "You have " << numMatches << " matches!\n";
	cout << "The remaining cards: ";
	for (SetIterator<Card> it = cards.begin(); it != cards.end(); ++it)
		cout << (it != cards.begin() ? ", " : "") << *it;
	cout << endl;
}
