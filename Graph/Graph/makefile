###############################################################
# Program:
#     Lesson 12, Graph
#     Brother Sloan, CS235
# Author:
#     Clint Goodman
#     Parker Hubbard
# Summary:
#     This assignment uses arrays to save vertices/nodes and any
#     connections between any vertices/nodes of the array. This
#     info is later used to determine the shortest path from one
#     vertice to another (or path through the maze)
# Time:
#     Clint : 1.5 Hours
#     Parker: 16  Hours
# Difficulties:
#     1) The hardest part was first figuring out the starting format 
#     of the assignment (what variables, if the array should be
#     of vertex or string type...) 
#     2) then the main dead end reached was of the second add() function, 
#     where we had to call on a special vertex of a list of vertex's, 
#     but we could only reach data/functions of the common vertex,
#     not the special vertex origionally set into the array and sought
#     after.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: lesson12.o graph.o maze.o
	g++ -o a.out lesson12.o graph.o maze.o
	tar -cf lesson12.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson12.o     : the driver program
##############################################################
lesson12.o: graph.h vertex.h lesson12.cpp
	g++ -c lesson12.cpp 

graph.o: graph.h set.h vertex.h graph.cpp
	g++ -c graph.cpp

maze.o: maze.cpp maze.h vertex.h graph.h
	g++ -c maze.cpp
