/*
 * AvlTree.cpp
 *
 *  Created on: Apr 10, 2018
 *      Author: david
 */

#include "AvlTree.h"

AvlTree::AvlTree()
{
	rootNode = 0;
	foundNode = 0;
}

AvlTree::~AvlTree() {}

void AvlTree::addItem(Eclipse* myEclipse)
{
	//If no rootNode, add as rootNode. Else, add as regular node
	bool hasRotated = false;
	if (rootNode == 0)
	{
		rootNode = new TreeNode(myEclipse);
	}
	else //Find insertion location recursively and insert as non-root node
	{
		TreeNode* curNode = rootNode; //curNode will travel down the tree to find insertion location
		TreeNode* insertNode = new TreeNode(myEclipse); //insertNode will travel down the tree so balanceTree can be called
		
		if (myEclipse->getID() > curNode->getKey()) //if this occurs, recurse right
		{
			if (curNode->getRightChild() == 0) //insert here if right child is 0
			{
				curNode->setRightChild(new TreeNode(curNode,myEclipse)); //don't use insertNode here to avoid extra line
				curNode->setBalanceFactor(computeBalanceFactor(curNode)); //guaranteed no rotations will happen here
				return;
			}

			recurseAdd(curNode->getRightChild(),insertNode,myEclipse,hasRotated);
			//After right recursion return, update balanceFactor based on right branch insertion
			if (!hasRotated) //only update bF if not rotated and if insertNode is a single child
			{
				curNode->setBalanceFactor(computeBalanceFactor(curNode));
			}

			if (abs(curNode->getBalanceFactor()) == 2) //check for re-balancing
			{
				hasRotated = updateTree(foundNode);
			}
		}
		else //otherwise, myEclipse ID should be < curNode's key, so recurse left
		{
			if (curNode->getLeftChild() == 0) //insert here if left child is 0
			{
				curNode->setLeftChild(new TreeNode(curNode,myEclipse)); //Don't use insertNode until recurseAdd
				curNode->setBalanceFactor(computeBalanceFactor(curNode)); //guaranteed no rotation will happen here
				return;
			}

			recurseAdd(curNode->getLeftChild(),insertNode,myEclipse,hasRotated);
			//After left recursion return, update balanceFactor based on left branch insertion
			if (!hasRotated) //only update bF if not rotated and if insertNode is a single child
			{
				curNode->setBalanceFactor(computeBalanceFactor(curNode));
			}

			if (abs(curNode->getBalanceFactor()) == 2) //check for re-balancing
			{
				hasRotated = updateTree(foundNode);
			}
		}
	}
}

void AvlTree::recurseAdd(TreeNode* curNode, TreeNode* insertNode, Eclipse* myEclipse, bool &hasRotated)
{
	if (myEclipse->getID() > curNode->getKey()) //if this occurs, recurse right
	{
		if (curNode->getRightChild() == 0) //insert here if right child is 0
		{
			curNode->setRightChild(insertNode); //when assigning insertNode, need to assign parent relation
			insertNode->setParent(curNode);
			curNode->setBalanceFactor(computeBalanceFactor(curNode));
			foundNode = curNode;
			return;
		}

		recurseAdd(curNode->getRightChild(),insertNode,myEclipse,hasRotated);
		//After right recursion return, update balanceFactor based on right branch insertion
		if (!hasRotated)
		{
			curNode->setBalanceFactor(computeBalanceFactor(curNode)); //Only update if lower branch hasn't rotated
		}

		if (abs(curNode->getBalanceFactor()) == 2) //check for re-balancing
		{
			hasRotated = updateTree(foundNode);
		}
	}
	else //otherwise, myEclipse ID should be < curNode's key, so recurse left
	{
		if (curNode->getLeftChild() == 0) //insert here if left child is 0
		{
			curNode->setLeftChild(insertNode);
			insertNode->setParent(curNode);
			curNode->setBalanceFactor(computeBalanceFactor(curNode));
			foundNode = curNode;
			return;
		}

		recurseAdd(curNode->getLeftChild(),insertNode,myEclipse,hasRotated);
		//After left recursion return, update balanceFactor based on left branch insertion
		if (!hasRotated)
		{
			curNode->setBalanceFactor(computeBalanceFactor(curNode)); //Only update if lower branch hasn't rotated
		}

		if (abs(curNode->getBalanceFactor()) == 2)
		{
			hasRotated = updateTree(foundNode); //check for re-balancing
		}
	}
}

TreeNode* AvlTree::getRootNode()
{
	return rootNode;
}

TreeNode* AvlTree::getFoundNode()
{
	return foundNode;
}

void AvlTree::setFoundNode(TreeNode* myFoundNode)
{
	foundNode = myFoundNode;
}

void AvlTree::removeItem(Eclipse* myEclipse)
{
	//TODO make 3 methods to cover the 3 removal cases: leaf node, node with 1 child, node with 2 children
	
	TreeNode* delNode = findNodeForRemoval(myEclipse->getID());
	if (delNode->getEclipse()->getIsBlank()) //If an invalid node, cerr and return
	{
		cerr << "This item does not exist!" << endl;
		return;
	}
	
	//Leaf Node case
	if (delNode->getLeftChild() == 0 && delNode->getRightChild() == 0) //delNode is a leaf node
	{
		if (delNode->getParent() == 0) //delnode is the root
		{
			delNode = 0;
		}
		else //delnode has a parent
		{
			if (delNode->getKey() == delNode->getParent()->getLeftChild()->getKey()) //delNode is a left child
			{
				updateTree(delNode);
				delNode->getParent()->setLeftChild(0);
				delNode = 0;

			}
			else //otherwise, delnode is a right child
			{
				updateTree(delNode);
				delNode->getParent()->setRightChild(0);
				delNode = 0;

			}
		}
	}
	
	//double child case
	else if (delNode->getLeftChild() != 0 && delNode->getRightChild() != 0) //delNode has two children
	{
		TreeNode* succNode = delNode->getRightChild(); //start the search for successor at delNode's right child and recurse left
		while (succNode->getLeftChild() != 0)
		{
			succNode = succNode->getLeftChild();
		}
		
		delNode->setEclipse(succNode->getEclipse()); //assign delNode as Successor
		removeItem(succNode->getEclipse()); //recurse to delete successor Node
		
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
				delNode = 0;
			}
			else
			{
				rootNode = delNode->getRightChild();
				delNode = 0;
			}
		}
		else //delNode has a parent
		{
			bool isLeftChild = (delNode->getKey() == delNode->getParent()->getLeftChild()->getKey());

			TreeNode* parent = delNode->getParent();
			if (isLeftChild)
			{
				if (hasLeftChild)
				{
					parent->setLeftChild(delNode->getLeftChild());
					parent->getLeftChild()->setParent(parent);
				}
				else
				{
					parent->setLeftChild(delNode->getRightChild());
					parent->getLeftChild()->setParent(parent);
				}
			}
			else //delNode is a right child
			{
				if (hasLeftChild)
				{
					parent->setRightChild(delNode->getLeftChild());
					parent->getRightChild()->setParent(parent);
				}
				else
				{
					parent->setRightChild(delNode->getRightChild());
					parent->getRightChild()->setParent(parent);
				}
			}
			//Parent to delNode-child relations have been formed, now delete delNode
			updateTree(delNode);
			delNode = 0;
		}
	}
}

Eclipse* AvlTree::findEclipse(int key) //will return an invalid Eclipse if not found
{
	TreeNode* curNode = rootNode;
	bool forRemoval = false;
	find(curNode,key,forRemoval);
	return foundNode->getEclipse();
}

TreeNode* AvlTree::findNode(int key) //will return an invalid TreeNode if not found
{
	TreeNode* curNode = rootNode;
	bool forRemoval = false;
	find(curNode,key);
	return foundNode;
}

TreeNode* AvlTree::findNodeForRemoval(int key)
{
	TreeNode* curNode = rootNode;
	bool forRemoval = true;
	find(curNode,key,forRemoval);
	return foundNode;
}

void AvlTree::find(TreeNode* curNode, int key)
{
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
		this->setFoundNode(curNode);
	}
	else
	{
		this->setFoundNode(new TreeNode());
	}
	return;
}

int AvlTree::computeBalanceFactor(TreeNode* myNode) //Use this to calculate a new bF
{
	int leftDepth = -1;
	int rightDepth = -1;
	computeBalanceFactor(myNode,leftDepth,rightDepth);
	return (leftDepth - rightDepth);
}

void AvlTree::computeBalanceFactor(TreeNode* myNode, int &leftDepth, int &rightDepth)
{
	//first compute left depth. If either child are valid, keep going
	if (leftDepth == -1) //only perform this once
	{
		leftDepth = 0;
		while (myNode->getLeftChild() != 0 || myNode->getRightChild() != 0)
		{
			if (myNode->getLeftChild() != 0)
			{
				computeBalanceFactor(myNode->getLeftChild(),leftDepth,rightDepth);
				leftDepth++;
				return;
			}

			if (leftDepth != 0 && myNode->getRightChild() != 0)
			{
				computeBalanceFactor(myNode->getRightChild(),leftDepth,rightDepth);
				leftDepth++;
				return;
			}
		}
	}

	//then compute right depth. If either child are valid, keep going
	if (rightDepth == -1) //only perform this once
	{
		rightDepth = 0;
		while (myNode->getLeftChild() != 0 || myNode->getRightChild() != 0)
		{
			if (myNode->getRightChild() != 0)
			{
				computeBalanceFactor(myNode->getRightChild(),leftDepth,rightDepth);
				rightDepth++;
				return;
			}

			if (rightDepth != 0 && myNode->getLeftChild() != 0)
			{
				computeBalanceFactor(myNode->getLeftChild(),leftDepth,rightDepth);
				rightDepth++;
				return;
			}
		}
	}
}

void AvlTree::printPreOrder()
{
	printPreOrder(rootNode);
}

void AvlTree::printPreOrder(TreeNode* curNode)
{
	cout << *(curNode->getEclipse());

	if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
	{
		printPreOrder(curNode->getLeftChild());
	}

	if (curNode->getRightChild() != 0) //only check right subtrees if not 0
	{
		printPreOrder(curNode->getRightChild());
	}
}

void AvlTree::printInOrder()
{
	printInOrder(rootNode);
}

void AvlTree::printInOrder(TreeNode* curNode)
{
	if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
	{
		printInOrder(curNode->getLeftChild());
	}

	cout << *(curNode->getEclipse());

	if (curNode->getRightChild() != 0) //only check right subtrees if not 0
	{
		printInOrder(curNode->getRightChild());
	}
}

void AvlTree::printPostOrder()
{
	printPostOrder(rootNode);
}

void AvlTree::printPostOrder(TreeNode* curNode)
{
	if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
	{
		printPostOrder(curNode->getLeftChild());
	}

	if (curNode->getRightChild() != 0) //only check right subtrees if not 0
	{
		printPostOrder(curNode->getRightChild());
	}

	cout << *(curNode->getEclipse());
}

void AvlTree::copyToArray(ResizeableArray<Eclipse> &myEclipses)
{
	copyToArray(myEclipses,rootNode);
}

void AvlTree::copyToArray(ResizeableArray<Eclipse> &myEclipses, TreeNode* firstNode)
{
	if (firstNode->getLeftChild() != 0) //only check left subtrees if not 0
	{
		copyToArray(myEclipses,firstNode->getLeftChild());
	}

	myEclipses.Add(*(firstNode->getEclipse()));

	if (firstNode->getRightChild() != 0) //only check right subtrees if not 0
	{
		copyToArray(myEclipses,firstNode->getRightChild());
	}
}

bool AvlTree::updateTree(TreeNode* insertedNode) //start from insertion, travel up the parents to check for rotation cases
{
	TreeNode* curNode = insertedNode->getParent();
	curNode->setBalanceFactor(computeBalanceFactor(curNode));
	bool isLeftChild = (insertedNode->getParent()->getLeftChild()->getKey() == insertedNode->getKey());

	if (abs(insertedNode->getParent()->getBalanceFactor()) == 2
			&& insertedNode->getParent()->hasTwoChildren()
			&& insertedNode->getBalanceFactor() == 0) //special case during removal at inserted node where we should start at sibling
	{
		if (isLeftChild)
		{
			return updateTree(insertedNode->getParent()->getRightChild()); //restart the balance op at the node that will catch the rotation
		}
		else //otherwise, insertedNode is a right child
		{
			return updateTree(insertedNode->getParent()->getLeftChild());
		}
	}

	while (curNode->getParent() != 0) //continue until you reach the head node
	{
		curNode->getParent()->setBalanceFactor(computeBalanceFactor(curNode));
		//Test for Left-Heavy rotation
		if (curNode->getBalanceFactor() == 1 && curNode->getParent()->getBalanceFactor() == 2)
		{
			leftHeavyRotate(curNode->getParent()); //rotate on sub-head node, return hasRotated
			return true;
		}
		//Test for Left-Inner rotation
		else if (curNode->getBalanceFactor() == -1 && curNode->getParent()->getBalanceFactor() == 2)
		{
			leftInnerRotate(curNode->getParent()); //rotate on sub-head node, return hasRotated
			return true;
		}
		//Test for Right-Heavy rotation
		else if (curNode->getBalanceFactor() == -1 && curNode->getParent()->getBalanceFactor() == -2)
		{
			rightHeavyRotate(curNode->getParent()); //rotate on sub-head node, return hasRotated
			return true;
		}
		//Test for Right-Inner rotation
		else if (curNode->getBalanceFactor() == 1 && curNode->getParent()->getBalanceFactor() == -2)
		{
			rightInnerRotate(curNode->getParent()); //rotate on sub-head node, return hasRotated
			return true;
		}
		//recurse up to the next parent
		curNode = curNode->getParent();
	}
	//If went up to parent and no rotations, return false
	return false;
}

void AvlTree::leftHeavyRotate(TreeNode* nodeA)
{
	bool isRoot = (nodeA->getParent() == 0);
	TreeNode* parentOfA;
	bool isLeftDecent;
	if (!isRoot)
	{
		parentOfA = nodeA->getParent();
		if (parentOfA->getLeftChild()->getKey() == nodeA->getKey())
		{
			isLeftDecent = true;
		}
		else (isLeftDecent = false);
	}
	TreeNode* nodeB = nodeA->getLeftChild();
	TreeNode* rcOfB = nodeB->getRightChild();

	nodeB->setRightChild(nodeA);
	nodeA->setParent(nodeB);
	nodeA->setLeftChild(rcOfB);
	rcOfB->setParent(nodeA);
	nodeB->setParent(parentOfA);
	if (isLeftDecent)
	{
		parentOfA->setLeftChild(nodeB);
	}
	else
	{
		parentOfA->setRightChild(nodeB);
	}

	nodeA->setBalanceFactor(0);
	nodeB->setBalanceFactor(0);
}

void AvlTree::leftInnerRotate(TreeNode* nodeA) //TODO
{
	TreeNode* parentOfA = nodeA->getParent();
	bool isLeftDecent;
	if (parentOfA->getLeftChild()->getKey() == nodeA->getKey())
	{
		isLeftDecent = true;
	}
	else (isLeftDecent = false);
	TreeNode* nodeB = nodeA->getLeftChild();
	TreeNode* nodeC = nodeB->getRightChild();
	TreeNode* lcOfC = nodeC->getLeftChild();
	TreeNode* rcOfC = nodeC->getRightChild();

	nodeC->setLeftChild(nodeB);
	nodeB->setParent(nodeC);
	nodeC->setRightChild(nodeA);
	nodeA->setParent(nodeC);
	nodeB->setRightChild(lcOfC);
	lcOfC->setParent(nodeB);
	nodeA->setLeftChild(rcOfC);
	rcOfC->setParent(nodeA);
	nodeC->setParent(parentOfA);
	if (isLeftDecent)
	{
		parentOfA->setLeftChild(nodeC);
	}
	else
	{
		parentOfA->setRightChild(nodeC);
	}

	nodeA->setBalanceFactor(0);
	nodeB->setBalanceFactor(0);
	nodeC->setBalanceFactor(0);
}

void AvlTree::rightHeavyRotate(TreeNode* nodeA) //In this case, only nodeA, nodeA's parent, nodeB, and B's left child need reassigning
{
	bool isRoot = (nodeA->getParent() == 0); //Edge case is that nodeA is the tree's root
	TreeNode* parentOfA;
	bool isRightDescent; //Because we don't know if nodeA is a left or right child, do a check at runtime
	if (!isRoot)
	{
		parentOfA = nodeA->getParent();
		if (parentOfA->getRightChild()->getKey() == nodeA->getKey())
		{
			isRightDescent = true;
		}
		else (isRightDescent = false);
	}
	TreeNode* nodeB = nodeA->getRightChild();
	TreeNode* lcOfB = nodeB->getLeftChild();

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
		if (isRightDescent)
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

void AvlTree::rightInnerRotate(TreeNode* nodeA) //TODO
{
	TreeNode* parentOfA = nodeA->getParent();
	bool isRightDecent;
	if (parentOfA->getRightChild()->getKey() == nodeA->getKey())
	{
		isRightDecent = true;
	}
	else (isRightDecent = false);
	TreeNode* nodeB = nodeA->getRightChild();
	TreeNode* nodeC = nodeB->getLeftChild();
	TreeNode* lcOfC = nodeC->getLeftChild();
	TreeNode* rcOfC = nodeC->getRightChild();

	nodeC->setLeftChild(nodeA);
	nodeA->setParent(nodeC);
	nodeC->setRightChild(nodeB);
	nodeB->setParent(nodeC);
	nodeA->setRightChild(lcOfC);
	lcOfC->setParent(nodeA);
	nodeB->setLeftChild(rcOfC);
	rcOfC->setParent(nodeB);
	nodeC->setParent(parentOfA);
	if (isRightDecent)
	{
		parentOfA->setRightChild(nodeC);
	}
	else
	{
		parentOfA->setLeftChild(nodeC);
	}

	nodeA->setBalanceFactor(0);
	nodeB->setBalanceFactor(0);
	nodeC->setBalanceFactor(0);
}
//----------------------------------------------------------------
int main() {
	string* myString1 = new string[18];
	string* myString2 = new string[18];
	string* myString3 = new string[18];
	string* myString4 = new string[18];
	string* myString5 = new string[18];
	string* myString6 = new string[18];
	string* myString7 = new string[18];
	string* myString8 = new string[18];
	string* myString9 = new string[18];
	string* myString10 = new string[18];
	string* myString11 = new string[18];
	string* myString12 = new string[18];
	for (int i = 0; i < 18; i++)
	{
		myString1[i] = "1";
		myString2[i] = "2";
		myString3[i] = "3";
		myString4[i] = "4";
		myString5[i] = "5";
		myString6[i] = "6";
		myString7[i] = "7";
		myString8[i] = "8";
		myString9[i] = "9";
		myString10[i] = "10";
		myString11[i] = "11";
		myString12[i] = "12";
	}
	Eclipse* myEclipse1 = new Eclipse(myString1);
	Eclipse* myEclipse2 = new Eclipse(myString2);
	Eclipse* myEclipse3 = new Eclipse(myString3);
	Eclipse* myEclipse4 = new Eclipse(myString4);
	Eclipse* myEclipse5 = new Eclipse(myString5);
	Eclipse* myEclipse6 = new Eclipse(myString6);
	Eclipse* myEclipse7 = new Eclipse(myString7);
	Eclipse* myEclipse8 = new Eclipse(myString8);
	Eclipse* myEclipse9 = new Eclipse(myString9);
	Eclipse* myEclipse10 = new Eclipse(myString10);
	Eclipse* myEclipse11 = new Eclipse(myString11);
	Eclipse* myEclipse12 = new Eclipse(myString12);

	AvlTree* myTree = new AvlTree();
	myTree->addItem(myEclipse1);
	myTree->addItem(myEclipse2);
	myTree->addItem(myEclipse3);
	/*myTree->addItem(myEclipse2);
	myTree->addItem(myEclipse6);
	myTree->addItem(myEclipse9);
	myTree->addItem(myEclipse12);
	myTree->addItem(myEclipse1);
	myTree->addItem(myEclipse4);
	myTree->addItem(myEclipse7);
	myTree->addItem(myEclipse11);
	myTree->addItem(myEclipse5);*/

	cout << "Printing Pre-Order..." << endl;
	myTree->printPreOrder();
	/*cout << "Printing In-Order..." << endl;
	myTree->printInOrder();
	cout << "Printing Post-Order..." << endl;
	myTree->printPostOrder();*/

	myTree->removeItem(myEclipse1);

	cout << "Done.";



	return 0;
}
//----------------------------------------------------------------

