
/***********************************************************************
 * Program:
 *    Lesson 12, Maze
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef GRAPH_H
#define GRAPH_H

#include <cassert>
#include <iostream>
#include <string>
#include "vertex.h"
#include "set.h"
using namespace std;

/**********************************************************************
 * Graph
 ***********************************************************************/
//template <class T>
class Graph
{
  private:
     int vertices;       //VERTEX IS A NODE, number of nodes
     int currentSpot;    //next spot to add a string in the arcs list
     string verticeTitles[100]; //list of vertices/nodes to possibly get connected
     Vertex arcsList[100][100];//list of arcs/edges connecting the vertices/nodes
     
     //http://codereview.stackexchange.com/questions/20184/undirected-connected-and-weighted-graph-implementation

     //https://www.cs.bu.edu/teaching/c/graph/linked/
  public:
     //default constructor
     Graph()
     {
        currentSpot = 0;
     }
     //non-default constructor
     Graph(int numVertices)
     {
        vertices = numVertices;
        currentSpot = 0;
        arcsList[vertices][vertices];
        for (int x = 0; x < vertices; x++) //set each spot to 0 (unconnected)
        {
           for (int y = 0; y < vertices; y++)
           {
              arcsList[x][y] = 0;
           }
        }
     }
     //copy constructor
     Graph(const Graph & rhs)
     {
        this->vertices = rhs.vertices;
        this->currentSpot = rhs.currentSpot;
        for (int y = 0; y < vertices; y++)
        {
           this->verticeTitles[y] = rhs.verticeTitles[y];
        }
        for (int x = 0; x < vertices; x++)
        {
           for (int y = 0; y < vertices; y++)
           {
              this->arcsList[x][y] = rhs.arcsList[x][y];
           }
        }
     }
     // destructor : free everything that was previously use
     ~Graph()
     {}
     //Returns the number of vertices in the Graph.
     int size()
     {
        return vertices;
     }
     //This method takes two vertices as parameters. It returns true if there
     //is an edge connecting the first vertex to the second.
     template <class T>
     bool isEdge(T & V1, T & V2)//CVertex&, CVertex&
     {
        string XX = V1.getText();
        string YY = V2.getText();
        int xSpot = 0;
        int ySpot = 0;
        for (int V = 0; V < currentSpot; V ++)
        {
           xSpot = V;
           if (verticeTitles[V] == XX)
           {break;}
        }
        for (int V = 0; V < currentSpot; V ++)
        {
           ySpot = V;
           if (verticeTitles[V] == YY)
           {break;}
        }
        return (arcsList[xSpot][ySpot] == 1);
     }
     //This method takes on vertex as a parameter and returns the
     //set of vertices that share an edge with it
     template <class T>
     int findEdges(T & V1)
     {
        
     }
     //Two vertices are passed, representing the start vertex and the end
     //vertex. The return value will be a Vector of all the vertices on the
     //shortest path between the two.
     void findPath(LVertex& V1, LVertex& V2)
     {
     }

     //There are two overloaded add() functions,
     //the first taking two vertices/nodes representing the new edge,
     template <class T>
     void add(T & V1, T & V2);

     //the second ADD() taking a vertex and a set of vertices containing X... items to
     //connect to the first vertex           //"origional"
     template <class P, class H>             //template <class P>
     void add(P & V1, Set<H> & spot2);       //void add(P & V1, Set<Vertex>& spot2)

};


/**********************************************************************
 * ADD()   1
 *  -connects/points the first vertex to the vertex indicated in the
 *  -second parameter
 ***********************************************************************/
template <class T>
void Graph::add(T & V1, T & V2)
{
   string XX = V1.getText();
   string YY = V2.getText();
   //cout << "unchanged first = " << XX << endl;
   //cout << "unchanged second = " << YY << endl;
   //1) if no items are in the list, add both items
   if (currentSpot == 0)
   {
      verticeTitles[0] = XX;
      verticeTitles[1] = YY;
      currentSpot = 2;
   }
   //2) else, see if either needs to be added
   else
   {
      bool first = false;
      bool second = false;
      //look to see if the first one is in the array
      for (int V = 0; V < currentSpot; V ++)
      {
         if (verticeTitles[V] == XX)
         {first = true;}
      }
      //if not, add it into the list
      if (first == false)
      {
         verticeTitles[currentSpot] = XX;
         currentSpot = currentSpot + 1;
      }
      //look to see if the second one is in the array
      for (int V = 0; V < currentSpot; V ++)
      {
         if (verticeTitles[V] == YY)
         {second = true;}
      }
      //if not, add it into the list
      if (second == false)
      {
         verticeTitles[currentSpot] = YY;
         currentSpot = currentSpot + 1;
      }
      currentSpot = currentSpot + 1;
   }
   //3)now find the "X" and "Y" spots on the "Vertex arcsList[100][100]"
   //and mark them connected as 1
   int xSpot = 0;
   int ySpot = 0;
   //cout << "items to add: X " << XX << " and Y " <<YY << endl;
   for (int V = 0; V < currentSpot; V ++)
   {
      xSpot = V;
      if (verticeTitles[V] == XX)
      {break;}
   }
   for (int V = 0; V < currentSpot; V ++)
   {
      ySpot = V;
      if (verticeTitles[V] == YY)
      {break;}
   }
   /*cout << "total items on the list" << endl;
   for (int V = 0; V < currentSpot; V ++)
   {
      cout << verticeTitles[V];
   }
   cout << endl;
   cout << "xSpot = " << xSpot << endl;
   cout << "ySpot = " << ySpot << endl;
   */
   //4)here are the possible spots to mark (one or another)
   arcsList[xSpot][ySpot] = 1;  //connect (x,y) spot with 1
   //arcsList[ySpot][xSpot] = 1;  //connect (y,x) spot with 1
}

/**********************************************************************
 * ADD()   2
 *  -connects/points the first vertex to each one in the second parameters
 *  -set
 ***********************************************************************/
template <class P, class H>
void Graph::add(P & V1, Set<H> & spot2)
{
   vertices = 9;
   //cout << "size of container = " << spot2.size() << endl;
   SetIterator <H> it;
   SetIterator <P> it2;
   for (it = spot2.begin(); it != spot2.end(); ++it)
   {
      P V2;
      //cout << "\tvalue existing in the iterator = "
      //<< (*it).getText() << endl;
         //<<(V2 = *it) << endl;

                 //now call on the small add() to connect the first vertex
                 //to each item in the second vertex set
                 //P V2;
                 //string cause = "help";
                 //V2.setText(cause);       //really set it to the current iterator data
                 //add(V1, V2);
   }

   //POSSIBLE
   //for each item of the list, connect them to the current vertex
   //for (int V = 0; V < spot2.size(); V ++)
   //{
      //add(V1, V2);
   //}
}
#endif
