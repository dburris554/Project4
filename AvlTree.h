/*
 * AvlTree.h
 *
 *  Created on: Apr 10, 2018
 *      Author: david
 */

#include "TreeNode.h"
#include "ResizeableArray.h"

#ifndef AVLTREE_H_
#define AVLTREE_H_

using namespace std;

template<typename TheType>
class AvlTree {

public:
	AvlTree();
	virtual ~AvlTree();
	void addItem(TheType* myObject, int theKey); //adds objects to tree
	TreeNode<TheType>* getRootNode();
	TreeNode<TheType>* getTempNode(); //tempNode allows simple coding for find and recursive calls
	void setTempNode(TreeNode<TheType>* myTempNode);
	void removeItem(TheType* myobject, int theKey); //use tempNode to call updateTree after removing item
	TheType* findData(int key); //retrieve data from the tree with an Eclipse ID
	TreeNode<TheType>* findNode(int key);
	void printPreOrder();
	void printInOrder(); //Prints are mainly for debugging
	void printPostOrder();
	void copyToArray(ResizeableArray<TheType>& myEclipses); //copy data in-order to Resizeable array

private:
	void updateTree(TreeNode<TheType>* insertedNode); //starts at inserted/deleted location, updates balanceFactors and checks for rotations back to rootNode
	void leftHeavyRotate(TreeNode<TheType>* nodeA); //rotation when bF are 1 -> 2
	void leftInnerRotate(TreeNode<TheType>* nodeA); //rotation when bF are -1 -> 2
	void rightHeavyRotate(TreeNode<TheType>* nodeA); //rotation when bF are -1 -> -2
	void rightInnerRotate(TreeNode<TheType>* nodeA); //rotation when bF are 1 -> -2
	void lHRemovalRotate(TreeNode<TheType>* nodeA); //rotation when bF are 0 -> -2
	void rHRemovalRotate(TreeNode<TheType>* nodeA); //rotation when bF are 0 -> 2
	void recurseAdd(TreeNode<TheType>* curNode,TreeNode<TheType>* insertNode, TheType* myobject, int &theKey); //use to simplify addItem recursion
	void printPreOrder(TreeNode<TheType>* curNode); //recurse print for pre-order
	void printInOrder(TreeNode<TheType>* curNode); //recurse print in-order
	void printPostOrder(TreeNode<TheType>* curNode); //recurse print post-order
	void copyToArray(ResizeableArray<TheType>& myEclipses, TreeNode<TheType>* firstNode); //see public method comment
	void find(TreeNode<TheType>* curNode, int key); //finds a node matching the key and assigns it to tempNode
	int computeBalanceFactor(TreeNode<TheType>* myNode); //uses left-max-depth and right-max-depth in real time
	void computeBalanceFactor(TreeNode<TheType>* myNode, int &branchDepth); //recurse based on bF
	TreeNode<TheType>* rootNode; //holds the root of the AvlTree
	TreeNode<TheType>* tempNode; //holds nodes during find and recursive calls
};

template<typename TheType>
AvlTree<TheType>::AvlTree()
{
	rootNode = 0;
	tempNode = 0;;
}

template<typename TheType>
AvlTree<TheType>::~AvlTree() {}

template<typename TheType>
void AvlTree<TheType>::addItem(TheType* myObject, int theKey)
{
	//If no rootNode, add as rootNode. Else, add as regular node
	if (rootNode == 0)
	{
		rootNode = new TreeNode<TheType>(myObject,theKey);
	}
	else //Find insertion location recursively and insert as non-root node
	{
		TreeNode<TheType>* curNode = rootNode; //curNode will travel down the tree to find insertion location
		TreeNode<TheType>* insertNode = new TreeNode<TheType>(myObject,theKey); //insertNode will travel down the tree so balanceTree can be called

		if (theKey > curNode->getKey()) //if this occurs, recurse right
		{
			if (curNode->getRightChild() == 0) //insert here if right child is 0
			{
				curNode->setRightChild(new TreeNode<TheType>(curNode,myObject,theKey)); //don't use insertNode here to avoid extra line
				curNode->setBalanceFactor(computeBalanceFactor(curNode)); //guaranteed no rotations will happen here
				return;
			}

			recurseAdd(curNode->getRightChild(),insertNode,myObject,theKey);
			//After right recursion return, update tree's bF's and rotations
			updateTree(insertNode);
		}
		else //otherwise, myEclipse ID should be < curNode's key, so recurse left
		{
			if (curNode->getLeftChild() == 0) //insert here if left child is 0
			{
				curNode->setLeftChild(new TreeNode<TheType>(curNode,myObject,theKey)); //Don't use insertNode until recurseAdd
				curNode->setBalanceFactor(computeBalanceFactor(curNode)); //guaranteed no rotation will happen here
				return;
			}

			recurseAdd(curNode->getLeftChild(),insertNode,myObject,theKey);
			updateTree(insertNode);
		}
	}
}

template<typename TheType>
void AvlTree<TheType>::recurseAdd(TreeNode<TheType>* curNode, TreeNode<TheType>* insertNode, TheType* myObject, int &theKey)
{
	if (theKey > curNode->getKey()) //if this occurs, recurse right
	{
		if (curNode->getRightChild() == 0) //insert here if right child is 0
		{
			curNode->setRightChild(insertNode); //when assigning insertNode, need to assign parent relation
			insertNode->setParent(curNode);
			return;
		}
		recurseAdd(curNode->getRightChild(),insertNode,myObject,theKey);
		return;
	}
	else //otherwise, myEclipse ID should be < curNode's key, so recurse left
	{
		if (curNode->getLeftChild() == 0) //insert here if left child is 0
		{
			curNode->setLeftChild(insertNode);
			insertNode->setParent(curNode);
			return;
		}
		recurseAdd(curNode->getLeftChild(),insertNode,myObject,theKey);
		return;
	}
}

template<typename TheType>
TreeNode<TheType>* AvlTree<TheType>::getRootNode()
{
	return rootNode;
}

template<typename TheType>
TreeNode<TheType>* AvlTree<TheType>::getTempNode()
{
	return tempNode;
}

template<typename TheType>
void AvlTree<TheType>::setTempNode(TreeNode<TheType>* myFoundNode)
{
	tempNode = myFoundNode;
}

template<typename TheType>
void AvlTree<TheType>::removeItem(TheType* myObject, int theKey)
{
	//3 removal cases: leaf node, node with 1 child, node with 2 children

	TreeNode<TheType>* delNode = findNode(theKey);
	if (delNode->getKey() == 0) //If an invalid node, cerr and return
	{
		cerr << "Eclipse catalog number " << theKey << " not found." << endl;
		return;
	}

	//Leaf Node case
	if (delNode->getLeftChild() == 0 && delNode->getRightChild() == 0) //delNode is a leaf node
	{
		if (delNode->getParent() == 0) //delnode is the root
		{
			delNode = 0;
			rootNode = 0;
		}
		else //delnode has a parent
		{
			bool isLeftChild = false;
			if (delNode->getParent()->getLeftChild() != 0) //only compare with left child if it exists
			{
				isLeftChild = delNode->getKey() == delNode->getParent()->getLeftChild()->getKey();
			}

			if (isLeftChild) //delNode is a left child
			{
				delNode->getParent()->setLeftChild(0);
				tempNode = delNode->getParent();
				delNode = 0;
				updateTree(tempNode);
			}
			else //otherwise, delnode is a right child
			{
				delNode->getParent()->setRightChild(0);
				tempNode = delNode->getParent();
				delNode = 0;
				updateTree(tempNode);
			}
		}
	}

	//double child case
	else if (delNode->getLeftChild() != 0 && delNode->getRightChild() != 0) //delNode has two children
	{
		TreeNode<TheType>* succNode = delNode->getRightChild(); //start the search for successor at delNode's right child and recurse left
		while (succNode->getLeftChild() != 0)
		{
			succNode = succNode->getLeftChild();
		}

		delNode->setKey(succNode->getKey());
		delNode->setData(succNode->getData()); //assign delNode with successor data

		bool isLeftChild = (succNode->getKey() == succNode->getParent()->getLeftChild()->getKey());
		//If succNode is a leaf node, delete leaf node and update tree
		if (succNode->getRightChild() == 0)
		{
			if (isLeftChild)
			{
				succNode->getParent()->setLeftChild(0);
			}
			else
			{
				succNode->getParent()->setRightChild(0);
			}
			tempNode = succNode->getParent();
			succNode = 0;
			updateTree(tempNode);
		}
		else //otherwise delete succNode as a has-right-child-and-parent case
		{
			tempNode = succNode->getParent();

			if (isLeftChild)
			{
				tempNode->setLeftChild(succNode->getRightChild());
				tempNode->getLeftChild()->setParent(tempNode);
			}
			else
			{
				tempNode->setRightChild(succNode->getRightChild());
				tempNode->getRightChild()->setParent(tempNode);
				//Parent to succNode-child relations have been formed, now delete succNode
				succNode = 0;
				updateTree(tempNode);
			}
		}

	}

	//single child case, only check if the child is left or right and if delNode has a parent
	else
	{
		bool hasLeftChild = (delNode->getLeftChild() != 0);

		if (delNode->getParent() == 0) //delNode is root
		{
			if (hasLeftChild)
			{
				rootNode = delNode->getLeftChild();
				rootNode->setParent(0);
				delNode = 0;
				updateTree(rootNode);
			}
			else
			{
				rootNode = delNode->getRightChild();
				rootNode->setParent(0);
				delNode = 0;
				updateTree(rootNode);
			}
		}
		else //delNode has a parent
		{
			bool isLeftChild = false;
			if (delNode->getParent()->getLeftChild() != 0) //only compare with left child if it exists
			{
				isLeftChild = delNode->getKey() == delNode->getParent()->getLeftChild()->getKey();
			}
			tempNode = delNode->getParent();

			if (isLeftChild) //if delNode is a left child...
			{
				if (hasLeftChild)
				{
					tempNode->setLeftChild(delNode->getLeftChild());
					tempNode->getLeftChild()->setParent(tempNode);
				}
				else
				{
					tempNode->setLeftChild(delNode->getRightChild());
					tempNode->getLeftChild()->setParent(tempNode);
				}
			}
			else //else delNode is a right child
			{
				if (hasLeftChild)
				{
					tempNode->setRightChild(delNode->getLeftChild());
					tempNode->getRightChild()->setParent(tempNode);
				}
				else
				{
					tempNode->setRightChild(delNode->getRightChild());
					tempNode->getRightChild()->setParent(tempNode);
				}
			}
			//Parent to delNode-child relations have been formed, now delete delNode
			delNode = 0;
			updateTree(tempNode);
		}
	}
}

template<typename TheType>
TheType* AvlTree<TheType>::findData(int key) //will return an invalid Eclipse if not found
{
	TreeNode<TheType>* curNode = rootNode;
	find(curNode,key);
	return tempNode->getData();
}

template<typename TheType>
TreeNode<TheType>* AvlTree<TheType>::findNode(int key) //will return an invalid TreeNode if not found
{
	TreeNode<TheType>* curNode = rootNode;
	find(curNode,key);
	return tempNode;
}

template<typename TheType>
void AvlTree<TheType>::find(TreeNode<TheType>* curNode, int key)
{
	if (rootNode == 0) //if tree is empty, don't look
	{
		tempNode = new TreeNode<TheType>();
		return;
	}
	if (curNode->getKey() < key) //first check to recurse right
	{
		if (curNode->getRightChild() != 0) //then make sure the right child exists
		{
			find(curNode->getRightChild(),key);
			return;
		}
	}
	else if (curNode->getKey() > key)//next check to recurse left
	{
		if (curNode->getLeftChild() != 0) //then check to see if left child exists
		{
			find(curNode->getLeftChild(),key);
			return;
		}
	}

	if (curNode->getKey() == key) //check if curNode is a match
	{
		tempNode = curNode;
	}
	else
	{
		tempNode = new TreeNode<TheType>();
	}
	return;
}

template<typename TheType>
int AvlTree<TheType>::computeBalanceFactor(TreeNode<TheType>* myNode) //Use this to calculate a new balanceFactor
{
	int leftHeight = 0;
	int rightHeight = 0;

	if (myNode->getLeftChild() != 0)
	{
		computeBalanceFactor(myNode->getLeftChild(),++leftHeight);
	}
	if (myNode->getRightChild() != 0)
	{
		computeBalanceFactor(myNode->getRightChild(),++rightHeight);
	}
	return (leftHeight - rightHeight);
}

template<typename TheType>
void AvlTree<TheType>::computeBalanceFactor(TreeNode<TheType>* myNode, int &branchDepth) //search left or right based on bF
{
	if (myNode->getLeftChild() != 0 || myNode->getRightChild() != 0) //keep recursing as long as there is a valid child
	{
		if (myNode->getBalanceFactor() > 0) //If bF is positive, look left first
		{
			if (myNode->getLeftChild() != 0)
			{
				branchDepth++;
				computeBalanceFactor(myNode->getLeftChild(),branchDepth);
				return;
			}

			if (myNode->getRightChild() != 0)
			{
				branchDepth++;
				computeBalanceFactor(myNode->getRightChild(),branchDepth);
				return;
			}
		}
		else //otherwise, bF should be negative or 0, so look right first
		{
			if (myNode->getRightChild() != 0)
			{
				branchDepth++;
				computeBalanceFactor(myNode->getRightChild(),branchDepth);
				return;
			}

			if (myNode->getLeftChild() != 0)
			{
				branchDepth++;
				computeBalanceFactor(myNode->getLeftChild(),branchDepth);
				return;
			}
		}
		return;
	}
}

template<typename TheType>
void AvlTree<TheType>::printPreOrder()
{
	printPreOrder(rootNode);
}

template<typename TheType>
void AvlTree<TheType>::printPreOrder(TreeNode<TheType>* curNode)
{
	if (rootNode != 0)
	{
		cout << *(curNode->getData());

		if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
		{
			printPreOrder(curNode->getLeftChild());
		}

		if (curNode->getRightChild() != 0) //only check right subtrees if not 0
		{
			printPreOrder(curNode->getRightChild());
		}
	}
}

template<typename TheType>
void AvlTree<TheType>::printInOrder()
{
	printInOrder(rootNode);
}

template<typename TheType>
void AvlTree<TheType>::printInOrder(TreeNode<TheType>* curNode)
{
	if (rootNode != 0)
	{
		if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
		{
			printInOrder(curNode->getLeftChild());
		}

		cout << *(curNode->getData());

		if (curNode->getRightChild() != 0) //only check right subtrees if not 0
		{
			printInOrder(curNode->getRightChild());
		}
	}
}

template<typename TheType>
void AvlTree<TheType>::printPostOrder()
{
	printPostOrder(rootNode);
}

template<typename TheType>
void AvlTree<TheType>::printPostOrder(TreeNode<TheType>* curNode)
{
	if (rootNode != 0)
	{
		if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
		{
			printPostOrder(curNode->getLeftChild());
		}

		if (curNode->getRightChild() != 0) //only check right subtrees if not 0
		{
			printPostOrder(curNode->getRightChild());
		}

		cout << *(curNode->getData());
	}
}

template<typename TheType>
void AvlTree<TheType>::copyToArray(ResizeableArray<TheType>& myEclipses)
{
	if (rootNode != 0) //only copy if tree is populated
	{
		copyToArray(myEclipses,rootNode);
	}
	else //otherwise, tree is empty, so clear myEclipses
	{
		myEclipses.clear();
	}
}

template<typename TheType>
void AvlTree<TheType>::copyToArray(ResizeableArray<TheType>& myEclipses, TreeNode<TheType>* firstNode)
{
	if (firstNode->getLeftChild() != 0) //only check left subtrees if not 0
	{
		copyToArray(myEclipses,firstNode->getLeftChild());
	}

	myEclipses.Add(*(firstNode->getData()));

	if (firstNode->getRightChild() != 0) //only check right subtrees if not 0
	{
		copyToArray(myEclipses,firstNode->getRightChild());
	}
}

template<typename TheType>
void AvlTree<TheType>::updateTree(TreeNode<TheType>* insertedNode) //start from insertion, travel up the parents to check for rotation cases
{
	insertedNode->setBalanceFactor(computeBalanceFactor(insertedNode));
	TreeNode<TheType>* curNode = new TreeNode<TheType>(*insertedNode); //we will start at the node that was added/removed
	bool hasLeftChild = (insertedNode->getLeftChild() != 0);

	if (abs(curNode->getBalanceFactor()) == 2 && (insertedNode->getLeftChild() != 0 || insertedNode->getRightChild() != 0))
	//special case during removal @ delNode's parent where we should start at sibling
	{
		if (hasLeftChild)
		{
			tempNode = insertedNode->getLeftChild();
			updateTree(tempNode);
			return;
		}
		else //otherwise, insertedNode has a right child
		{
			tempNode = insertedNode->getRightChild();
			updateTree(tempNode);
			return;
		}
	}	//above will restart at the node that will catch the rotation

	while (curNode->getParent() != 0) //continue updating and checking rotations until you reach the head node
	{
		//tempNode will be child and recurse up to the next parent
		tempNode = curNode;
		curNode = curNode->getParent();

		curNode->setBalanceFactor(computeBalanceFactor(curNode)); //update parent's bF before checking for rotation

		//Test for Left-Heavy rotation
		if (tempNode->getBalanceFactor() == 1 && curNode->getBalanceFactor() == 2)
		{
			leftHeavyRotate(curNode); //rotate on sub-head node, return hasRotated
		}
		//Test for Left-Inner rotation
		else if (tempNode->getBalanceFactor() == -1 && curNode->getBalanceFactor() == 2)
		{
			leftInnerRotate(curNode); //rotate on sub-head node, return hasRotated
		}
		//Test for Right-Heavy rotation
		else if (tempNode->getBalanceFactor() == -1 && curNode->getBalanceFactor() == -2)
		{
			rightHeavyRotate(curNode); //rotate on sub-head node, return hasRotated
		}
		//Test for Right-Inner rotation
		else if (tempNode->getBalanceFactor() == 1 && curNode->getBalanceFactor() == -2)
		{
			rightInnerRotate(curNode); //rotate on sub-head node, return hasRotated
		}
		//Test for Left-Heavy Removal rotation
		else if (tempNode->getBalanceFactor() == 0 && curNode->getBalanceFactor() == -2)
		{
			lHRemovalRotate(curNode); //rotate on sub-head node, return hasRotated
		}
		//Test for Right-Heavy Removal rotation
		else if (tempNode->getBalanceFactor() == 0 && curNode->getBalanceFactor() == 2)
		{
			rHRemovalRotate(curNode); //rotate on sub-head node, return hasRotated
		}
	}
	//check if rootNode (curNode here) needs to rotate
	if (abs(curNode->getBalanceFactor()) == 2)
	{
		if (curNode->getBalanceFactor() == 2) //check if left branch will rotate
		{
			if (curNode->getLeftChild()->getBalanceFactor() == 1) //Left-Heavy rotate
			{
				leftHeavyRotate(curNode);
			}
			else if (curNode->getLeftChild()->getBalanceFactor() == -1) //Left-Inner rotate
			{
				leftInnerRotate(curNode);
			}
			else
			{
				lHRemovalRotate(curNode);
			}
		}

		if (curNode->getBalanceFactor() == -2) //check if right branch will rotate
		{
			if (curNode->getRightChild()->getBalanceFactor() == -1) //Right-Heavy rotate
			{
				rightHeavyRotate(curNode);
			}
			else if (curNode->getRightChild()->getBalanceFactor() == 1) //Right-Inner rotate
			{
				rightInnerRotate(curNode);
			}
			else
			{
				rHRemovalRotate(curNode);
			}
		}
	}
	return;
}

template<typename TheType>
void AvlTree<TheType>::leftHeavyRotate(TreeNode<TheType>* nodeA)
{
	bool isRoot = (nodeA->getParent() == 0); //edge case is that nodeA is the root
	TreeNode<TheType>* parentOfA;
	bool isLeftChild; //check whether nodeA is a left child
	if (!isRoot)
	{
		parentOfA = nodeA->getParent();
		if (parentOfA->getLeftChild()->getKey() == nodeA->getKey())
		{
			isLeftChild = true;
		}
		else (isLeftChild = false);
	}
	TreeNode<TheType>* nodeB = nodeA->getLeftChild();
	TreeNode<TheType>* rcOfB = nodeB->getRightChild();

	nodeB->setRightChild(nodeA);
	nodeA->setParent(nodeB);
	nodeA->setLeftChild(rcOfB);
	if (rcOfB != 0) //only assign if it exists
	{
		rcOfB->setParent(nodeA);
	}

	if (!isRoot)
	{
		nodeB->setParent(parentOfA);

		if (isLeftChild)
		{
			parentOfA->setLeftChild(nodeB);
		}
		else
		{
			parentOfA->setRightChild(nodeB);
		}
	}
	else //otherwise, assign nodeB's parent as 0, and nodeB is now the root
	{
		nodeB->setParent(0);
		rootNode = nodeB;
	}

	nodeA->setBalanceFactor(0);
	nodeB->setBalanceFactor(0);
}

template<typename TheType>
void AvlTree<TheType>::leftInnerRotate(TreeNode<TheType>* nodeA)
{
	bool isRoot = (nodeA->getParent() == 0); //edge case is that nodeA is the root
	TreeNode<TheType>* parentOfA;
	bool isLeftChild; //check whether nodeA is a left child
	if (!isRoot)
	{
		parentOfA = nodeA->getParent();
		if (parentOfA->getLeftChild()->getKey() == nodeA->getKey())
		{
			isLeftChild = true;
		}
		else (isLeftChild = false);
	}
	TreeNode<TheType>* nodeB = nodeA->getLeftChild();
	TreeNode<TheType>* nodeC = nodeB->getRightChild(); //after rotation, check if nodeC is the new root
	TreeNode<TheType>* lcOfC = nodeC->getLeftChild();
	TreeNode<TheType>* rcOfC = nodeC->getRightChild();

	nodeC->setLeftChild(nodeB);
	nodeB->setParent(nodeC);
	nodeC->setRightChild(nodeA);
	nodeA->setParent(nodeC);
	nodeB->setRightChild(lcOfC);
	if (lcOfC != 0) //only assign if exists
	{
		lcOfC->setParent(nodeB);
	}
	nodeA->setLeftChild(rcOfC);
	if (rcOfC != 0) //only assign if exists
	{
		rcOfC->setParent(nodeA);
	}

	if (!isRoot)
	{
		nodeC->setParent(parentOfA);

		if (isLeftChild)
		{
			parentOfA->setLeftChild(nodeC);
		}
		else
		{
			parentOfA->setRightChild(nodeC);
		}
	}
	else //nodeC is the new root
	{
		nodeC->setParent(0);
		rootNode = nodeC;
	}

	nodeA->setBalanceFactor(0);
	nodeB->setBalanceFactor(0);
	nodeC->setBalanceFactor(0);
}

template<typename TheType>
void AvlTree<TheType>::rightHeavyRotate(TreeNode<TheType>* nodeA) //In this case, only nodeA, nodeA's parent, nodeB, and B's left child need reassigning
{
	bool isRoot = (nodeA->getParent() == 0); //Edge case is that nodeA is the tree's root
	TreeNode<TheType>* parentOfA;
	bool isRightChild; //Because we don't know if nodeA is a left or right child, do a check at runtime
	if (!isRoot)
	{
		parentOfA = nodeA->getParent();
		if (parentOfA->getRightChild()->getKey() == nodeA->getKey())
		{
			isRightChild = true;
		}
		else (isRightChild = false);
	}
	TreeNode<TheType>* nodeB = nodeA->getRightChild();
	TreeNode<TheType>* lcOfB = nodeB->getLeftChild();

	nodeB->setLeftChild(nodeA); //re-assign nodes
	nodeA->setParent(nodeB);
	nodeA->setRightChild(lcOfB);
	if (lcOfB != 0)
	{
		lcOfB->setParent(nodeA); //Only point B's left child to A if child exists
	}

	if (!isRoot) //If nodeA is not the root, assign nodeB's parent and nodeA's parent's child
	{
		nodeB->setParent(parentOfA);

		if (isRightChild)
		{
			parentOfA->setRightChild(nodeB);
		}
		else
		{
			parentOfA->setLeftChild(nodeB);
		}
	}
	else //otherwise, assign nodeB's parent as 0, and nodeB is now the root
	{
		nodeB->setParent(0);
		rootNode = nodeB;
	}

	nodeA->setBalanceFactor(0); //Reset balance factors of main nodes of the rotation
	nodeB->setBalanceFactor(0);
}

template<typename TheType>
void AvlTree<TheType>::rightInnerRotate(TreeNode<TheType>* nodeA)
{
	bool isRoot = (nodeA->getParent() == 0); //edge case is that nodeA is the root
	TreeNode<TheType>* parentOfA;
	bool isRightChild; //check whether nodeA is a left child
	if (!isRoot)
	{
		parentOfA = nodeA->getParent();
		isRightChild = (parentOfA->getRightChild()->getKey() == nodeA->getKey());
	}
	TreeNode<TheType>* nodeB = nodeA->getRightChild();
	TreeNode<TheType>* nodeC = nodeB->getLeftChild();
	TreeNode<TheType>* lcOfC = nodeC->getLeftChild();
	TreeNode<TheType>* rcOfC = nodeC->getRightChild();

	nodeC->setLeftChild(nodeA);
	nodeA->setParent(nodeC);
	nodeC->setRightChild(nodeB);
	nodeB->setParent(nodeC);
	nodeA->setRightChild(lcOfC);
	if (lcOfC != 0) //if exists, assign
	{
		lcOfC->setParent(nodeA);
	}
	nodeB->setLeftChild(rcOfC);
	if (rcOfC != 0) //only assign if exists
	{
		rcOfC->setParent(nodeB);
	}

	if (!isRoot)
	{
		nodeC->setParent(parentOfA);

		if (isRightChild)
		{
			parentOfA->setRightChild(nodeC);
		}
		else
		{
			parentOfA->setLeftChild(nodeC);
		}
	}
	else //nodeC is the new root
	{
		nodeC->setParent(0);
		rootNode = nodeC;
	}

	nodeA->setBalanceFactor(0);
	nodeB->setBalanceFactor(0);
	nodeC->setBalanceFactor(0);
}

template<typename TheType>
void AvlTree<TheType>::lHRemovalRotate(TreeNode<TheType>* nodeA)
{
	bool isRoot = (nodeA->getParent() == 0); //edge case is that nodeA is the root
	TreeNode<TheType>* parentOfA;
	bool isRightChild; //check whether nodeA is a left child
	if (!isRoot)
	{
		parentOfA = nodeA->getParent();
		isRightChild = (parentOfA->getRightChild()->getKey() == nodeA->getKey());
	}

	TreeNode<TheType>* nodeB = nodeA->getRightChild();
	TreeNode<TheType>* nodeC = nodeB->getLeftChild();

	if (!isRoot)
	{
		nodeA->setParent(nodeB);
		nodeB->setLeftChild(nodeA);
		nodeA->setRightChild(nodeC);
		nodeC->setParent(nodeA);
		nodeB->setParent(parentOfA);

		if (isRightChild)
		{
			parentOfA->setRightChild(nodeB);
		}
		else //otherwise nodeA was a left child
		{
			parentOfA->setLeftChild(nodeB);
		}
	}
	else //nodeA is the root
	{
		nodeA->setParent(nodeB);
		nodeB->setLeftChild(nodeA);
		nodeC->setParent(nodeA);
		nodeA->setRightChild(nodeC);
		nodeB->setParent(0);
		rootNode = nodeB;
	}

	nodeA->setBalanceFactor(0);
	nodeB->setBalanceFactor(0);
	nodeC->setBalanceFactor(0);
}

template<typename TheType>
void AvlTree<TheType>::rHRemovalRotate(TreeNode<TheType>* nodeA)
{
	bool isRoot = (nodeA->getParent() == 0); //edge case is that nodeA is the root
	TreeNode<TheType>* parentOfA;
	bool isLeftChild; //check whether nodeA is a left child
	if (!isRoot)
	{
		parentOfA = nodeA->getParent();
		if (parentOfA->getLeftChild()->getKey() == nodeA->getKey())
		{
			isLeftChild = true;
		}
		else (isLeftChild = false);
	}

	TreeNode<TheType>* nodeB = nodeA->getLeftChild();
	TreeNode<TheType>* nodeC = nodeB->getRightChild();

	if (!isRoot)
	{
		nodeA->setParent(nodeB);
		nodeB->setRightChild(nodeA);
		nodeC->setParent(nodeA);
		nodeA->setLeftChild(nodeC);
		nodeB->setParent(parentOfA);

		if (isLeftChild)
		{
			parentOfA->setLeftChild(nodeB);
		}
		else //nodeA was a right child
		{
			parentOfA->setRightChild(nodeA);
		}
	}
	else //nodeA is the root
	{
		nodeA->setParent(nodeB);
		nodeB->setRightChild(nodeA);
		nodeC->setParent(nodeA);
		nodeA->setLeftChild(nodeC);
		nodeB->setParent(0);
		rootNode = nodeB;
	}

	nodeA->setBalanceFactor(0);
	nodeB->setBalanceFactor(0);
	nodeC->setBalanceFactor(0);
}

#endif /* AVLTREE_H_ */
