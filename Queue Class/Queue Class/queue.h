/***********************************************************************
 * Program:
 *    Lesson 3, Queue
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

/**********************************************************************
 * Stack
 * //creating the class for Stacks
 ***********************************************************************/
template <class T>
class Queue
{
  private:
     T * data;      //dynamically allocated array of T
     int frontSpot; //the "X" value of where the bottum/front item is found
     int backSpot;  //the "X" value of where the top/back item is found
     int current_size;  //the current Set size, or number of items
     int capacity_size; //how many items can I put on the Set before full?
     void resize(int newCapacity) throw (bad_alloc);
  public:
     // default constructor :
     Queue() : data(NULL) {}
     // copy constructor : copy details of another indicated
  Queue(const Queue<T> & rhs) : data(NULL), current_size(0), capacity_size(0), frontSpot(-1), backSpot(-1)
     {
        if (rhs.size())   { *this = rhs; }
     }
     // non-default constructor : pre-allocate
  Queue(int capacity) : data(NULL), current_size(0), capacity_size(0), frontSpot(-1), backSpot(-1)
     {
        if (capacity > 0) { resize(capacity); }
     }
     // destructor : free everything that was previously used
     ~Queue()
     {
        if (NULL != data)//(capacity)
        {  //assert(capacity);
           delete[] data;
        }
     }
     
     /////////COMMANDS///////////////////
     //size(): Return the Setsize
     int size()        const{ return current_size; }
     //empty(): Test whether the set is empty
     bool empty()      //const { return current_size == 0; }
     //POSSIBLY INDICATE EMPTY WHEN FRONT_SPOT == BACK_SPOT
        const { return backSpot == -1; }
};
#endif
