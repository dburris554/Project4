/*
 * TreeNode.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: david
 */

#include "TreeNode.h"

TreeNode::TreeNode() //used to make invalid node
{
	parent = 0;
	leftChild = 0;
	rightChild = 0;
	eclipse = new Eclipse();
	key = 0;
	balanceFactor = 0;
	//height = 0; //TODO
}

TreeNode::TreeNode(Eclipse* myEclipse) //used to initialize root node
{
	parent = 0;
	leftChild = 0;
	rightChild = 0;
	eclipse = myEclipse;
	key = eclipse->getID();
	balanceFactor = 0;
	//height = 0; //TODO
}

TreeNode::TreeNode(TreeNode* parentNode, Eclipse* myEclipse) //used to initialize all other nodes
{
	parent = parentNode;
	leftChild = 0;
	rightChild = 0;
	eclipse = myEclipse;
	key = eclipse->getID();
	balanceFactor = 0;
	//height = 0; //TODO

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
	//this->height = oldNode.height; //TODO
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

/*void TreeNode::incrementHeight() //TODO
{
	height++;
}*/

/*void TreeNode::decrementHeight() //TODO
{
	height--;
}*/

/*int TreeNode::getHeight() //TODO
{
	return height;
}*/

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


