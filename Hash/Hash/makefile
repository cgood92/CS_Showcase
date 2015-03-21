###############################################################
# Program:
#     Lesson 11, Hash
#     Brother Helfrich, CS235
# Author:
#     <your name here>
# Summary:
#     <put a description here>
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

