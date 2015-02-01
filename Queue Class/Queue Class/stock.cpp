/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <sstream>
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include <math.h>
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "dollars.h"     // 
using namespace std;

struct Transaction
{
	string action;
	Dollars amt;
	int qty;
	Dollars profit;
};

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   try
   {
	   //Variables
	   Queue <Transaction> buyHistory;
	   Queue <Transaction> sellHistory;
	   string line;

	   string action;
	   int qty;
	   Dollars price(0);
	   Dollars proceeds(0);
	   
	   //Clear buffer (from previous cin's)
	   cin.ignore(1000, '\n');
	   while (true)
	   {
		   //Get inputs
		   cout << "> ";
		   getline(std::cin, line);

		   //This may seem a little tacky, but this allows us to get the action (first word),
		   //convert the qty to an int, and then after is our price
		   std::stringstream  linestream(line);
		   string lineTemp;
		   for (int i = 0; i < 2; i++)
		   {
			   linestream >> lineTemp;
			   switch (i)
			   {
			   case 0:
				   action = lineTemp;
				   break;
			   case 1:
				   istringstream(lineTemp) >> qty;
				   break;
			   }
		   }
		   //Special hack to get price right.  Putting it in above was creating problems, so we need to insert via istream (other ways did not work)
		   linestream >> price;

		   //Determine actions
		   if (action == "buy")
		   {
			   //Creat our transaction
			   Transaction trans;
			   trans.action = "Buy";
			   trans.amt = price;
			   trans.qty = qty;
			   buyHistory.push(trans);
		   }
		   else if (action == "sell")
		   {
			   //temp is used for figuring out profit
			   Dollars temp(proceeds);
			   //tempQty is used so that if we need to borrow stocks from more than one transaction, we can determine
			   //how many more we have left to borrow
			   int tempQty = qty;
			   while (tempQty > 0)
			   {
				   if (buyHistory.empty())
				   {
					   throw "Selling more stocks than you currently own!";
				   }
				   //More stocks in the first transaction than we need
				   if (buyHistory.front().qty > tempQty)
				   {
					   //Subtract from transaction
					   buyHistory.front().qty -= tempQty;
					   proceeds += (price - buyHistory.front().amt) * tempQty;

					   Transaction trans;
					   trans.action = "Sell";
					   trans.amt = price;
					   trans.qty = tempQty;
					   trans.profit = (price - buyHistory.front().amt) * tempQty;

					   sellHistory.push(trans);

					   tempQty = 0;
				   }
				   //We're going to have to use the whole first transaction, then some more
				   else
				   {
					   proceeds += (price - buyHistory.front().amt) * buyHistory.front().qty;
					   tempQty -= buyHistory.front().qty;

					   Transaction trans;
					   trans.action = "Sell";
					   trans.amt = price;
					   trans.qty = buyHistory.front().qty;
					   trans.profit = (price - buyHistory.front().amt) * buyHistory.front().qty;

					   sellHistory.push(trans);
					   //Sell all of first transaction
					   buyHistory.pop();
				   }
			   }
		   }
		   else if (action == "display")
		   {
			   //Create temporary queues for display purposes only.  Suggested by Bro. Sloan
			   Queue <Transaction> tempBuy(buyHistory);
			   Queue <Transaction> tempSell(sellHistory);
			   if (!tempBuy.empty())
				   cout << "Currently held:\n";
			   for (; !tempBuy.empty(); tempBuy.pop())
			   {
				   cout << "\t";
				   cout << "Bought " << tempBuy.front().qty << " shares at " << tempBuy.front().amt << endl;
			   }
			   if (!tempSell.empty())
				   cout << "Sell History:\n";
			   for (; !tempSell.empty(); tempSell.pop())
			   {
				   cout << "\t";
				   cout << "Sold " << tempSell.front().qty << " shares at " << tempSell.front().amt << " for a profit of " << tempSell.front().profit << endl;
			   }
			   cout << "Proceeds: " << proceeds << endl;
		   }
		   else if (action == "quit")
		   {
			   //Quit the while loop
			   break;
		   }
		   else
		   {

		   }
	   }
   }
   catch (const char * error)
   {
	   //Catch errors
	   cout << error << endl;
   }
}