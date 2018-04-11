/*
 * HashMap.h
 *
 *  Created on: Mar 31, 2018
 *      Author: david
 */
#include "Bucket.h"
#include "Eclipse.h"
#include "ResizeableArray.h"
#include "LinkedList.h"
#include <math.h>

#ifndef HASHMAP_H_
#define HASHMAP_H_

using namespace std;

class HashMap {

public:
	HashMap(LinkedList myLinkedList, int myBucketDepth); //creates HashMap from given LinkedList and max bucket depth
	HashMap(); //non-functional default constructor
	virtual ~HashMap();
	int getSize();
	LinkedList* getHashLinkedList();
	void assignToMap(Eclipse* myEclipse);
	int getNumBuckets();
	double getLoadFactor();
	void setLoadFactor(double myLoadFactor);
	Eclipse* findInMap(int ID);
	void printMap();

private:
	Bucket* bucketArray;
	LinkedList* hashLinkedList;
	int size;
	int numBuckets;
	int bucketDepth;
	double loadFactor;
	int hash(int ID); //Hashing function to store objects into map

};
//***************************************************************************
HashMap::HashMap(LinkedList myLinkedList, int myBucketDepth)
{
	hashLinkedList = new LinkedList();
	loadFactor = 0.5; //This ensures the Hash Map will always end up half full
	bucketDepth = myBucketDepth;

	//now we copy the incoming LinkedList
	size = myLinkedList.getLength();
	hashLinkedList->setHeadNode(myLinkedList.getHeadNode());
	hashLinkedList->setTailNode(myLinkedList.getTailNode());
	hashLinkedList->setNumItems(size);

	//now we use a formula to decide how many buckets to make based on load factor and depth
	//formula will be accurate with a double's division and a +0.5 static int cast
	numBuckets = static_cast<int>(ceil((size/(loadFactor * bucketDepth))));
	bucketArray = new Bucket[numBuckets];

	for (int i = 0; i < numBuckets; i++)
	{
		bucketArray[i] = Bucket(bucketDepth);
	}

	//now we populate the bucketArray
	LinkedList::Node* curNode = hashLinkedList->getHeadNode();
	for (int i = 0; i < hashLinkedList->getLength(); i++)
	{
		assignToMap(curNode->data);
		curNode = curNode->next;
	}
}

HashMap::HashMap() //empty constructor sets everything to 0
{
	hashLinkedList = 0;
	size = 0;
	numBuckets = 0;
	bucketDepth = 0;
	loadFactor = 0;
}

HashMap::~HashMap() {}

int HashMap::getSize()
{
	return size;
}

LinkedList* HashMap::getHashLinkedList()
{
	return hashLinkedList;
}

void HashMap::assignToMap(Eclipse* myEclipse)
{
	//First we take the ID from the Eclipse and hash the value, then check to see if that bucket index is empty
	//we check the bucket index by trying the first bucket depth value, and going up to the max depth
	//if the bucket is completely full, jump ahead 5 buckets and try again
	int myHashIndex = hash(myEclipse->getID());
	int origHashIndex = myHashIndex;

	do
	{
		if (bucketArray[myHashIndex].isAvailable())
		{
			bucketArray[myHashIndex].assignBucket(myEclipse);
			break;
		}
		myHashIndex = (myHashIndex + 1) % numBuckets;
	} while (origHashIndex != myHashIndex);
}

int HashMap::getNumBuckets()
{
	return numBuckets;
}

double HashMap::getLoadFactor()
{
	return loadFactor;
}

void HashMap::setLoadFactor(double myLoadFactor)
{
	loadFactor = myLoadFactor;
}

int HashMap::hash(int ID)
{
	return (ID % numBuckets); //This hashing function returns the ID, and will wrap around if greater than numBuckets
								//This strategy is combined with linear collision resolution to have minimal empty buckets and only
								//slight linear clumping. Load factor ensures no overflow.
}

Eclipse* HashMap::findInMap(int ID) //Takes an eclipse ID and finds that Eclipse, if not found, returns a blank Eclipse.
{
	int myHashIndex = hash(ID);
	int origHashIndex = myHashIndex;
	do
	{
		if (!bucketArray[myHashIndex].getEclipse(ID)->getIsBlank())
		{
			return bucketArray[myHashIndex].getEclipse(ID);
		}
		myHashIndex = (myHashIndex + 1) % numBuckets;
	} while (origHashIndex != myHashIndex); //Stop searching if you reach the original hash index

	return new Eclipse();
}

void HashMap::printMap()
{
	for (int i = 0; i < numBuckets; i++) //looping over each bucket 'i'
	{
		if (bucketArray[i].getNumItems() == 0) //If bucket is empty, print NULL as contents
		{
			cout << "Bucket " << i <<": NULL" << endl;
		}
		else for (int j = 0; j < bucketArray[i].getNumItems(); j++) //looping over bucket 'i' contents 'j',
																	//where 'j' is the bucket index
		{
			cout << "Bucket " << i <<": " << *(bucketArray[i].getEclipseByIndex(j)); //print bucket 'i' eclipse at 'j'
		}

		cout << endl; //blank line between buckets
	}
}
//***************************************************************************
#endif /* HASHMAP_H_ */
