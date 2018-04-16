/*
 * AvlTree.h
 *
 *  Created on: Apr 10, 2018
 *      Author: david
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "TreeNode.h"

class AvlTree {

public:
	AvlTree();
	virtual ~AvlTree();
	void addItem(Eclipse* myEclipse);
	TreeNode* getRootNode();
	void removeItem(Eclipse* myEclipse); //you can remove a node with an eclipse or key
	void removeItem(int key);
	Eclipse* findEclipse(int key);
	TreeNode* findNode(int key);
	void printPreOrder();
	void printInOrder();
	void printPostOrder();

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
	TreeNode* rootNode;
};

#endif /* AVLTREE_H_ */
