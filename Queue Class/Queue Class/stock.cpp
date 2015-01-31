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
	   Queue <Transaction> buyHistory;
	   Queue <Transaction> sellHistory;
	   string action;
	   Dollars proceeds(0);
	   while (action != "quit")
	   {
		   cout << "> ";
		   cin >> action;
		   int qty = 20;
		   Dollars price(20.50);
		   if (action == "buy")
		   {
			   Transaction trans;
			   trans.action = "Buy";
			   trans.amt = price;
			   trans.qty = qty;
			   buyHistory.push(trans);
		   }
		   else if (action == "sell")
		   {
			   Dollars temp(proceeds);
			   int tempQty = qty;
			   while (tempQty > 0)
			   {
				   if (buyHistory.empty())
				   {
					   throw "Big problem";
				   }
				   if (buyHistory.front().qty > tempQty)
				   {
					   buyHistory.front().qty -= tempQty;
					   proceeds += buyHistory.front().amt * tempQty;
					   tempQty = 0;
				   }
				   else
				   {
					   proceeds += buyHistory.front().amt * buyHistory.front().qty;
					   tempQty -= buyHistory.front().qty;
					   buyHistory.pop();
				   }
			   }
			   Transaction trans;
			   trans.action = "Sell";
			   trans.amt = price;
			   trans.qty = qty;
			   trans.profit = proceeds - temp;

			   sellHistory.push(trans);
		   }
		   else if (action == "display")
		   {
			   Queue <Transaction> tempBuy(buyHistory);
			   Queue <Transaction> tempSell(sellHistory);
			   if (!tempBuy.empty())
				   cout << "Currently held:";
			   for (; !tempBuy.empty(); tempBuy.pop())
			   {
				   cout << "\n\t";
				   cout << "Bought " << qty << " shares at " << tempBuy.front().amt;
			   }
			   if (!tempSell.empty())
				   cout << "\nSell History:";
			   for (; !tempSell.empty(); tempSell.pop())
			   {
				   cout << "\n\t";
				   cout << "Sold " << qty << " shares at $2.00 for a profit of " << tempSell.front().profit;
			   }
			   cout << "\nProceeds: " << proceeds << endl;
		   }
		   else if (action == "quit")
		   {
			   break;
		   }
		   else
		   {

		   }
	   }

   }
   catch (const char * error)
   {
	   cout << error << endl;
	   string quit;
	   cin >> quit;
   }
}