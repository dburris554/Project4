/*
 * AvlTree.h
 *
 *  Created on: Apr 10, 2018
 *      Author: david
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <TreeNode.h>

class AvlTree {

public:
	AvlTree();
	virtual ~AvlTree();
	void addItem(Eclipse* myEclipse);


private:
	TreeNode* balanceTree(TreeNode* insertedNode); //use balanceResult to determine rotation
	TreeNode* rotateTree(TreeNode* unbalNode); //call this for unbalanced Node in balanceTree
	TreeNode* rotateLeft(TreeNode* subHeadNode);
	TreeNode* rotateRight(TreeNode* subHeadNode);
	int maxDepth(TreeNode* subHeadNode); //call this on BalanceFactor's left and right child
	int balanceFactorResult(TreeNode* subHeadNode); //returns balance factor of Node
	TreeNode* rootNode;
};

#endif /* AVLTREE_H_ */
