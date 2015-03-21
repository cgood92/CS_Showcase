/***********************************************************************
 * Module:
 *    Lesson 10, Sort Bubble
 *    Brother Helfrich, CS 235
 * Author:
 *    Clint Goodman and Parker Hubbard
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
   T sideValue;
   int numToObserve = num - 1;
   do
   {
      for (int i = 0; i < numToObserve; i++)
      {
         if (array[i] > array[i + 1])
         {

            sideValue = array[i + 1];
            array[i + 1] = array[i];
            array[i] = sideValue;

         }
      }
      numToObserve = numToObserve - 1;
   }while (numToObserve > 1);
}


#endif // SORT_BUBBLE_H
