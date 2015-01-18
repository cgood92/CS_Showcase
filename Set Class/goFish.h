/*
  THE REST BELONGS TO THE goFish.h THEN goFish.cpp
* Program :
* Lesson 01, Sets
*    Brother Sloan, CS 235
* Author :
*Clint Goodman and Parker Hubbard
* Summary :
*********************************************************************** */
#ifndef GOFISH_H
#define GOFISH_H

#include <cassert>
#include <iostream>
#include <string>

#include "set.h"
//#include <set>
#include "card.h"
using namespace std;
#include <fstream>

//template <class TT>
class goFish
{
public:
	goFish()
	{
		play();
	}
	void play();
};
#endif