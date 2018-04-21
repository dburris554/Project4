/*
 * AvlTree.h
 *
 *  Created on: Apr 10, 2018
 *      Author: david
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "TreeNode.h"
#include "ResizeableArray.h"

class AvlTree {

public:
	AvlTree();
	virtual ~AvlTree();
	void addItem(Eclipse* myEclipse);
	TreeNode* getRootNode();
	TreeNode* getFoundNode(); //refactor to TempNode
	void setFoundNode(TreeNode* myFoundNode); //refactor to tempNode
	void removeItem(Eclipse* myEclipse); //use tempNode to call updateTree after removing item
	Eclipse* findEclipse(int key);
	TreeNode* findNode(int key);
	void printPreOrder();
	void printInOrder();
	void printPostOrder();
	void copyToArray(ResizeableArray<Eclipse>& myEclipses);

private:
	bool balanceTree(TreeNode* insertedNode); //starts at inserted/deleted location, updates balanceFactors and checks for rotations back to rootNode
	void leftHeavyRotate(TreeNode* nodeA);
	void leftInnerRotate(TreeNode* nodeA);
	void rightHeavyRotate(TreeNode* nodeA);
	void rightInnerRotate(TreeNode* nodeA);
	void recurseAdd(TreeNode* curNode,TreeNode* insertNode, Eclipse* myEclipse, bool &hasRotated); //use to simplify addItem recursion
	void printPreOrder(TreeNode* curNode); //recurse print for pre-order
	void printInOrder(TreeNode* curNode); //recurse print in-order
	void printPostOrder(TreeNode* curNode); //recurse print post-order
	void copyToArray(ResizeableArray<Eclipse>& myEclipses, TreeNode* firstNode);
	void find(TreeNode* curNode, int key, bool &forRemoval); //make sure this is updated
	int computeBalanceFactor(TreeNode* myNode);
	void computeBalanceFactor(TreeNode* myNode, int &leftDepth, int &rightDepth); //resolve infinite loop here
	TreeNode* rootNode;
	TreeNode* foundNode; //refactor this to tempNode
};

#endif /* AVLTREE_H_ */
