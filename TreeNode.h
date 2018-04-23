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
	//void incrementHeight(); //TODO
	//void decrementHeight(); //TODO
	//int getHeight(); //TODO
	TreeNode* operator=(const TreeNode& myNode);

private:
	TreeNode* parent; //points to parent Node, will be 0 for root node
	TreeNode* leftChild; //initialize left and right children to 0
	TreeNode* rightChild;
	Eclipse* eclipse; //main data held in TreeNode
	int key; //key for each node will be the Eclipse's ID number
	int balanceFactor; //upon insertion and deletion, re-do balanceFactor
	//int height; //allows easy and quick balance factor updates //TODO
};

#endif /* TREENODE_H_ */
