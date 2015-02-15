###############################################################
# Program:
#     Lesson 05, NODE
#     Brother Helfrich, CS235
# Author:
#     Clint Goodman and Parker Hubbard
# Summary:
#     Clint Gooodman - 7 hours
#     Parker Hubbard - 9.5 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: node.h lesson05.o 
	g++ -o a.out lesson05.o 
	tar -cf lesson05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson05.o      : the driver program
#      <anything else?>
##############################################################
lesson05.o: node.h lesson05.cpp sortInsertion.h
	g++ -c lesson05.cpp
