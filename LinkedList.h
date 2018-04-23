/*
 * LinkedList.h
 *
 *  Created on: Mar 13, 2018
 *      Author: david
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Eclipse.h"
#include "ResizeableArray.h"

using namespace std;

struct Node //Instead of making a class for a node in the Linked List, use a struct
	{
		Eclipse* data; //Node contains a single Eclipse object pointer
		Node* next; //Node also contains a pointer to the next node in the list
		Node(Eclipse* myEclipse)
		{
			data = myEclipse; //Upon construction, take an arg for the Eclipse pointer and set the pointer to 0
			next = 0;
		}

		Node(const Node& oldNode) //copies pointers of one node to another
		{
			this->data = oldNode.data;
			this->next = oldNode.next;
		}

		Node* operator=(const Node& myNode) //allows '=' to copy one node to another
		{
			this->data = myNode.data;
			this->next = myNode.next;
			return this;
		}
	};

class LinkedList {

public:
	struct Node //Instead of making a class for a node in the Linked List, use a struct
	{
		Eclipse* data; //Node contains a single Eclipse object pointer
		Node* next; //Node also contains a pointer to the next node in the list
		Node(Eclipse* myEclipse)
		{
			data = myEclipse; //Upon construction, take an arg for the Eclipse pointer and set the pointer to 0
			next = 0;
		}

		Node(const Node& oldNode) //copies pointers of one node to another
		{
			this->data = oldNode.data;
			this->next = oldNode.next;
		}

		Node* operator=(const Node& myNode) //allows '=' to copy one node to another
		{
			this->data = myNode.data;
			this->next = myNode.next;
			return this;
		}
	};
	LinkedList();
	LinkedList(ResizeableArray<Eclipse>& myEclipses, Eclipse* tempEclipse);
	LinkedList(LinkedList& myList);
	virtual ~LinkedList();
	LinkedList* operator=(const LinkedList& myList);
	Node* operator=(const Node& myNode);
	int mergeAdd(Eclipse* object);
	void purgeRemove(Eclipse* object);
	void append(Eclipse* object);
	void prepend(Eclipse* object);
	void insertAfter(Node* curNode, Eclipse* object);
	void removeAfter(Node* curNode);
	void removeAt(int index);
	void print();
	void sort();
	bool isEmpty();
	Eclipse getHeadData();
	Eclipse getTailData();
	LinkedList::Node* getHeadNode();
	LinkedList::Node* getTailNode();
	void setHeadNode(LinkedList::Node*);
	void setTailNode(LinkedList::Node*);
	void setNumItems(int myNumItems);
	int getLength();
	void copyToArray(ResizeableArray<Eclipse>& myEclipses);

private:
	Node* head;
	Node* tail;
	int numItems;
};
//**************************************************************************************************
LinkedList::LinkedList() //LinkedList will always be created with blank pointers and no items
{
	head = 0;
	tail = 0;
	numItems = 0;
}

LinkedList::LinkedList(ResizeableArray<Eclipse>& myEclipses, Eclipse* tempEclipse)
{
	head = 0;
	tail = 0;
	numItems = 0;

	for (int i = 0; i < myEclipses.getNumItems(); i++)
	{
		tempEclipse = new Eclipse(myEclipses[i]);
		append(tempEclipse);
	}
}

LinkedList::~LinkedList() {}

LinkedList::LinkedList(LinkedList& myList)
{
	head = myList.head;
	tail = myList.tail;
	numItems = myList.numItems;
}

LinkedList* LinkedList::operator=(const LinkedList& myList)
{
	head = myList.head;
	tail = myList.tail;
	numItems = myList.numItems;
	return this;
}

int LinkedList::mergeAdd(Eclipse* object) //adds incoming Eclipses in order by ID number, returns 1 if duplicate
{
	int dupEntries = 0; //Set default number of duplicates to 0
	Node* myNode = new Node(object); //myNode is the node to mergeAdd
	Node* curNode = head; //set curNode to point at the head of the list

	if (numItems == 0) //Add the first node
	{
		tail = myNode;
		head = myNode;
		numItems++;
		return dupEntries;
	}
	else if (curNode->data->compareId(object) == 1) //If curNodeID > objectID, insert before the head
	{
		myNode->next = head;
		head = myNode;
		numItems++;
		return dupEntries;
	}
	else if (curNode->data->compareId(object) == 0) //Evaluates true if equal, then replaces head
	{
		myNode->next = head->next;
		delete head;
		head = myNode;
		dupEntries++;
		return dupEntries;
	}

	if (numItems == 1 && curNode->data->compareId(object) == -1) //If object needs to go after the only node, append
	{
		tail->next = myNode;
		tail = myNode;
		numItems++;
		return dupEntries;
	}

	do //check if new Node is equal to another, and compare ID's to find sorted location
	{
		if (curNode->next->data->compareId(object) == 0) //Evaluates true if equivalent ID's, replace
		{
			myNode->next = curNode->next->next;
			delete curNode->next;
			curNode->next = myNode;
			if (curNode->next->next == 0) //If replacing the tail, assign the tail
			{
				tail = myNode;
			}
			dupEntries++;
			return dupEntries;
		}
		else if (curNode->next->data->compareId(object) == 1) //If object ID < curNode.next ID, insert
		{
			myNode->next = curNode->next;
			curNode->next = myNode;
			numItems++;
			return dupEntries;
		}
		curNode = curNode->next;
	} while (curNode->next != 0);

	//In this case, the curNode points to the tail, and the objectID > all nodes in myList, then append
	tail->next = myNode;
	tail = myNode;
	numItems++;
	return dupEntries;
}

void LinkedList::purgeRemove(Eclipse* object) //Takes an incoming object's ID and removes it from the database if found
{
	Node* curNode = head;

	if (curNode->data->compareId(object) == 0) //Evaluates true if equal, then delete head
	{
		curNode = head->next;
		delete head;
		head = curNode;
		numItems--;
		return;
	}

	while (curNode->next != 0 && curNode->data->compareId(object) == -1)
	{
		if (curNode->next->data->compareId(object) == 0) //If Equal, remove curNode.next
		{
			Node* tempNode = curNode->next->next;
			delete curNode->next;
			curNode->next = tempNode;
			numItems--;
			return;
		}
		curNode = curNode->next;
	}
	//Otherwise, declare Eclipse not found in the list
	cerr << "Eclipse catalog number " << object->getVal(0) << " not found." << endl;
	return;
}

void LinkedList::append(Eclipse* object)
{
	Node* myNode = new Node(object);
	if (head == 0)
	{
		head = myNode;
	}
	else
	{
		tail->next = myNode;
	}
	tail = myNode;
	numItems++;
}

void LinkedList::prepend(Eclipse* object)
{
	Node* myNode = new Node(object);
	if (head == 0)
	{
		tail = myNode;
	}
	else
	{
		myNode->next = head;
	}
	head = myNode;
	numItems++;
}

void LinkedList::insertAfter(Node* curNode, Eclipse* object)
{
	Node* myNode = new Node(object);
	//Three cases: As first node, as last node, or in the middle
	if (head == 0)
	{
		head = myNode;
		tail = myNode;
	}
	else if (head != 0 && curNode == tail)
	{
		tail->next = myNode;
		tail = myNode;
	}
	else
	{
		myNode->next = curNode->next;
		curNode->next = myNode;
	}
}

void LinkedList::removeAfter(Node* curNode)
{
	//Two cases: if curNode is 0, removed the head node,
	// otherwise, remove the node after curNode
	Node* succNode;
	if (curNode == 0)
	{
		succNode = head->next;
		delete head;
		head = succNode;
		if (succNode == 0) //If there was only one node, redirect the tail
		{
			tail = 0;
		}
	}
	else if (curNode->next != 0) //If there is a node to remove, remove it
	{
		succNode = curNode->next->next;
		delete curNode->next;
		curNode->next = succNode;
		if (succNode == 0)//This is where the tail was removed
		{
			tail = curNode;
		}
	}
	numItems--;
}

void LinkedList::print()
{
	Node* curNode = head;
	while (curNode != 0) //Loop will terminate when curNode checks the tail's next node
	{
		cout << *(curNode->data);
		curNode = curNode->next;
	}
}

void LinkedList::sort()
{
	//for practice perhaps
}

bool LinkedList::isEmpty()
{
	if (head == 0 && tail == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Eclipse LinkedList::getHeadData()
{
	return *(head->data);
}

Eclipse LinkedList::getTailData()
{
	return *(tail->data);
}

LinkedList::Node* LinkedList::getHeadNode()
{
	return head;
}

LinkedList::Node* LinkedList::getTailNode()
{
	return tail;
}

void LinkedList::setHeadNode(Node* myHead)
{
	head = myHead;
}

void LinkedList::setTailNode(Node* myTail)
{
	tail = myTail;
}

int LinkedList::getLength()
{
	return numItems;
}

void LinkedList::setNumItems(int myNumItems)
{
	numItems = myNumItems;
}

void LinkedList::copyToArray(ResizeableArray<Eclipse>& myEclipses) //places node Eclipse contents into a ResizeableArray
{
	Node* curNode = head;
	myEclipses.clear();
	for (int i = 0; i < numItems; i++)
	{
		myEclipses.Add(*(curNode->data));
		curNode = curNode->next;
	}
}
//**************************************************************************************************
#endif /* LINKEDLIST_H_ */
