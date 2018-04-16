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
				curNode->setBalanceFactor(curNode->getBalanceFactor() - 1); //guaranteed no rotations will happen here
				return;
			}

			recurseAdd(curNode->getRightChild(),insertNode,myEclipse,hasRotated);
			//After right recursion return, update balanceFactor based on right branch insertion
			if (!hasRotated)
			{
				curNode->setBalanceFactor(curNode->getBalanceFactor() - 1); //Only update if lower branch hasn't rotated
			}

			if (abs(curNode->getBalanceFactor()) == 2) //check for re-balancing
			{
				hasRotated = balanceTree(insertNode);
			}
		}
		else //otherwise, myEclipse ID should be < curNode's key, so recurse left
		{
			if (curNode->getLeftChild() == 0) //insert here if left child is 0
			{
				curNode->setLeftChild(new TreeNode(curNode,myEclipse)); //Don't use insertNode until recurseAdd
				curNode->setBalanceFactor(curNode->getBalanceFactor() + 1); //guaranteed no rotation will happen here
				return;
			}

			recurseAdd(curNode->getLeftChild(),insertNode,myEclipse,hasRotated);
			//After left recursion return, update balanceFactor based on left branch insertion
			if (!hasRotated)
			{
				curNode->setBalanceFactor(curNode->getBalanceFactor() + 1); //Only update if lower branch hasn't rotated
			}

			if (abs(curNode->getBalanceFactor()) == 2) //check for re-balancing
			{
				hasRotated = balanceTree(insertNode);
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
			curNode->setBalanceFactor(curNode->getBalanceFactor() - 1);

			if (abs(curNode->getBalanceFactor()) == 2) //check for re-balancing? May not have to
			{
				hasRotated = balanceTree(insertNode);
			}
			return;
		}

		recurseAdd(curNode->getRightChild(),insertNode,myEclipse,hasRotated);
		//After right recursion return, update balanceFactor based on right branch insertion
		if (!hasRotated)
		{
			curNode->setBalanceFactor(curNode->getBalanceFactor() - 1); //Only update if lower branch hasn't rotated
		}

		if (abs(curNode->getBalanceFactor()) == 2) //check for re-balancing
		{
			hasRotated = balanceTree(insertNode);
		}
	}
	else //otherwise, myEclipse ID should be < curNode's key, so recurse left
	{
		if (curNode->getLeftChild() == 0) //insert here if left child is 0
		{
			curNode->setLeftChild(insertNode);
			insertNode->setParent(curNode);
			curNode->setBalanceFactor(curNode->getBalanceFactor() + 1);

			if (abs(curNode->getBalanceFactor()) == 2) //check for re-balancing? May not have to
			{
				hasRotated = balanceTree(insertNode);
			}
			return;
		}

		recurseAdd(curNode->getLeftChild(),insertNode,myEclipse,hasRotated);
		//After left recursion return, update balanceFactor based on left branch insertion
		if (!hasRotated)
		{
			curNode->setBalanceFactor(curNode->getBalanceFactor() + 1); //Only update if lower branch hasn't rotated
		}

		if (abs(curNode->getBalanceFactor()) == 2)
		{
			hasRotated = balanceTree(insertNode); //check for re-balancing
		}
	}
}

TreeNode* AvlTree::getRootNode()
{
	return rootNode;
}

void AvlTree::removeItem(Eclipse* myEclipse)
{
	//TODO
}

void AvlTree::removeItem(int key)
{
	//TODO
}

Eclipse* AvlTree::findEclipse(int key)
{
	//TODO
}

TreeNode* AvlTree::findNode(int key)
{
	//TODO
}

void AvlTree::printPreOrder()
{
	TreeNode* curNode = rootNode;
	if (curNode != 0)
	{
		cout << *(curNode->getEclipse());
	}

	if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
	{
		printInOrder(curNode->getLeftChild());
	}

	if (curNode->getRightChild() != 0) //only check right subtrees if not 0
	{
		printInOrder(curNode->getRightChild());
	}
}

void AvlTree::printPreOrder(TreeNode* curNode)
{
	cout << *(curNode->getEclipse());

	if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
	{
		printInOrder(curNode->getLeftChild());
	}

	if (curNode->getRightChild() != 0) //only check right subtrees if not 0
	{
		printInOrder(curNode->getRightChild());
	}
}

void AvlTree::printInOrder()
{
	TreeNode* curNode = rootNode;
	if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
	{
		printInOrder(curNode->getLeftChild());
	}

	if (curNode != 0)
	{
		cout << *(curNode->getEclipse());
	}

	if (curNode->getRightChild() != 0) //only check right subtrees if not 0
	{
		printInOrder(curNode->getRightChild());
	}
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
	TreeNode* curNode = rootNode;
	if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
	{
		printInOrder(curNode->getLeftChild());
	}

	if (curNode->getRightChild() != 0) //only check right subtrees if not 0
	{
		printInOrder(curNode->getRightChild());
	}

	if (curNode != 0)
	{
		cout << *(curNode->getEclipse());
	}
}

void AvlTree::printPostOrder(TreeNode* curNode)
{
	if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
	{
		printInOrder(curNode->getLeftChild());
	}

	if (curNode->getRightChild() != 0) //only check right subtrees if not 0
	{
		printInOrder(curNode->getRightChild());
	}

	cout << *(curNode->getEclipse());
}

bool AvlTree::balanceTree(TreeNode* insertedNode) //start from insertion, travel up the parents to check for rotation cases
{
	TreeNode* curNode = insertedNode->getParent(); //curNode starts at insertedNode's parent because insertedNode's bF == 0
	while (curNode->getParent() != 0) //continue until you reach the head node
	{
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
	TreeNode* parentOfA = nodeA->getParent(); //TODO
	bool isLeftDecent;
	if (parentOfA->getLeftChild()->getKey() == nodeA->getKey())
	{
		isLeftDecent = true;
	}
	else (isLeftDecent = false);
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
	bool isRightDecent; //Because we don't know if nodeA is a left or right child, do a check at runtime
	if (!isRoot)
	{
		parentOfA = nodeA->getParent();
		if (parentOfA->getRightChild()->getKey() == nodeA->getKey())
		{
			isRightDecent = true;
		}
		else (isRightDecent = false);
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
		if (isRightDecent)
		{
			parentOfA->setRightChild(nodeB);
		}
		else
		{
			parentOfA->setLeftChild(nodeB);
		}
	}
	else (nodeB->setParent(0)); //otherwise, assign nodeB's parent as 0, and nodeB is now the root
	rootNode = nodeB;

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
	for (int i = 0; i < 18; i++)
	{
		myString1[i] = "1";
		myString2[i] = "2";
		myString3[i] = "3";
		myString4[i] = "4";
		myString5[i] = "5";
		myString6[i] = "6";
	}
	Eclipse* myEclipse1 = new Eclipse(myString1);
	Eclipse* myEclipse2 = new Eclipse(myString2);
	Eclipse* myEclipse3 = new Eclipse(myString3);
	Eclipse* myEclipse4 = new Eclipse(myString4);
	Eclipse* myEclipse5 = new Eclipse(myString5);
	Eclipse* myEclipse6 = new Eclipse(myString6);

	AvlTree* myTree = new AvlTree();
	myTree->addItem(myEclipse1);
	myTree->addItem(myEclipse2);
	myTree->addItem(myEclipse3);
	myTree->addItem(myEclipse4);
	myTree->addItem(myEclipse5);
	myTree->addItem(myEclipse6);

	cout << "Printing Pre-Order..." << endl;
	myTree->printPreOrder();
	cout << "Printing In-Order..." << endl;
	myTree->printInOrder();
	cout << "Printing Post-Order..." << endl;
	myTree->printPostOrder();
	cout << "Done.";



	return 0;
}
//----------------------------------------------------------------

