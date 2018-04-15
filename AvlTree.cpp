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
	//TODO //If no rootNode, add as rootNode. Else, add as regular node
	bool hasRotated = false;
	if (rootNode == 0)
	{
		rootNode = new TreeNode(myEclipse);
	}
	else //Find insertion location recursively and insert as non-root node
	{
		TreeNode* curNode = rootNode;
		
		if (myEclipse->getID() > curNode->getKey()) //if this occurs, recurse right
		{
			if (curNode->getRightChild() == 0) //insert here if right child is 0
			{
				curNode->setRightChild(new TreeNode(curNode,myEclipse));
				//Now we check tree for re-balancing
				hasRotated = balanceTree(curNode->getRightChild());
				if (!hasRotated)
				{
					curNode->setBalanceFactor(curNode->getBalanceFactor() - 1);
				}
				return;
			}
			recurseAdd(curNode->getRightChild(),myEclipse,hasRotated);
			if (!hasRotated)
			{
				curNode->setBalanceFactor(curNode->getBalanceFactor() - 1);
			}
		}
		else //otherwise, myEclipse ID should be < curNode's key, so recurse left
		{
			if (curNode->getLeftChild() == 0) //insert here if left child is 0
			{
				curNode->setLeftChild(new TreeNode(curNode,myEclipse));
				//Now we check tree for re-balancing
				hasRotated = balanceTree(curNode->getLeftChild());
				if (!hasRotated)
				{
					curNode->setBalanceFactor(curNode->getBalanceFactor() + 1);
				}
				return;
			}
			recurseAdd(curNode->getLeftChild(),myEclipse,hasRotated);
			if (!hasRotated)
			{
				curNode->setBalanceFactor(curNode->getBalanceFactor() + 1);
			}
		}
	}
}

void AvlTree::recurseAdd(TreeNode* curNode, Eclipse* myEclipse, bool &hasRotated)
{
	if (myEclipse->getID() > curNode->getKey()) //if this occurs, recurse right
	{
		if (curNode->getRightChild() == 0) //insert here if right child is 0
		{
			curNode->setRightChild(new TreeNode(curNode,myEclipse));
			//Now we check tree for re-balancing
			hasRotated = balanceTree(curNode->getRightChild());
			if (!hasRotated)
			{
				curNode->setBalanceFactor(curNode->getBalanceFactor() - 1);
			}
			return;
		}
		recurseAdd(curNode->getRightChild(),myEclipse,hasRotated);
		if (!hasRotated)
		{
			curNode->setBalanceFactor(curNode->getBalanceFactor() - 1);
		}
	}
	else //otherwise, myEclipse ID should be < curNode's key, so recurse left
	{
		if (curNode->getLeftChild() == 0) //insert here if left child is 0
		{
			curNode->setLeftChild(new TreeNode(curNode,myEclipse));
			//Now we check tree for re-balancing
			hasRotated = balanceTree(curNode->getLeftChild());
			if (!hasRotated)
			{
				curNode->setBalanceFactor(curNode->getBalanceFactor() + 1);
			}
			return;
		}
		recurseAdd(curNode->getLeftChild(),myEclipse,hasRotated);
		if (!hasRotated)
		{
			curNode->setBalanceFactor(curNode->getBalanceFactor() + 1);
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

bool AvlTree::balanceTree(TreeNode* insertedNode)
{
	TreeNode* curNode = insertedNode->getParent();
	while (curNode->getParent() != 0) //continue until you reach the head node
	{
		//Test for Left-Heavy rotation
		if (curNode->getBalanceFactor() == 1 && curNode->getParent()->getBalanceFactor() == 2)
		{
			leftHeavyRotate(curNode->getParent());
			return true;
		}
		//Test for Left-Inner rotation
		else if (curNode->getBalanceFactor() == -1 && curNode->getParent()->getBalanceFactor() == 2)
		{
			leftInnerRotate(curNode->getParent());
			return true;
		}
		//Test for Right-Heavy rotation
		else if (curNode->getBalanceFactor() == -1 && curNode->getParent()->getBalanceFactor() == -2)
		{
			rightHeavyRotate(curNode->getParent());
			return true;
		}
		//Test for Right-Inner rotation
		else if (curNode->getBalanceFactor() == 1 && curNode->getParent()->getBalanceFactor() == -2)
		{
			rightInnerRotate(curNode->getParent());
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
	TreeNode* parentOfA = nodeA->getParent();
	bool isLeftDecent;
	if (parentOfA->getLeftChild()->getKey() == nodeA->getKey())
	{
		isLeftDecent = true;
	}
	else (isLeftDecent = false);
	TreeNode* nodeB = nodeA->getLeftChild();
	TreeNode* rcOfB = nodeB->getRightChild();

	nodeA->setParent(nodeB);
	nodeB->setRightChild(nodeA);
	nodeA->setLeftChild(rcOfB);
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

void AvlTree::leftInnerRotate(TreeNode* nodeA)
{
	//TODO
}

void AvlTree::rightHeavyRotate(TreeNode* nodeA)
{
	TreeNode* parentOfA = nodeA->getParent();
	bool isRightDecent;
	if (parentOfA->getRightChild()->getKey() == nodeA->getKey())
	{
		isRightDecent = true;
	}
	else (isRightDecent = false);
	TreeNode* nodeB = nodeA->getRightChild();
	TreeNode* lcOfB = nodeB->getLeftChild();

	nodeA->setParent(nodeB);
	nodeB->setLeftChild(nodeA);
	nodeA->setRightChild(lcOfB);
	nodeB->setParent(parentOfA);
	if (isRightDecent)
	{
		parentOfA->setRightChild(nodeB);
	}
	else
	{
		parentOfA->setLeftChild(nodeB);
	}

	nodeA->setBalanceFactor(0);
	nodeB->setBalanceFactor(0);
}

void AvlTree::rightInnerRotate(TreeNode* nodeA)
{
	//TODO
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

