/***********************************************************************
 * Program:
 *    Lesson 7, Binary Tree
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef BNODE_H
#define BNODE_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;


/**********************************************************************
 * Binary Node
 ***********************************************************************/
template <class T>
class BinaryNode
{
  public:   
     T data;
	 bool isRed;
     BinaryNode <T> * pRight;
     BinaryNode <T> * pLeft; 
     BinaryNode <T> * pParent; 
     //default constructor
	 BinaryNode() : pRight(NULL), pLeft(NULL), pParent(NULL), isRed(true)
     {
     }
     //non-default constructor
	 BinaryNode(T data) : pRight(NULL), pLeft(NULL), pParent(NULL), data(data), isRed(true)
     {
     }
     // copy constructor
     BinaryNode(const BinaryNode<T> & rhs)
     {
     }
     // destructor : free everything that was previously used
     ~BinaryNode()
     {
     }
     BinaryNode <T> * addLeft(BinaryNode <T> * pBNode)
     {
        this->pLeft = pBNode;
        this->pLeft->pParent = this;
        return this;
     }
     BinaryNode <T> * addLeft(T  data)
     {
        BinaryNode<T> * newNode = new BinaryNode<T>(data);
        newNode->pParent = this;
        this->pLeft = newNode;
        return this;
     }
     BinaryNode <T> * addRight(BinaryNode <T> * pBNode)
     {
        this->pRight = pBNode;
        this->pRight->pParent = this;
        return this;
     }
     BinaryNode <T> * addRight(T  data)
     {
        BinaryNode<T> * newNode = new BinaryNode <T>(data);
        this->pRight = newNode;
        newNode->pParent = this;
        return this;
     }
	 int findDepth() const;
	 void verifyRedBlack(int depth) const;
	 void verifyBTree() const;
};

template <class T>
void deleteBinaryTree(BinaryNode <T> * pBNode)
{
   //node pointer to main root of the binary tree
   BinaryNode <T> * root = pBNode;
   //node pointer "pLeft" points to "pBNode"s "pLeft"
   BinaryNode <T> * pLeft = pBNode->pLeft;
   //same for "pRight"
   BinaryNode <T> * pRight = pBNode->pRight;

   //int time = 0;
   bool leftLast = true;
   //do until the left and right of the "root" both equal NULL  
   do
   {
      //reset pointer to thw top root
      BinaryNode <T> * current = pBNode;
      int restart = false;
      do
      {
         //check left side, and go down that side
         if (current->pLeft != NULL)
         {
            current = current->pLeft;
            leftLast = true;
            //cout << "navLeft ";
         }
         //check right side, and go down that side
         else if (current->pRight != NULL)
         {
            current = current->pRight;
            leftLast = false;
            //cout << "navRight ";
         }
         //if both left and right equal NULL, remove and start back at the top
         else if ((current->pRight == NULL) && (current->pLeft == NULL))
         {
            //if we moved down "left" last
            if (leftLast == true)
            {
               current->pParent->pLeft = NULL;
               current->pParent = NULL;
               //cout << "deadLeft ";
            }
            //if we moved down "right" last
            else
            {
               current->pParent->pRight = NULL;
               current->pParent = NULL;
               //cout << "deadRight ";
            }         
            restart = true;
            //time = time +1;
            delete current;
            //begin back at the "root" (topmost node)
            break;
         }
      }while (restart != true);
   }
   while ((root->pLeft != NULL) || (root->pRight != NULL));
   
   //last we delete the foundation root of the tree
   delete root;
}

/*****************************************
* DISPLAY
* Display the contents of a binary tree
****************************************/
template <class T>
ostream & operator << (ostream & out, BinaryNode<T> * pTree)
{
   displayInorder(pTree);
   return out;
}

/*****************************************
* DISPLAY
* Display the contents of a binary tree
****************************************/
template <class T>
void displayInorder (BinaryNode<T> * pTree)
{
   BinaryNode <T> * pLeft = pTree->pLeft;
   BinaryNode <T> * pRight = pTree->pRight;
   if (pLeft)
   {
      displayInorder(pLeft);
   }
   cout << pTree->data << " ";
   if (pRight)
   {
      displayInorder(pRight);
   }
}

// you might want to put these methods into your BinaryNode class
// to help you debug your red-black balancing code

/****************************************************
 * BINARY NODE :: FIND DEPTH
 * Find the depth of the black nodes. This is useful for
 * verifying that a given red-black tree is valid
 ****************************************************/
template <class T>
int BinaryNode <T> :: findDepth() const
{
   // if there are no children, the depth is ourselves
   if (pRight == NULL && pLeft == NULL)
      return (isRed ? 0 : 1);

   // if there is a right child, go that way
   if (pRight != NULL)
      return (isRed ? 0 : 1) + pRight->findDepth();
   else
      return (isRed ? 0 : 1) + pLeft->findDepth();
}

/****************************************************
 * BINARY NODE :: VERIFY RED BLACK
 * Do all four red-black rules work here?
 ***************************************************/
template <class T>
void BinaryNode <T> :: verifyRedBlack(int depth) const
{
   depth -= (isRed == false) ? 1 : 0;

   // Rule a) Every node is either red or black
   assert(isRed == true || isRed == false); // this feels silly

   // Rule b) The root is black
   if (pParent == NULL)
      assert(isRed == false);

   // Rule c) Red nodes have black children
   if (isRed == true)
   {
      if (pLeft != NULL)
         assert(pLeft->isRed == false);
      if (pRight != NULL)
         assert(pRight->isRed == false);
   }

   // Rule d) Every path from a leaf to the root has the same # of black nodes
   if (pLeft == NULL && pRight && NULL)
      assert(depth == 0);
   if (pLeft != NULL)
      pLeft->verifyRedBlack(depth);
   if (pRight != NULL)
      pRight->verifyRedBlack(depth);
}

/******************************************************
 * VERIFY B TREE
 * Verify that the tree is correctly formed
 ******************************************************/
template <class T>
void BinaryNode <T> :: verifyBTree() const
{
   // check parent
   if (pParent)
      assert(pParent->pLeft == this || pParent->pRight == this);

   // check left
   if (pLeft)
   {
      assert(pLeft->data <= data);
      assert(pLeft->pParent == this);
      pLeft->verifyBTree();
   }

   // check right
   if (pRight)
   {
      assert(pRight->data >= data);
      assert(pRight->pParent == this);
      pRight->verifyBTree();
   }
}


#endif
