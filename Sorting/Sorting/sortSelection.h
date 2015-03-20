/***********************************************************************
 * Module:
 *    Lesson 10, Sort Select
 *    Brother Helfrich, CS 235
 * Author:
 *    Clint Goodman and Parker Hubbard
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H
#include <iostream>   // for COUT, CIN, CERR
#include <string>
using namespace std;

/*****************************************************
 * SORT SELECTION
 * Perform the selection sort
 ****************************************************/
template <class T>
void sortSelection(T array[], int num)
{
   //start the smallest item at item 0 of the array
   int numToObserve = num - 1;
   T smallestSoFar = array[0];
   int startSpot = 0;


   for (int hh = numToObserve; hh > 0; hh--)
   {
      smallestSoFar = array[startSpot];
      //go through the list, find the smallest value to start with
      for (int i = numToObserve; i > startSpot; i--)
      {
         //if we find a value smaller than the current smallest item
         //set the smallest pointer to this spot of the array
         if (smallestSoFar > array[i])
         {
            smallestSoFar = array[i];         
         }
      }
      //now find the spot
      for (int k = numToObserve; k > startSpot; k--)
      {
         //now find that spot, and switch the two values
         if (array[k] == smallestSoFar)
         {
            T save = array[startSpot];
            array[startSpot] = array[k];
            array[k] = save;
            break;
         }
      }

      startSpot = startSpot + 1;
         
   }
}
#endif // SORT_SELECTION_H
