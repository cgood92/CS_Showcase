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
   Node <T> * n = NULL;
/***********************************************
 * 1) add all items unto the list from the array (back to front)
 **********************************************/
   for (int i = num - 1; i >= 0; i--)
   {
	   //first time throug - no need to sort, just put in front
	   if (i == num - 1)
	   {
		   insert(array[i], n, true);
		   continue;
	   }
	   //Check to see if this value is less than something in the array (if so, place it where it fits)
	   for (Node <T> * ph = n; ph; ph = ph->pNext)
	   {
		   //If this is going to replace the head...
		   if (ph->data == n->data && array[i] < ph->data)
		   {
			   insert(array[i], n, true);
			   break;
		   }
		   //If this is next up, or this is the end of the list ...
		   if (ph->pNext && array[i] < ph->pNext->data || !ph->pNext)
		   {
			   insert(array[i], ph);
			   break;
		   }
	   }
   }

/***********************************************
 * add all items of linked list (possibly sorted)
 * to the previous array
 **********************************************/
   int jj = 0;
   for (Node <T> * ph = n; ph; ph = ph->pNext)
   {
      array[jj] = ph->data;
      jj = jj + 1;
   }
}

#endif // INSERTION_SORT_H

