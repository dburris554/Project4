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
	AvlTree(const AvlTree* oldTree); //deep copy constructor
	virtual ~AvlTree();
	AvlTree* operator=(const AvlTree* mytree); //corresponding assignment operator
	void addItem(Eclipse* myEclipse); //adds objects to tree
	TreeNode* getRootNode();
	TreeNode* getTempNode(); //tempNode allows simple coding for find and recursive calls
	void setTempNode(TreeNode* myTempNode);
	void removeItem(Eclipse* myEclipse); //use tempNode to call updateTree after removing item
	Eclipse* findEclipse(int key); //retrieve data from the tree with an Eclipse ID
	TreeNode* findNode(int key);
	void printPreOrder();
	void printInOrder(); //Prints are mainly for debugging
	void printPostOrder();
	void copyToArray(ResizeableArray<Eclipse>& myEclipses); //copy data in-order to Resizeable array
	void copyToTempTree(TreeNode* curNode); //temp tree is used to hold tree data while remaking the original
	void setTempTree(AvlTree* myTempTree);
	AvlTree* getTempTree();

private:
	void updateTree(TreeNode* insertedNode); //starts at inserted/deleted location, updates balanceFactors and checks for rotations back to rootNode
	void leftHeavyRotate(TreeNode* nodeA); //rotation when bF are 1 -> 2
	void leftInnerRotate(TreeNode* nodeA); //rotation when bF are -1 -> 2
	void rightHeavyRotate(TreeNode* nodeA); //rotation when bF are -1 -> -2
	void rightInnerRotate(TreeNode* nodeA); //rotation when bF are 1 -> -2
	void recurseAdd(TreeNode* curNode,TreeNode* insertNode, Eclipse* myEclipse); //use to simplify addItem recursion
	void printPreOrder(TreeNode* curNode); //recurse print for pre-order
	void printInOrder(TreeNode* curNode); //recurse print in-order
	void printPostOrder(TreeNode* curNode); //recurse print post-order
	void copyToArray(ResizeableArray<Eclipse>& myEclipses, TreeNode* firstNode); //see public method comment
	void find(TreeNode* curNode, int key); //finds a node matching the key and assigns it to tempNode
	int computeBalanceFactor(TreeNode* myNode); //uses left-max-depth and right-max-depth in real time
	void computeBalanceFactor(TreeNode* myNode, int &branchDepth); //recurse based on bF
	TreeNode* rootNode; //holds the root of the AvlTree
	TreeNode* tempNode; //holds nodes during find and recursive calls
	AvlTree* tempTree; //initialized and used when remaking the tree
};

#endif /* AVLTREE_H_ */
