/***********************************************************************
 * Module:
 *    Lesson 10, Sort Insertion
 *    Brother Helfrich, CS 235
 * Author:
 *    Clint Goodman and Parker Hubbard
 * Summary:
 *    This program will implement the Insertion Sort
 ************************************************************************/

#ifndef SORT_INSERTION_H
#define SORT_INSERTION_H

#include <cassert>
#include <iostream>   // for COUT, CIN, CERR
#include <string>
#include "bst.h"
using namespace std;
   
/*****************************************************
 * SORT INSERTION
 * Perform the insertion sort
 ****************************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   int numToObserve = num;
   T CopiedArray[num];
   int numberAddedToCopy = 0;

   for (int p = 1; p < num; p++)
   {
      CopiedArray[p] = 0;
   }
   
   if ( numberAddedToCopy == 0)
   {
      CopiedArray[0] = array[0];
      numberAddedToCopy = numberAddedToCopy + 1;
   }

   for (int i = 1; i < (numToObserve); i++)
   {
      bool found = false;
      int first = 0;
      int last = numberAddedToCopy;
      int newMiddle = (last + first) / 2;
      
      do
      {
         newMiddle = (last + first) / 2;
         if (array[i] < CopiedArray[newMiddle])
         {
            last = newMiddle - 1;
         }
         else if(array[i] > CopiedArray[newMiddle])
         {
            first = newMiddle + 1;
         }
         else
         {
            found = true;
         }

      }while((first<=last) && (found == false));

      int currentAddition;
      
      //1) Check if new item is smaller than the first one of the array
      //   then add in front and move all others one over
      if ((newMiddle == 0) && (CopiedArray[0] > array[i]))
      {
         //move all to the right of it forward by one
         for (int f = numberAddedToCopy; f >= 0 ; f--)
         {
            CopiedArray[f + 1] = CopiedArray[f];
         }
         CopiedArray[0] = array[i];
      }
      //2) if larger than the last/rightmost item of the array
      else if ((newMiddle == last) &&
          (array[i] > CopiedArray[numberAddedToCopy - 1]))
      {
         CopiedArray[numberAddedToCopy] = array[i];         
      }
      //else add item to a spot in the middle of the array
      else
      {
         if (array[i] > CopiedArray[newMiddle])
         {
            for (int f = numberAddedToCopy; f > newMiddle; f--)
            {
               CopiedArray[f + 1] = CopiedArray[f];
            }
            CopiedArray[newMiddle + 1] = array[i];
         }
         //if new object is less than the item of current spot
         else if (array[i] < CopiedArray[newMiddle])
         {
            //move all to the right of it forward by one
            for (int f = numberAddedToCopy; f >= newMiddle; f--)
            {
               CopiedArray[f + 1] = CopiedArray[f];
            }
            //now add the item
            CopiedArray[newMiddle] = array[i];
         }
         //if new object is equal to the item of current spot
         else if (array[i] == CopiedArray[newMiddle])
         {
            //move all to the right of it forward by one
            for (int f = numberAddedToCopy; f >= newMiddle; f--)
            {
               CopiedArray[f + 1] = CopiedArray[f];
            }
            //now add the item
            CopiedArray[newMiddle] = array[i];
         }
      }
      //overall one more value has been added to the array
      numberAddedToCopy = numberAddedToCopy + 1;
   }

   //after all steps, give array what the copy has
   for (int k = 0; k < num; k++)
   {
     array[k] = CopiedArray[k];
   }
   
}


#endif // SORT_INSERTION_H
