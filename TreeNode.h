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
	TreeNode();
	TreeNode(Eclipse* myEclipse);
	TreeNode(TreeNode* parentNode,Eclipse* myEclipse);
	TreeNode(const TreeNode& oldNode);
	virtual ~TreeNode();
	void setParent(TreeNode* myParent);
	TreeNode* getParent();
	void setLeftChild(TreeNode* myLeftChild);
	TreeNode* getLeftChild();
	void setRightChild(TreeNode* myRightChild);
	TreeNode* getRightChild();
	void setEclipse(Eclipse* myEclipse);
	Eclipse* getEclipse();
	int getKey();
	void setKey(int myKey);
	void setBalanceFactor(int myBalanceFactor);
	int getBalanceFactor();
	TreeNode* operator=(const TreeNode& myNode);

private:
	TreeNode* parent; //points to parent Node, will be 0 for root node
	TreeNode* leftChild; //initialize left and right children to 0
	TreeNode* rightChild;
	Eclipse* eclipse; //main data held in TreeNode
	int key; //key for each node will be the Eclipse's ID number
	int balanceFactor; //upon insertion and deletion, re-do balanceFactor
};
//-------------------------------------------------------------
TreeNode::TreeNode() //used to make invalid node
{
	parent = 0;
	leftChild = 0;
	rightChild = 0;
	eclipse = new Eclipse();
	key = 0;
	balanceFactor = 0;
}

TreeNode::TreeNode(Eclipse* myEclipse) //used to initialize root node
{
	parent = 0;
	leftChild = 0;
	rightChild = 0;
	eclipse = myEclipse;
	key = eclipse->getID();
	balanceFactor = 0;
}

TreeNode::TreeNode(TreeNode* parentNode, Eclipse* myEclipse) //used to initialize all other nodes
{
	parent = parentNode;
	leftChild = 0;
	rightChild = 0;
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

TreeNode::TreeNode(const TreeNode& oldNode)
{
	this->balanceFactor = oldNode.balanceFactor;
	this->eclipse = oldNode.eclipse;
	this->key = oldNode.key;
	this->leftChild = oldNode.leftChild;
	this->parent = oldNode.parent;
	this->rightChild = oldNode.rightChild;
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

void TreeNode::setKey(int myKey)
{
	key = myKey;
}

TreeNode* TreeNode::operator=(const TreeNode& myNode)
{
	this->balanceFactor = myNode.balanceFactor;
	this->eclipse = myNode.eclipse;
	this->key = myNode.key;
	this->leftChild = myNode.leftChild;
	this->parent = myNode.parent;
	this->rightChild = myNode.rightChild;
	return this;
}
//-------------------------------------------------------------
#endif /* TREENODE_H_ */
