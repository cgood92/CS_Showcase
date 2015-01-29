###############################################################
# Program:
#     Lesson 03, QUEUE
#     Brother Helfrich, CS235
# Author:
#     Clint
#     Parker 
# Summary:
#     <put a description here>
# Time:
#     Clint:  XXX hours so far
#     Parker: 4.0 hours so far
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h lesson03.o dollars.o stock.o
	g++ -o a.out lesson03.o dollars.o stock.o
	tar -cf lesson03.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp

##############################################################
# The individual components
#      lesson03.o     : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
##############################################################
lesson03.o: queue.h lesson03.cpp
	g++ -c lesson03.cpp

dollars.o: dollars.h dollars.cpp
	g++ -c dollars.cpp

stock.o: stock.h stock.cpp queue.h
	g++ -c stock.cpp
