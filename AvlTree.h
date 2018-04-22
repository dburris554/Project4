/*
 * AvlTree.h
 *
 *  Created on: Apr 10, 2018
 *      Author: david
 */

#include "TreeNode.h"
#include "ResizeableArray.h"

#ifndef AVLTREE_H_
#define AVLTREE_H_

class AvlTree {

public:
	AvlTree();
	virtual ~AvlTree();
	void addItem(Eclipse* myEclipse);
	TreeNode* getRootNode();
	TreeNode* getTempNode();
	void setTempNode(TreeNode* myTempNode);
	void removeItem(Eclipse* myEclipse); //use tempNode to call updateTree after removing item
	Eclipse* findEclipse(int key);
	TreeNode* findNode(int key);
	void printPreOrder();
	void printInOrder();
	void printPostOrder();
	void copyToArray(ResizeableArray<Eclipse>& myEclipses);

private:
	void updateTree(TreeNode* insertedNode); //starts at inserted/deleted location, updates balanceFactors and checks for rotations back to rootNode
	void leftHeavyRotate(TreeNode* nodeA);
	void leftInnerRotate(TreeNode* nodeA);
	void rightHeavyRotate(TreeNode* nodeA);
	void rightInnerRotate(TreeNode* nodeA);
	void recurseAdd(TreeNode* curNode,TreeNode* insertNode, Eclipse* myEclipse); //use to simplify addItem recursion
	void printPreOrder(TreeNode* curNode); //recurse print for pre-order
	void printInOrder(TreeNode* curNode); //recurse print in-order
	void printPostOrder(TreeNode* curNode); //recurse print post-order
	void copyToArray(ResizeableArray<Eclipse>& myEclipses, TreeNode* firstNode);
	void find(TreeNode* curNode, int key);
	int computeBalanceFactor(TreeNode* myNode);
	void computeBalanceFactor(TreeNode* myNode, int &branchDepth, bool isLeftBranch); //resolve infinite loop here
	TreeNode* rootNode;
	TreeNode* tempNode;
};

#endif /* AVLTREE_H_ */
