/*
 * Bucket.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: david
 */

#include "Bucket.h"

Bucket::Bucket() //default depth of 1
{
	myArray = new Eclipse[1];
	depth = 1;
	for (int i = 0; i < depth; i++)
	{
		myArray[i] = Eclipse(); //Fill each array with empty eclipses
	}
	numItems = 0;
}

Bucket::Bucket(int myDepth) //constructor with a set depth
{
	myArray = new Eclipse[myDepth];
	depth = myDepth;
	for (int i = 0; i < depth; i++)
	{
		myArray[i] = Eclipse();
	}
	numItems = 0;
}

Bucket::~Bucket() {}

int Bucket::getDepth()
{
	return depth;
}

int Bucket::getNumItems()
{
	return numItems;
}

Eclipse* Bucket::getEclipse(int ID) //look through the bucket for an eclipse by ID
{
	for (int i = 0; i < numItems; i++)
	{
		if (myArray[i].getID() == ID)
		{
			return &myArray[i];
		}
	}
	return new Eclipse();
}

Eclipse* Bucket::getEclipseByIndex(int index) //return an Eclipse via index value in array
{
	return &myArray[index];
}

bool Bucket::isEmpty(int index) //used to see if a bucket has any valid contents
{
	return (myArray[index].getIsBlank());
}

void Bucket::assignBucket(Eclipse* myEclipse) //place Eclipse in bucket bottom up, and increment numItems
{
	myArray[numItems++] = *myEclipse;
}

bool Bucket::isAvailable() //returns true if there is any room left in bucket
{
	return (numItems < depth);
}
