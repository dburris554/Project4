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
	//curNode = 0;
}

AvlTree::~AvlTree() {}

void AvlTree::addItem(Eclipse* myEclipse)
{
	//TODO //If no rootNode, add as rootNode. Else, add as regular node
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
				//balanceTree(insertNode);
				return;
			}
			recurseAdd(curNode->getRightChild(),myEclipse);
		}
		else //otherwise, myEclipse ID should be < curNode's key, so recurse left
		{
			if (curNode->getLeftChild() == 0) //insert here if left child is 0
			{
				
				curNode->setLeftChild(new TreeNode(curNode,myEclipse));

				//Now we check tree for re-balancing
				//balanceTree(insertNode);
				return;
			}
			recurseAdd(curNode->getLeftChild(),myEclipse);
		}
	}
}

void AvlTree::recurseAdd(TreeNode* curNode, Eclipse* myEclipse)
{





	if (myEclipse->getID() > curNode->getKey()) //if this occurs, recurse right
	{
		if (curNode->getRightChild() == 0) //insert here if right child is 0
		{

			curNode->setRightChild(new TreeNode(curNode,myEclipse));

			//Now we check tree for re-balancing
			//balanceTree(insertNode);
			return;
		}
		recurseAdd(curNode->getRightChild(),myEclipse);
	}
	else //otherwise, myEclipse ID should be < curNode's key, so recurse left
	{
		if (curNode->getLeftChild() == 0) //insert here if left child is 0
		{

			curNode->setLeftChild(new TreeNode(curNode,myEclipse));

			//Now we check tree for re-balancing
			//balanceTree(insertNode);
			return;
		}
		recurseAdd(curNode->getLeftChild(),myEclipse);
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

TreeNode* AvlTree::rotateTree(TreeNode* unbalNode)
{
	//TODO
}

TreeNode* AvlTree::rotateLeft(TreeNode* subHeadNode)
{
	//TODO
}

TreeNode* AvlTree::rotateRight(TreeNode* subHeadNode)
{
	//TODO
}

int AvlTree::maxDepth(TreeNode* subHeadNode)
{
	//TODO
}

int balanceFactorResult(TreeNode* subHeadNode)
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
	myTree->addItem(myEclipse4);
	myTree->addItem(myEclipse2);
	myTree->addItem(myEclipse5);
	myTree->addItem(myEclipse1);
	myTree->addItem(myEclipse3);
	myTree->addItem(myEclipse6);

	//myTree->printPreOrder();
	myTree->printInOrder();
	//myTree->printPostOrder();



	return 0;
}
//----------------------------------------------------------------

