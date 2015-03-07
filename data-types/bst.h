#ifndef BST_H
#define BST_H

#include <cassert>
#include <iostream>
#include <string>
#include "bnode.h"
#include <stack>
using namespace std;

template <class T>
class BSTIterator;

/**********************************************************************
 * (BST) Binary Node
 ***********************************************************************/
template <class T>
class BST
{
  private:
     BinaryNode <T> * masterTree;
  public:
     BST(): masterTree(NULL)
     {
     } 
     ~BST() {}
     BST(const BST & rhs)
     {
        this->masterTree = new BinaryNode <T>();
        BinaryNode <T> * currentNodeRHS = rhs.masterTree;
        BinaryNode <T> * currentNodeLHS = this->masterTree;
        this->masterTree->data = rhs.masterTree->data;
        deepCopy(currentNodeLHS, currentNodeRHS);
     }
     void deepCopy(BinaryNode <T> * currentNodeLHS,
                   BinaryNode <T> * currentNodeRHS)
     {
        if (currentNodeRHS->pLeft)
        {
           currentNodeLHS->addLeft(currentNodeRHS->pLeft);
           deepCopy(currentNodeLHS->pLeft, currentNodeRHS->pLeft);
        }
        if (currentNodeRHS->pRight)
        {
           currentNodeLHS->addRight(currentNodeRHS->pRight);
           deepCopy(currentNodeLHS->pRight, currentNodeRHS->pRight);
        }
     }
     bool empty()
     {
        return (masterTree->data == NULL);
     }
     void insert(T data);
     void insert(T data, BinaryNode <T> * currentNode);
     void clear()
     {
        void deleteBinaryTree(BinaryNode <T> * masterTree);
     }
     BSTIterator <T> begin()
     {
        BSTIterator <T> myIt;
        myIt = BSTIterator <T>(this->masterTree);
        return myIt;
     }
     BSTIterator <T> end()
     {
        BSTIterator <T> myIt;
        myIt = BSTIterator <T>(this->masterTree);
        myIt.stackOfNodes = NULL;
        return myIt;
     }
     BSTIterator <T> rbegin()
     {
        BSTIterator <T> myIt;
        myIt = BSTIterator <T>(this->masterTree);
        myIt.reverse();
        return myIt;
     }
     BSTIterator <T> rend()
     {
        BSTIterator <T> myIt;
        myIt = BSTIterator <T>(this->masterTree);
        myIt.stackOfNodes = NULL;
        return myIt;
     }

     void noChild(BinaryNode <T> * currentNode)
     {
        if (currentNode->data == currentNode->pParent->pLeft->data)
        {
           currentNode->pParent->pLeft = NULL;
        }
        else
        {
           currentNode->pParent->pRight = NULL;
        }
		currentNode->pParent = NULL;
		currentNode->pRight = NULL;
		currentNode->pLeft = NULL;
		delete currentNode;
     }
     void oneChild(BinaryNode <T> * currentNode)
     {
		 if (currentNode == currentNode->pParent->pLeft)
		 {
			 if (currentNode->pLeft)
			 {
				 currentNode->pLeft->pParent = currentNode->pParent;
				 currentNode->pParent->pLeft = currentNode->pLeft;
			 }
			 else
			 {
				 currentNode->pRight->pParent = currentNode->pParent;
				 currentNode->pParent->pLeft = currentNode->pRight;
			 }
		 }
		 else
		 {
			 if (currentNode->pLeft)
			 {
				 currentNode->pLeft->pParent = currentNode->pParent;
				 currentNode->pParent->pRight = currentNode->pLeft;
			 }
			 {
				 currentNode->pRight->pParent = currentNode->pParent;
				 currentNode->pParent->pRight = currentNode->pRight;
			 }
		 }
		 currentNode->pParent = NULL;
		 currentNode->pRight = NULL;
		 currentNode->pLeft = NULL;
		 delete currentNode;

     }
	 void twoChild(BinaryNode <T> * nodeToDelete, BinaryNode <T> * currentNode)
     {
		 if (currentNode->pLeft)
		 {
			 twoChild(nodeToDelete, currentNode->pLeft);
		 }
		 else
		 {
			 nodeToDelete->data = currentNode->data;
			 remove(currentNode);
		 }
     }
     
	 void remove(BSTIterator <T> myIt)
	 {
		 BinaryNode <T> * currentNode = myIt.stackOfNodes->top();
		 remove(currentNode);
	 }

	 void remove(BinaryNode <T> * currentNode)
	 {
		 //1) if the nodes a leaf, having no children
		 if (!currentNode->pLeft && !currentNode->pRight)
		 {
			 noChild(currentNode);
		 }
		 //2) if the node has 2 children
		 else if (currentNode->pLeft && currentNode->pRight)
		 {
			 twoChild(currentNode, currentNode->pRight);
		 }
		 //3) if the node has 1 child
		 else
		 {
			 oneChild(currentNode);
		 }
	 }

	 BSTIterator <T> find(T data)
	 {
		 BSTIterator <T> it = BSTIterator <T>(this->masterTree);
		 for (; it != this->end(); ++it)
			 if (*it == data)
			 {
				 return it;
			 }
		 return this->end();
	 }
};

template <class T>
void BST<T>::insert(T data)
{
   if (!this->masterTree)
   {
      this->masterTree = new BinaryNode <T>();
      this->masterTree->data = data;
      return;
   }
   else
   {
      insert(data, this->masterTree);
   }
}

template <class T>
void BST<T>::insert(T data, BinaryNode <T> * currentNode)
{
   if (data < currentNode->data)
   {
      if (!currentNode->pLeft)
      {
         currentNode->addLeft(data);
      }
      else
      {
         insert(data, currentNode->pLeft);
      }
   }
   else if (data >= currentNode->data)
   {
      if (!currentNode->pRight)
      {
         currentNode->addRight(data);
      }
      else
      {
         insert(data, currentNode->pRight);
      }
   }
}

template <class T>
class BSTIterator
{
public: 
	stack < BinaryNode <T> * > * stackOfNodes;
  private:
     BinaryNode <T> * masterTree;
     void fillStack(BinaryNode <T> * pTree)
     {
        BinaryNode <T> * pLeft = pTree->pLeft;
        BinaryNode <T> * pRight = pTree->pRight;
        if (pRight)
        {
           fillStack(pRight);
        }
        stackOfNodes->push(pTree);
        if (pLeft)
        {
           fillStack(pLeft);
        }
     }
     void reverse()
     {
        stack < BinaryNode <T> * > * stackOfNodesNew = new stack < BinaryNode <T> * >();
        while (stackOfNodes->size() > 0)
        {
           stackOfNodesNew->push(stackOfNodes->top());
           stackOfNodes->pop();
        }
        stackOfNodes = stackOfNodesNew;
     }
  public:
     BSTIterator() : masterTree(NULL), stackOfNodes(NULL)
     {
     }
     BSTIterator(BinaryNode <T> * masterTree) : masterTree(NULL),
        stackOfNodes(NULL)
     {
        if (masterTree)
        {
           this->stackOfNodes = new stack < BinaryNode <T> * >();
           this->masterTree = masterTree;
           if (masterTree)
           {
              fillStack(masterTree);
           }
        }
     }
     BSTIterator(const BSTIterator & rhs) : masterTree(NULL),
        stackOfNodes(NULL)
     {
        *this = rhs;
     }
     BSTIterator & operator = (const BSTIterator & rhs)
     {
        this->masterTree = rhs.masterTree;
        this->stackOfNodes = rhs.stackOfNodes;
        return *this;
     }
     bool operator != (const BSTIterator & rhs) const
     {
        return rhs.stackOfNodes != this->stackOfNodes;
     }
     bool operator == (const BSTIterator & rhs) const
     {
        return rhs.stackOfNodes == this->stackOfNodes;
     }
     T & operator * ()
     {
        return this->stackOfNodes->top()->data;
     }
     BSTIterator <T> & operator -- ()
     {
        if (this->stackOfNodes->size() > 1)
        {
           this->stackOfNodes->pop();
        }
        else
        {
           this->stackOfNodes = NULL;
        }
        return *this;
     }
     BSTIterator <T> operator--(int prefix)
     {
        BSTIterator tmp(*this);
        if (this->stackOfNodes->size() > 0)
        {
           this->stackOfNodes->pop();
        }
        else
        {
           this->stackOfNodes = NULL;
        }
        return tmp;
     }
     BSTIterator <T> & operator ++ ()
     {
        if (this->stackOfNodes->size() > 1)
        {
           this->stackOfNodes->pop();
        }
        else
        {
           this->stackOfNodes = NULL;
        }
        return *this;
     }
     BSTIterator <T> operator++(int postfix)
     {
        BSTIterator tmp(*this);
        if (this->stackOfNodes->size() > 0)
        {
           this->stackOfNodes->pop();
        }
        else
        {
           this->stackOfNodes = NULL;
        }
        return tmp;
     }
     template <class TT>
     friend class BST;
};


#endif
