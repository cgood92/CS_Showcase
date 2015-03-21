###############################################################
# Program:
#     Lesson 10, Sorts
#     Brother Helfrich, CS265
# Author:
#     <your name here>
# Summary:
#     <put a description here>
# Time:
#     <how long did it take to complete this program>?
###############################################################

##############################################################
# The main rule
##############################################################
a.out: lesson10.o
	g++ -o a.out lesson10.o 
	tar -cf lesson10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson10.o     : the driver program
##############################################################
lesson10.o: bnode.h bst.h stack.h lesson10.cpp sortValue.h \
		sortBinary.h sortInsertion.h sortHeap.h sortBubble.h \
		sortSelection.h sortMerge.h sortQuick.h
	g++ -c lesson10.cpp

