/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Clint Goodman and Parker Hubbard
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{  
	Node <T> * unsortedList = NULL;
	for (int i = 0; i < num; i++)
	{
		insert(array[i], unsortedList);
	}
   Node <T> * sortedList = NULL;
/***********************************************
 * 1) add all items unto the list from the array (back to front)
 **********************************************/
   for (Node <T> * pu = unsortedList; pu; pu = pu->pNext)
   {
	   //first time throug - no need to sort, just put in front
	   if (!sortedList)
	   {
		   insert(pu->data, sortedList, true);
		   continue;
	   }
	   //Check to see if this value is less than something in the array (if so, place it where it fits)
	   for (Node <T> * ps = sortedList; ps; ps = ps->pNext)
	   {
		   //If this is going to replace the head...
		   if (ps->data == sortedList->data && pu->data < ps->data)
		   {
			   insert(pu->data, sortedList, true);
			   break;
		   }
		   //If this is next up, or this is the end of the list ...
		   if (ps->pNext && pu->data < ps->pNext->data || !ps->pNext)
		   {
			   insert(pu->data, ps);
			   break;
		   }
	   }
   }

/***********************************************
 * add all items of linked list (possibly sorted)
 * to the previous array
 **********************************************/
   int jj = 0;
   for (Node <T> * ph = sortedList; ph; ph = ph->pNext)
   {
      array[jj] = ph->data;
      jj = jj + 1;
   }
}

#endif // INSERTION_SORT_H

