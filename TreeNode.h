/*
 * TreeNode.h
 *
 *  Created on: Apr 10, 2018
 *      Author: david
 */

#ifndef TREENODE_H_
#define TREENODE_H_

#include <Eclipse.h>

using namespace std;

class TreeNode {

public:
	TreeNode();
	virtual ~TreeNode();

private:
	TreeNode* parent; //points to parent Node, will be 0 for root node
	TreeNode* leftChild; //initialize left and right children to 0
	TreeNode* rightChild;
	TreeNode* successor; //points to next node in-order of ID number (key)
	Eclipse* myEclipse; //main data held in TreeNode
	int key; //key for each node will be the Eclipse's ID number
	int balanceFactor; //upon insertion and deletion, re-do balanceFactor
};
//-------------------------------------------------------------


//-------------------------------------------------------------
#endif /* TREENODE_H_ */
