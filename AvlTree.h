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
	void balanceTree(TreeNode* insertedNode); //use balanceResult to determine rotation
	TreeNode* rotateTree(TreeNode* unbalNode); //call this for unbalanced Node in balanceTree
	TreeNode* rotateLeft(TreeNode* subHeadNode);
	TreeNode* rotateRight(TreeNode* subHeadNode);
	int maxDepth(TreeNode* subHeadNode); //call this on BalanceFactor's left and right child
	void recurseAdd(TreeNode* curNode, Eclipse* myEclipse, bool &isAdded); //use to simplify addItem recursion
	int balanceFactorResult(TreeNode* subHeadNode); //returns balance factor of Node
	TreeNode* rootNode;
};

#endif /* AVLTREE_H_ */
