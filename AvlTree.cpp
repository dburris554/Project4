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
	if (rootNode == 0)
	{
		rootNode = new TreeNode(myEclipse);
	}
	else //Find insertion location recursively and insert as non-root node
	{
		TreeNode* curNode = rootNode;
		bool isAdded = false;
		if (myEclipse->getID() > curNode->getKey()) //if this occurs, recurse right
		{
			if (curNode->getRightChild() == 0) //insert here if right child is 0
			{
				TreeNode* insertNode = new TreeNode(curNode,myEclipse);
				curNode->setRightChild(insertNode);
				isAdded = true;
				//Now we check tree for re-balancing
				balanceTree(insertNode);
				return;
			}
			recurseAdd(curNode,myEclipse,isAdded);
		}
		else //otherwise, myEclipse ID should be < curNode's key, so recurse left
		{
			if (curNode->getLeftChild() == 0) //insert here if left child is 0
			{
				TreeNode* insertNode = new TreeNode(curNode,myEclipse);
				curNode->setLeftChild(insertNode);
				isAdded = true;
				//Now we check tree for re-balancing
				balanceTree(insertNode);
				return;
			}
			recurseAdd(curNode,myEclipse,isAdded);
		}
	}
}

void AvlTree::recurseAdd(TreeNode* curNode, Eclipse* myEclipse, bool &isAdded)
{
	if (isAdded)
	{
		return;
	}
	TreeNode* insertNode;
	if (myEclipse->getID() > curNode->getKey()) //if this occurs, recurse right
	{
		if (curNode->getRightChild() == 0) //insert here if right child is 0
		{
			insertNode = new TreeNode(curNode,myEclipse);
			curNode->setRightChild(insertNode);
			isAdded = true;
			//Now we check tree for re-balancing
			balanceTree(insertNode);
			return;
		}
		recurseAdd(curNode,myEclipse,isAdded);
	}
	else //otherwise, myEclipse ID should be < curNode's key, so recurse left
	{
		if (curNode->getLeftChild() == 0) //insert here if left child is 0
		{
			insertNode = new TreeNode(curNode,myEclipse);
			curNode->setLeftChild(insertNode);
			isAdded = true;
			//Now we check tree for re-balancing
			balanceTree(insertNode);
			return;
		}
		recurseAdd(curNode,myEclipse,isAdded);
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
	//TODO
}

void AvlTree::printInOrder()
{
	//TODO
}

void AvlTree::printPostOrder()
{
	//TODO
}

void AvlTree::balanceTree(TreeNode* insertedNode)
{
	//TODO
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
	AvlTree myTree();

	return 0;
}
//----------------------------------------------------------------

