/*
 * AvlTree.cpp
 *
 *  Created on: Apr 10, 2018
 *      Author: david
 */

#include "AvlTree.h"

AvlTree::AvlTree()
{
	rootNode = 0;
	tempNode = 0;
}

AvlTree::~AvlTree() {}

void AvlTree::addItem(Eclipse* myEclipse)
{
	//If no rootNode, add as rootNode. Else, add as regular node
	if (rootNode == 0)
	{
		rootNode = new TreeNode(myEclipse);
	}
	else //Find insertion location recursively and insert as non-root node
	{
		TreeNode* curNode = rootNode; //curNode will travel down the tree to find insertion location
		TreeNode* insertNode = new TreeNode(myEclipse); //insertNode will travel down the tree so balanceTree can be called
		
		if (myEclipse->getID() > curNode->getKey()) //if this occurs, recurse right
		{
			if (curNode->getRightChild() == 0) //insert here if right child is 0
			{
				curNode->setRightChild(new TreeNode(curNode,myEclipse)); //don't use insertNode here to avoid extra line
				curNode->setBalanceFactor(computeBalanceFactor(curNode)); //guaranteed no rotations will happen here
				return;
			}

			recurseAdd(curNode->getRightChild(),insertNode,myEclipse);
			//After right recursion return, update tree's bF's and rotations
			updateTree(insertNode);
		}
		else //otherwise, myEclipse ID should be < curNode's key, so recurse left
		{
			if (curNode->getLeftChild() == 0) //insert here if left child is 0
			{
				curNode->setLeftChild(new TreeNode(curNode,myEclipse)); //Don't use insertNode until recurseAdd
				curNode->setBalanceFactor(computeBalanceFactor(curNode)); //guaranteed no rotation will happen here
				return;
			}

			recurseAdd(curNode->getLeftChild(),insertNode,myEclipse);
			//After left recursion return, update tree's bF's and rotations
			updateTree(insertNode);
		}
	}
}

void AvlTree::recurseAdd(TreeNode* curNode, TreeNode* insertNode, Eclipse* myEclipse)
{
	if (myEclipse->getID() > curNode->getKey()) //if this occurs, recurse right
	{
		if (curNode->getRightChild() == 0) //insert here if right child is 0
		{
			curNode->setRightChild(insertNode); //when assigning insertNode, need to assign parent relation
			insertNode->setParent(curNode);
			return;
		}
		recurseAdd(curNode->getRightChild(),insertNode,myEclipse);

		return;
	}
	else //otherwise, myEclipse ID should be < curNode's key, so recurse left
	{
		if (curNode->getLeftChild() == 0) //insert here if left child is 0
		{
			curNode->setLeftChild(insertNode);
			insertNode->setParent(curNode);
			return;
		}
		recurseAdd(curNode->getLeftChild(),insertNode,myEclipse);

		return;
	}
}

TreeNode* AvlTree::getRootNode()
{
	return rootNode;
}

TreeNode* AvlTree::getTempNode()
{
	return tempNode;
}

void AvlTree::setTempNode(TreeNode* myFoundNode)
{
	tempNode = myFoundNode;
}

void AvlTree::removeItem(Eclipse* myEclipse)
{
	//3 removal cases: leaf node, node with 1 child, node with 2 children
	
	TreeNode* delNode = findNode(myEclipse->getID());
	if (delNode->getEclipse()->getIsBlank()) //If an invalid node, cerr and return
	{
		cerr << "Item with key " << myEclipse->getID() << " does not exist!" << endl;
		return;
	}
	
	//Leaf Node case
	if (delNode->getLeftChild() == 0 && delNode->getRightChild() == 0) //delNode is a leaf node
	{
		if (delNode->getParent() == 0) //delnode is the root
		{
			delNode = 0;
			rootNode = 0;
		}
		else //delnode has a parent
		{
			bool isLeftChild = false;
			if (delNode->getParent()->getLeftChild() != 0) //only compare with left child if it exists
			{
				isLeftChild = delNode->getKey() == delNode->getParent()->getLeftChild()->getKey();
			}

			if (isLeftChild) //delNode is a left child
			{
				delNode->getParent()->setLeftChild(0);
				tempNode = delNode->getParent();
				delNode = 0;
				updateTree(tempNode);
			}
			else //otherwise, delnode is a right child
			{
				delNode->getParent()->setRightChild(0);
				tempNode = delNode->getParent();
				delNode = 0;
				updateTree(tempNode);
			}
		}
	}
	
	//double child case
	else if (delNode->getLeftChild() != 0 && delNode->getRightChild() != 0) //delNode has two children
	{
		TreeNode* succNode = delNode->getRightChild(); //start the search for successor at delNode's right child and recurse left
		while (succNode->getLeftChild() != 0)
		{
			succNode = succNode->getLeftChild();
		}
		
		delNode->setKey(succNode->getKey());
		delNode->setEclipse(succNode->getEclipse()); //assign delNode with successor data

		bool isLeftChild = (succNode->getKey() == succNode->getParent()->getLeftChild()->getKey());
		//If succNode is a leaf node, delete leaf node and update tree
		if (succNode->getRightChild() == 0)
		{
			if (isLeftChild)
			{
				succNode->getParent()->setLeftChild(0);
			}
			else
			{
				succNode->getParent()->setRightChild(0);
			}
			tempNode = succNode->getParent();
			succNode = 0;
			updateTree(tempNode);
		}
		else //otherwise delete succNode as a has-right-child-and-parent case
		{
			TreeNode* parent = succNode->getParent();

			if (isLeftChild)
			{
				parent->setLeftChild(succNode->getRightChild());
				parent->getLeftChild()->setParent(parent);
			}
			else
			{
				parent->setRightChild(succNode->getRightChild());
				parent->getRightChild()->setParent(parent);
				//Parent to succNode-child relations have been formed, now delete succNode
				succNode = 0;
				updateTree(parent);
			}
		}
		
	}
	
	//single child case, only check if the child is left or right and if delNode has a parent
	else
	{
		bool hasLeftChild = (delNode->getLeftChild() != 0);
		
		if (delNode->getParent() == 0) //delNode is root
		{
			if (hasLeftChild)
			{
				rootNode = delNode->getLeftChild();
				delNode = 0;
				updateTree(rootNode);
			}
			else
			{
				rootNode = delNode->getRightChild();
				delNode = 0;
				updateTree(rootNode);
			}
		}
		else //delNode has a parent
		{
			bool isLeftChild = false;
			if (delNode->getParent()->getLeftChild() != 0) //only compare with left child if it exists
			{
				isLeftChild = delNode->getKey() == delNode->getParent()->getLeftChild()->getKey();
			}
			TreeNode* parent = delNode->getParent();

			if (isLeftChild) //if delNode is a left child...
			{
				if (hasLeftChild)
				{
					parent->setLeftChild(delNode->getLeftChild());
					parent->getLeftChild()->setParent(parent);
				}
				else
				{
					parent->setLeftChild(delNode->getRightChild());
					parent->getLeftChild()->setParent(parent);
				}
			}
			else //else delNode is a right child
			{
				if (hasLeftChild)
				{
					parent->setRightChild(delNode->getLeftChild());
					parent->getRightChild()->setParent(parent);
				}
				else
				{
					parent->setRightChild(delNode->getRightChild());
					parent->getRightChild()->setParent(parent);
				}
			}
			//Parent to delNode-child relations have been formed, now delete delNode
			delNode = 0;
			updateTree(parent);
		}
	}
}

Eclipse* AvlTree::findEclipse(int key) //will return an invalid Eclipse if not found
{
	TreeNode* curNode = rootNode;
	find(curNode,key);
	return tempNode->getEclipse();
}

TreeNode* AvlTree::findNode(int key) //will return an invalid TreeNode if not found
{
	TreeNode* curNode = rootNode;
	find(curNode,key);
	return tempNode;
}

void AvlTree::find(TreeNode* curNode, int key)
{
	if (curNode->getKey() < key) //first check to recurse right
	{
		if (curNode->getRightChild() != 0) //then make sure the right child exists
		{
			find(curNode->getRightChild(),key);
			return;
		}
	}
	else if (curNode->getKey() > key)//next check to recurse left
	{
		if (curNode->getLeftChild() != 0) //then check to see if left child exists
		{
			find(curNode->getLeftChild(),key);
			return;
		}
	}

	if (curNode->getKey() == key) //check if curNode is a match
	{
		tempNode = curNode;
	}
	else
	{
		tempNode = new TreeNode();
	}
	return;
}

int AvlTree::computeBalanceFactor(TreeNode* myNode) //Use this to calculate a new balanceFactor
{
	int leftDepth = 0;
	int rightDepth = 0;
	computeBalanceFactor(myNode,leftDepth,true);
	computeBalanceFactor(myNode,rightDepth,false);
	return (leftDepth - rightDepth);
}

void AvlTree::computeBalanceFactor(TreeNode* myNode, int &branchDepth, bool isLeftBranch)
{
	//first compute left depth. If either child are valid, keep going
	if (isLeftBranch)
	{
		while (myNode->getLeftChild() != 0 || myNode->getRightChild() != 0) //keep recursing as long as there is a valid child
		{
			if (myNode->getLeftChild() != 0)
			{
				branchDepth++;
				computeBalanceFactor(myNode->getLeftChild(),branchDepth,isLeftBranch);
				return;
			}

			if (branchDepth != 0 && myNode->getRightChild() != 0)
			{
				branchDepth++;
				computeBalanceFactor(myNode->getRightChild(),branchDepth,isLeftBranch);
				return;
			}
			return;
		}
	}

	//then compute right depth. If either child are valid, keep going
	else
	{
		while (myNode->getLeftChild() != 0 || myNode->getRightChild() != 0)
		{
			if (myNode->getRightChild() != 0)
			{
				branchDepth++;
				computeBalanceFactor(myNode->getRightChild(),branchDepth,isLeftBranch);
				return;
			}

			if (branchDepth != 0 && myNode->getLeftChild() != 0)
			{
				branchDepth++;
				computeBalanceFactor(myNode->getLeftChild(),branchDepth,isLeftBranch);
				return;
			}
			return;
		}
	}
}

void AvlTree::printPreOrder()
{
	printPreOrder(rootNode);
}

void AvlTree::printPreOrder(TreeNode* curNode)
{
	if (rootNode != 0)
	{
		cout << *(curNode->getEclipse());

		if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
		{
			printPreOrder(curNode->getLeftChild());
		}

		if (curNode->getRightChild() != 0) //only check right subtrees if not 0
		{
			printPreOrder(curNode->getRightChild());
		}
	}
}

void AvlTree::printInOrder()
{
	printInOrder(rootNode);
}

void AvlTree::printInOrder(TreeNode* curNode)
{
	if (rootNode != 0)
	{
		if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
		{
			printInOrder(curNode->getLeftChild());
		}

		cout << *(curNode->getEclipse());

		if (curNode->getRightChild() != 0) //only check right subtrees if not 0
		{
			printInOrder(curNode->getRightChild());
		}
	}
}

void AvlTree::printPostOrder()
{
	printPostOrder(rootNode);
}

void AvlTree::printPostOrder(TreeNode* curNode)
{
	if (rootNode != 0)
	{
		if (curNode->getLeftChild() != 0) //only check left subtrees if not 0
		{
			printPostOrder(curNode->getLeftChild());
		}

		if (curNode->getRightChild() != 0) //only check right subtrees if not 0
		{
			printPostOrder(curNode->getRightChild());
		}

		cout << *(curNode->getEclipse());
	}
}

void AvlTree::copyToArray(ResizeableArray<Eclipse> &myEclipses)
{
	copyToArray(myEclipses,rootNode);
}

void AvlTree::copyToArray(ResizeableArray<Eclipse> &myEclipses, TreeNode* firstNode)
{
	if (firstNode->getLeftChild() != 0) //only check left subtrees if not 0
	{
		copyToArray(myEclipses,firstNode->getLeftChild());
	}

	myEclipses.Add(*(firstNode->getEclipse()));

	if (firstNode->getRightChild() != 0) //only check right subtrees if not 0
	{
		copyToArray(myEclipses,firstNode->getRightChild());
	}
}

void AvlTree::updateTree(TreeNode* insertedNode) //start from insertion, travel up the parents to check for rotation cases
{
	TreeNode* curNode = insertedNode; //we start at the node that was added/removed
	curNode->setBalanceFactor(computeBalanceFactor(curNode));
	bool hasLeftChild = (insertedNode->getLeftChild() != 0);

	if (abs(insertedNode->getBalanceFactor()) == 2 && (insertedNode->getLeftChild() != 0 || insertedNode->getRightChild() != 0))
	//special case during removal @ delNode's parent where we should start at sibling
	{
		if (hasLeftChild)
		{
			tempNode = insertedNode->getLeftChild();
			updateTree(tempNode);
			return;
		}
		else //otherwise, insertedNode has a right child
		{
			tempNode = insertedNode->getRightChild();
			updateTree(tempNode);
			return;
		}
	}	//above will restart at the node that will catch the rotation

	while (curNode->getParent() != 0) //continue updating and checking rotations until you reach the head node
	{
		curNode->getParent()->setBalanceFactor(computeBalanceFactor(curNode->getParent())); //update parent's bF before checking for rotation

		//Test for Left-Heavy rotation
		if (curNode->getBalanceFactor() == 1 && curNode->getParent()->getBalanceFactor() == 2)
		{
			leftHeavyRotate(curNode->getParent()); //rotate on sub-head node, return hasRotated
			return;
		}
		//Test for Left-Inner rotation
		else if (curNode->getBalanceFactor() == -1 && curNode->getParent()->getBalanceFactor() == 2)
		{
			leftInnerRotate(curNode->getParent()); //rotate on sub-head node, return hasRotated
			return;
		}
		//Test for Right-Heavy rotation
		else if (curNode->getBalanceFactor() == -1 && curNode->getParent()->getBalanceFactor() == -2)
		{
			rightHeavyRotate(curNode->getParent()); //rotate on sub-head node, return hasRotated
			return;
		}
		//Test for Right-Inner rotation
		else if (curNode->getBalanceFactor() == 1 && curNode->getParent()->getBalanceFactor() == -2)
		{
			rightInnerRotate(curNode->getParent()); //rotate on sub-head node, return hasRotated
			return;
		}
		//recurse up to the next parent
		curNode = curNode->getParent();
	}
	return;
}

void AvlTree::leftHeavyRotate(TreeNode* nodeA)
{
	bool isRoot = (nodeA->getParent() == 0); //edge case is that nodeA is the root
	TreeNode* parentOfA;
	bool isLeftChild; //check whether nodeA is a left child
	if (!isRoot)
	{
		parentOfA = nodeA->getParent();
		if (parentOfA->getLeftChild()->getKey() == nodeA->getKey())
		{
			isLeftChild = true;
		}
		else (isLeftChild = false);
	}
	TreeNode* nodeB = nodeA->getLeftChild();
	TreeNode* rcOfB = nodeB->getRightChild();

	nodeB->setRightChild(nodeA);
	nodeA->setParent(nodeB);
	nodeA->setLeftChild(rcOfB);
	if (rcOfB != 0) //only assign if it exists
	{
		rcOfB->setParent(nodeA);
	}

	if (!isRoot)
	{
		nodeB->setParent(parentOfA);

		if (isLeftChild)
		{
			parentOfA->setLeftChild(nodeB);
		}
		else
		{
			parentOfA->setRightChild(nodeB);
		}
	}
	else //otherwise, assign nodeB's parent as 0, and nodeB is now the root
	{
		nodeB->setParent(0);
		rootNode = nodeB;
	}

	nodeA->setBalanceFactor(0);
	nodeB->setBalanceFactor(0);
}

void AvlTree::leftInnerRotate(TreeNode* nodeA)
{
	bool isRoot = (nodeA->getParent() == 0); //edge case is that nodeA is the root
	TreeNode* parentOfA;
	bool isLeftChild; //check whether nodeA is a left child
	if (!isRoot)
	{
		parentOfA = nodeA->getParent();
		if (parentOfA->getLeftChild()->getKey() == nodeA->getKey())
		{
			isLeftChild = true;
		}
		else (isLeftChild = false);
	}
	TreeNode* nodeB = nodeA->getLeftChild();
	TreeNode* nodeC = nodeB->getRightChild(); //after rotation, check if nodeC is the new root
	TreeNode* lcOfC = nodeC->getLeftChild();
	TreeNode* rcOfC = nodeC->getRightChild();

	nodeC->setLeftChild(nodeB);
	nodeB->setParent(nodeC);
	nodeC->setRightChild(nodeA);
	nodeA->setParent(nodeC);
	nodeB->setRightChild(lcOfC);
	if (lcOfC != 0) //only assign if exists
	{
		lcOfC->setParent(nodeB);
	}
	nodeA->setLeftChild(rcOfC);
	if (rcOfC != 0) //only assign if exists
	{
		rcOfC->setParent(nodeA);
	}

	if (!isRoot)
	{
		nodeC->setParent(parentOfA);

		if (isLeftChild)
		{
			parentOfA->setLeftChild(nodeC);
		}
		else
		{
			parentOfA->setRightChild(nodeC);
		}
	}
	else //nodeC is the new root
	{
		nodeC->setParent(0);
		rootNode = nodeC;
	}

	nodeA->setBalanceFactor(0);
	nodeB->setBalanceFactor(0);
	nodeC->setBalanceFactor(0);
}

void AvlTree::rightHeavyRotate(TreeNode* nodeA) //In this case, only nodeA, nodeA's parent, nodeB, and B's left child need reassigning
{
	bool isRoot = (nodeA->getParent() == 0); //Edge case is that nodeA is the tree's root
	TreeNode* parentOfA;
	bool isRightChild; //Because we don't know if nodeA is a left or right child, do a check at runtime
	if (!isRoot)
	{
		parentOfA = nodeA->getParent();
		if (parentOfA->getRightChild()->getKey() == nodeA->getKey())
		{
			isRightChild = true;
		}
		else (isRightChild = false);
	}
	TreeNode* nodeB = nodeA->getRightChild();
	TreeNode* lcOfB = nodeB->getLeftChild();

	nodeB->setLeftChild(nodeA); //re-assign nodes
	nodeA->setParent(nodeB);
	nodeA->setRightChild(lcOfB);
	if (lcOfB != 0)
	{
		lcOfB->setParent(nodeA); //Only point B's left child to A if child exists
	}

	if (!isRoot) //If nodeA is not the root, assign nodeB's parent and nodeA's parent's child
	{
		nodeB->setParent(parentOfA);

		if (isRightChild)
		{
			parentOfA->setRightChild(nodeB);
		}
		else
		{
			parentOfA->setLeftChild(nodeB);
		}
	}
	else //otherwise, assign nodeB's parent as 0, and nodeB is now the root
	{
		nodeB->setParent(0);
		rootNode = nodeB;
	}

	nodeA->setBalanceFactor(0); //Reset balance factors of main nodes of the rotation
	nodeB->setBalanceFactor(0);
}

void AvlTree::rightInnerRotate(TreeNode* nodeA)
{
	bool isRoot = (nodeA->getParent() == 0); //edge case is that nodeA is the root
	TreeNode* parentOfA;
	bool isRightChild; //check whether nodeA is a left child
	if (!isRoot)
	{
		parentOfA = nodeA->getParent();
		if (parentOfA->getLeftChild()->getKey() == nodeA->getKey())
		{
			isRightChild = true;
		}
		else (isRightChild = false);
	}
	TreeNode* nodeB = nodeA->getRightChild();
	TreeNode* nodeC = nodeB->getLeftChild();
	TreeNode* lcOfC = nodeC->getLeftChild();
	TreeNode* rcOfC = nodeC->getRightChild();

	nodeC->setLeftChild(nodeA);
	nodeA->setParent(nodeC);
	nodeC->setRightChild(nodeB);
	nodeB->setParent(nodeC);
	nodeA->setRightChild(lcOfC);
	if (lcOfC != 0) //if exists, assign
	{
		lcOfC->setParent(nodeA);
	}
	nodeB->setLeftChild(rcOfC);
	if (rcOfC != 0) //only assign if exists
	{
		rcOfC->setParent(nodeB);
	}

	if (!isRoot)
	{
		nodeC->setParent(parentOfA);

		if (isRightChild)
		{
			parentOfA->setRightChild(nodeC);
		}
		else
		{
			parentOfA->setLeftChild(nodeC);
		}
	}
	else //nodeC is the new root
	{
		nodeC->setParent(0);
		rootNode = nodeC;
	}

	nodeA->setBalanceFactor(0);
	nodeB->setBalanceFactor(0);
	nodeC->setBalanceFactor(0);
}
//----------------------------------------------------------------
int main() {
	string* myString1 = new string[18];
	string* myString2 = new string[18];
	string* myString3 = new string[18];
	string* myString4 = new string[18];
	string* myString5 = new string[18];
	string* myString6 = new string[18];
	string* myString7 = new string[18];
	string* myString8 = new string[18];
	string* myString9 = new string[18];
	string* myString10 = new string[18];
	string* myString11 = new string[18];
	string* myString12 = new string[18];
	for (int i = 0; i < 18; i++)
	{
		myString1[i] = "1";
		myString2[i] = "2";
		myString3[i] = "3";
		myString4[i] = "4";
		myString5[i] = "5";
		myString6[i] = "6";
		myString7[i] = "7";
		myString8[i] = "8";
		myString9[i] = "9";
		myString10[i] = "10";
		myString11[i] = "11";
		myString12[i] = "12";
	}
	Eclipse* myEclipse1 = new Eclipse(myString1);
	Eclipse* myEclipse2 = new Eclipse(myString2);
	Eclipse* myEclipse3 = new Eclipse(myString3);
	Eclipse* myEclipse4 = new Eclipse(myString4);
	Eclipse* myEclipse5 = new Eclipse(myString5);
	Eclipse* myEclipse6 = new Eclipse(myString6);
	Eclipse* myEclipse7 = new Eclipse(myString7);
	Eclipse* myEclipse8 = new Eclipse(myString8);
	Eclipse* myEclipse9 = new Eclipse(myString9);
	Eclipse* myEclipse10 = new Eclipse(myString10);
	Eclipse* myEclipse11 = new Eclipse(myString11);
	Eclipse* myEclipse12 = new Eclipse(myString12);

	AvlTree* myTree = new AvlTree();
	myTree->addItem(myEclipse1);
	myTree->addItem(myEclipse3);
	myTree->addItem(myEclipse5);
	myTree->addItem(myEclipse7);
	myTree->addItem(myEclipse9);
	myTree->addItem(myEclipse11);
	myTree->addItem(myEclipse12);
	myTree->addItem(myEclipse2);
	myTree->addItem(myEclipse4);
	myTree->addItem(myEclipse10);
	myTree->addItem(myEclipse6);
	myTree->addItem(myEclipse8);

	cout << "Printing Pre-Order..." << endl;
	myTree->printPreOrder();
	/*cout << "Printing In-Order..." << endl;
	myTree->printInOrder();
	cout << "Printing Post-Order..." << endl;
	myTree->printPostOrder();*/

	cout << "Deleting nodes..." << endl;
	myTree->removeItem(myEclipse2);
	myTree->removeItem(myEclipse4);
	myTree->removeItem(myEclipse6);
	myTree->removeItem(myEclipse12);
	myTree->removeItem(myEclipse10);
	myTree->removeItem(myEclipse8);
	myTree->removeItem(myEclipse10);

	cout << "Re-printing Pre-Order..." << endl;
	myTree->printPreOrder();

	cout << "Done.";



	return 0;
}
//----------------------------------------------------------------

