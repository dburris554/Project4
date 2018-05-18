/*
 * TreeNode.h
 *
 *  Created on: Apr 10, 2018
 *      Author: david
 */

#ifndef TREENODE_H_
#define TREENODE_H_

using namespace std;

template<typename TheType>
class TreeNode {

public:
	TreeNode();
	TreeNode(TheType* myObject,int theKey);
	TreeNode(TreeNode* parentNode,TheType* myObject,int theKey);
	TreeNode(const TreeNode& oldNode);
	virtual ~TreeNode();
	void setParent(TreeNode* myParent);
	TreeNode* getParent();
	void setLeftChild(TreeNode* myLeftChild);
	TreeNode* getLeftChild();
	void setRightChild(TreeNode* myRightChild);
	TreeNode* getRightChild();
	void setData(TheType* object);
	TheType* getData();
	int getKey();
	void setKey(int myKey);
	void setBalanceFactor(int myBalanceFactor);
	int getBalanceFactor();
	TreeNode* operator=(const TreeNode& myNode);

private:
	TreeNode* parent; //points to parent Node, will be 0 for root node
	TreeNode* leftChild; //initialize left and right children to 0
	TreeNode* rightChild;
	TheType* myData; //main data held in TreeNode
	int key; //key for each node will be the Eclipse's ID number
	int balanceFactor; //upon insertion and deletion, re-do balanceFactor
};

template<typename TheType>
TreeNode<TheType>::TreeNode() //used to make invalid node
{
	parent = 0;
	leftChild = 0;
	rightChild = 0;
	myData = new TheType();
	key = 0;
	balanceFactor = 0;
}

template<typename TheType>
TreeNode<TheType>::TreeNode(TheType* myObject, int theKey) //used to initialize root node
{
	parent = 0;
	leftChild = 0;
	rightChild = 0;
	myData = myObject;
	key = theKey;
	balanceFactor = 0;
}

template<typename TheType>
TreeNode<TheType>::TreeNode(TreeNode* parentNode, TheType* myObject, int theKey) //used to initialize all other nodes
{
	parent = parentNode;
	leftChild = 0;
	rightChild = 0;
	myData = myObject;
	key = theKey;
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

template<typename TheType>
TreeNode<TheType>::TreeNode(const TreeNode& oldNode)
{
	this->balanceFactor = oldNode.balanceFactor;
	this->myData = oldNode.myData;
	this->key = oldNode.key;
	this->leftChild = oldNode.leftChild;
	this->parent = oldNode.parent;
	this->rightChild = oldNode.rightChild;
}

template<typename TheType>
TreeNode<TheType>::~TreeNode() {}

template<typename TheType>
void TreeNode<TheType>::setParent(TreeNode* myParent)
{
	parent = myParent;
}

template<typename TheType>
TreeNode<TheType>* TreeNode<TheType>::getParent()
{
	return parent;
}

template<typename TheType>
void TreeNode<TheType>::setLeftChild(TreeNode* myLeftChild)
{
	leftChild = myLeftChild;
}

template<typename TheType>
TreeNode<TheType>* TreeNode<TheType>::getLeftChild()
{
	return leftChild;
}

template<typename TheType>
void TreeNode<TheType>::setRightChild(TreeNode* myRightChild)
{
	rightChild = myRightChild;
}

template<typename TheType>
TreeNode<TheType>* TreeNode<TheType>::getRightChild()
{
	return rightChild;
}

template<typename TheType>
void TreeNode<TheType>::setData(TheType* theData)
{
	myData = theData;
}

template<typename TheType>
TheType* TreeNode<TheType>::getData()
{
	return myData;
}

template<typename TheType>
int TreeNode<TheType>::getKey()
{
	return key;
}

template<typename TheType>
void TreeNode<TheType>::setBalanceFactor(int myBalanceFactor)
{
	balanceFactor = myBalanceFactor;
}

template<typename TheType>
int TreeNode<TheType>::getBalanceFactor()
{
	return balanceFactor;
}

template<typename TheType>
void TreeNode<TheType>::setKey(int myKey)
{
	key = myKey;
}

template<typename TheType>
TreeNode<TheType>* TreeNode<TheType>::operator=(const TreeNode& myNode)
{
	this->balanceFactor = myNode.balanceFactor;
	this->myData = myNode.myData;
	this->key = myNode.key;
	this->leftChild = myNode.leftChild;
	this->parent = myNode.parent;
	this->rightChild = myNode.rightChild;
	return this;
}

#endif /* TREENODE_H_ */
