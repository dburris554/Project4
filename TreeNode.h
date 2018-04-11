/*
 * TreeNode.h
 *
 *  Created on: Apr 10, 2018
 *      Author: david
 */

#ifndef TREENODE_H_
#define TREENODE_H_

#include "Eclipse.h"

using namespace std;

class TreeNode {

public:
	TreeNode(Eclipse* myEclipse);
	TreeNode(TreeNode* parentNode,Eclipse* myEclipse);
	virtual ~TreeNode();
	void setParent(TreeNode* myParent);
	TreeNode* getParent();
	void setLeftChild(TreeNode* myLeftChild);
	TreeNode* getLeftChild();
	void setRightChild(TreeNode* myRightChild);
	TreeNode* getRightChild();
	void setSuccessor(TreeNode* mySuccessor);
	TreeNode* getSuccessor();
	void setEclipse(Eclipse* myEclipse);
	Eclipse* getEclipse();
	int getKey();
	void setBalanceFactor(int myBalanceFactor);
	int getBalanceFactor();

private:
	TreeNode* parent; //points to parent Node, will be 0 for root node
	TreeNode* leftChild; //initialize left and right children to 0
	TreeNode* rightChild;
	TreeNode* successor; //points to next node in-order of ID number, used for removal
	Eclipse* eclipse; //main data held in TreeNode
	int key; //key for each node will be the Eclipse's ID number
	int balanceFactor; //upon insertion and deletion, re-do balanceFactor
};
//-------------------------------------------------------------
TreeNode::TreeNode(Eclipse* myEclipse) //used to initialize root node
{
	parent = 0;
	leftChild = 0;
	rightChild = 0;
	successor = 0;
	eclipse = myEclipse;
	key = eclipse->getID();
	balanceFactor = 0;
}

TreeNode::TreeNode(TreeNode* parentNode, Eclipse* myEclipse) //used to initialize all other nodes
{
	parent = parentNode;
	leftChild = 0;
	rightChild = 0;
	successor = 0;
	eclipse = myEclipse;
	key = eclipse->getID();
	balanceFactor = 0;

	if (key > parent->getKey()) //if this Node's key is greater than parent's, assign as right child
	{
		parent->setRightChild(this);
	}
	else
	{
		parent->setLeftChild(this);
	}
}

TreeNode::~TreeNode() {}

void TreeNode::setParent(TreeNode* myParent)
{
	parent = myParent;
}

TreeNode* TreeNode::getParent()
{
	return parent;
}

void TreeNode::setLeftChild(TreeNode* myLeftChild)
{
	leftChild = myLeftChild;
}

TreeNode* TreeNode::getLeftChild()
{
	return leftChild;
}

void TreeNode::setRightChild(TreeNode* myRightChild)
{
	rightChild = myRightChild;
}

TreeNode* TreeNode::getRightChild()
{
	return rightChild;
}

void TreeNode::setSuccessor(TreeNode* mySuccessor)
{
	successor = mySuccessor;
}

TreeNode* TreeNode::getSuccessor()
{
	return successor;
}

void TreeNode::setEclipse(Eclipse* myEclipse)
{
	eclipse = myEclipse;
}

Eclipse* TreeNode::getEclipse()
{
	return eclipse;
}

int TreeNode::getKey()
{
	return key;
}

void TreeNode::setBalanceFactor(int myBalanceFactor)
{
	balanceFactor = myBalanceFactor;
}

int TreeNode::getBalanceFactor()
{
	return balanceFactor;
}
//-------------------------------------------------------------
#endif /* TREENODE_H_ */