###############################################################
# Program:
#     Lesson 08, Binary Search Tree
#     Brother Helfrich, CS265
# Author:
#     Clint Goodman and Parker Hubbard
# Summary:
#     <put a description here>
# Time:
#     Clint  9 Hours
#     Parker 6.5 Hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: lesson08.o
	g++ -o a.out lesson08.o 
	tar -cf lesson08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson08.o     : the driver program
##############################################################
lesson08.o: bnode.h bst.h stack.h lesson08.cpp sortBinary.h
	g++ -c lesson08.cpp

