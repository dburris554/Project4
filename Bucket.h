/*
 * Bucket.h
 *
 *  Created on: Mar 31, 2018
 *      Author: david
 */
#include "Eclipse.h"

#ifndef BUCKET_H_
#define BUCKET_H_

using namespace std;

class Bucket {
public:
	Bucket();
	Bucket(int depth);
	virtual ~Bucket();
	bool isEmpty(int index);
	Eclipse* getEclipse(int ID);
	Eclipse* getEclipseByIndex(int index);
	int getDepth();
	int getNumItems();
	bool isAvailable();
	void assignBucket(Eclipse* myEclipse);

private:
	Eclipse* myArray; //Pointer for an array of Eclipse objects
	int depth; //how many items can be stored in bucket
	int numItems; //number of items currently in bucket
};

#endif /* BUCKET_H_ */
