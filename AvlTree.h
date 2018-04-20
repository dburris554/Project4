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
	TreeNode* getFoundNode();
	void setFoundNode(TreeNode* myFoundNode);
	void removeItem(Eclipse* myEclipse); //you can remove a node with an eclipse or key
	Eclipse* findEclipse(int key);
	TreeNode* findNode(int key);
	TreeNode* findNodeForRemoval(int key);
	void printPreOrder();
	void printInOrder();
	void printPostOrder();
	void copyToArray(ResizeableArray<Eclipse>& myEclipses);

private:
	bool balanceTree(TreeNode* insertedNode); //use balanceResult to determine rotation
	void leftHeavyRotate(TreeNode* nodeA);
	void leftInnerRotate(TreeNode* nodeA);
	void rightHeavyRotate(TreeNode* nodeA);
	void rightInnerRotate(TreeNode* nodeA);
	void recurseAdd(TreeNode* curNode,TreeNode* insertNode, Eclipse* myEclipse, bool &hasRotated); //use to simplify addItem recursion
	void printPreOrder(TreeNode* curNode); //recurse print for pre-order
	void printInOrder(TreeNode* curNode); //recurse print in-order
	void printPostOrder(TreeNode* curNode); //recurse print post-order
	void copyToArray(ResizeableArray<Eclipse>& myEclipses, TreeNode* firstNode);
	void find(TreeNode* curNode, int key, bool &forRemoval);
	int computeBalanceFactor(TreeNode* myNode);
	void computeBalanceFactor(TreeNode* myNode, int &leftDepth, int &rightDepth);
	TreeNode* rootNode;
	TreeNode* foundNode;
};

#endif /* AVLTREE_H_ */
