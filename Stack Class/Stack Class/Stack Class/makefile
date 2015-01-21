###############################################################
# Program:
#     Lesson 02, STACK
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
a.out: stack.h lesson02.o infix.o 
	g++ -o a.out lesson02.o infix.o 
	tar -cf lesson02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson02.o     : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
lesson02.o: stack.h infix.h lesson02.cpp
	g++ -c lesson02.cpp

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp

