###############################################################
# Program:
#     Lesson 04, DEQUE
#     Brother Helfrich, CS235
# Author:
#     Clint Goodman
#     Parker Hubbard
# Summary:
#     <put a description here>
# Time:
#     Clint:  X hours so far
#     Parker: 1 hours so far
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h lesson04.o nowServing.o
	g++ -o a.out lesson04.o nowServing.o
	tar -cf lesson04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson04.o     : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
lesson04.o: deque.h lesson04.cpp
	g++ -c lesson04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp
