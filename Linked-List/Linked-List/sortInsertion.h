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
	//Convert array to linked list (will be useful in next assignment)
	for (int i = 0; i < num; i++)
	{
		insert(array[i], unsortedList);
	}
   Node <T> * sortedList = NULL;

   //Loop through all items
   //For comments sake, we will call this loop 1
   //pu indicates: pointer-to-unsorted, and ps indicates: pointer-to-sorted
   for (Node <T> * pu = unsortedList; pu; pu = pu->pNext)
   {
	   //first time through - no need to sort, just put in front
	   if (!sortedList)
	   {
		   insert(pu->data, sortedList, true);
		   continue;
	   }
	   //Compare this item (in the unsorted list) with every item in the sorted list
	   //For comments sake, we will call this loop 2
	   for (Node <T> * ps = sortedList; ps; ps = ps->pNext)
	   {
		   /* The following will place at the head the data value
		   * Conditions under which we want things at the head:
		   *   1) This is smaller than the current head
		   */
		   if (pu->data < sortedList->data)
		   {
			   insert(pu->data, sortedList, true);
			   break;
		   }
		   /* The following will place the data right after the current position we are in at loop 2
		   * Conditions under which we want things at the head:
		   *   1) The data is smaller than what is coming up after this current loop 2 iteration
		   *     - Note: In order to check ps->pNext->data, and not have access violations, we must ensure that there
		   *       is a pNext before we compare this with that.  If there is no pNext, immediately that first condition is false
		   *   OR 2) This is the last time through this loop (there is no pNext indicates last item)
		   */
		   if ((ps->pNext && pu->data < ps->pNext->data) || !ps->pNext)
		   {
			   insert(pu->data, ps);
			   break;
		   }
	   }
   }

// add all items of linked list to the previous array
   int jj = 0;
   for (Node <T> * ph = sortedList; ph; ph = ph->pNext)
   {
      array[jj] = ph->data;
      jj = jj + 1;
   }
}

#endif // INSERTION_SORT_H

