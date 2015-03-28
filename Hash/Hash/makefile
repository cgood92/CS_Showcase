###############################################################
# Program:
#     Lesson 11, Hash
#     Brother Sloan, CS235
# Author:
#     Clint Goodman and Parker Hubbard
# Summary:
#     This hash table will hold a data type of N items, and will 
#	  be able to, in some cases in O(1) times, find that item.
#	  The hardest part was figuring for Clint was to figure out 
#	  how to work with a pointer to an array of list pointers. This
#	  included figuring out how to dereference them, initialize them,
#	  etc.  
#	  Clint hours - 4 hours
#	  Parker hours - 7 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: lesson11.o spellCheck.o
	g++ -o a.out lesson11.o spellCheck.o
	tar -cf lesson11.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson11.o     : the driver program
#      spellCheck.o   : the spell-check program and driver
##############################################################
lesson11.o: hash.h lesson11.cpp list.h
	g++ -c lesson11.cpp 

spellCheck.o: hash.h spellCheck.h spellCheck.cpp
	g++ -c spellCheck.cpp

