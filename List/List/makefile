###############################################################
# Program:
#     Lesson 06, LIST
#     Brother Helfrich, CS235
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
a.out: list.h lesson06.o fibonacci.o
	g++ -o a.out lesson06.o fibonacci.o
	tar -cf lesson06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson06.o     : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
lesson06.o: list.h lesson06.cpp
	g++ -c lesson06.cpp

fibonacci.o: fibonacci.h fibonacci.cpp list.h
	g++ -c fibonacci.cpp

