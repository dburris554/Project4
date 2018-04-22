/*
 * ResizeableArray.h
 *
 *  Created on: Dec 17, 2017
 *      Author: david
 */

#ifndef RESIZEABLEARRAY_H_
#define RESIZEABLEARRAY_H_

using namespace std;

template<typename TheType>
class ResizeableArray
{
	public:
		ResizeableArray();
		ResizeableArray(int startingSize);
		virtual ~ResizeableArray();
		void PrintAll() const;
		void Add(TheType myObject);
		void AddAt(TheType myObject, int index);
		void ReplaceAt(TheType myObject, int index);
		void RemoveAt(int index);
		int getMyLength();
		int getNumItems();
		TheType operator[](int index);
		void clear();

	private:
		void Double();
		void Half();
		TheType* myArray;
		int myLength;
		int numItems;
};

template<typename TheType>
ResizeableArray<TheType>::ResizeableArray() //noArg constructor shows 10 empty spots and creates a new TheType[]
{
	myLength = 10;
	numItems = 0;
	myArray = new TheType[myLength];
}

template<typename TheType>
ResizeableArray<TheType>::ResizeableArray(int startingSize) //constructor with an arg for the starting size
{
	myLength = startingSize;
	numItems = 0;
	myArray = new TheType[myLength];
}

template<typename TheType>
ResizeableArray<TheType>::~ResizeableArray()
{
	delete[] myArray;
}

template<typename TheType>
void ResizeableArray<TheType>::PrintAll() const
{
	for (int i = numItems - 1; i >= 0; i--)
	{
		cout << myArray[i];
	}
}

template<typename TheType>
void ResizeableArray<TheType>::Add(TheType myObject)
{
	myArray[numItems] = myObject; //fill a spot with an object, then increment the index
	numItems++; //with this notation, numItems is also the index of the array

	if ((numItems * 2) >= myLength) //Double array size if array fills half way
	{
		Double();
	}
}

template<typename TheType>
void ResizeableArray<TheType>::AddAt(TheType myObject, int myIndex)
{
	if (myIndex >= myLength) //Check for a valid index arg
	{
		cerr << "Error: this array only has length " << myLength << "." << endl;
	}
	else if (myIndex < 0)
	{
		cerr << "Error: given index can't be negative." << endl;
	}

	myArray[myIndex] = myObject; //Then place the object at the given index
	numItems++;

	if ((numItems * 2) >= myLength) //Also check for filling halfway
	{
		Double();
	}
}

template<typename TheType>
void ResizeableArray<TheType>::ReplaceAt(TheType myObject, int myIndex)
{
	if (myIndex >= myLength) //Check index for validity
	{
		cerr << "Error: this array only has length " << myLength << "." << endl;
	}
	else if (myIndex < 0)
	{
		cerr << "Error: given index can't be negative." << endl;
	}
	else
	{
		if (myIndex > numItems) //Because numItems is also the current index, increment numItems if replacing ahead
		{
			numItems++;
		}
		myArray[myIndex] = myObject;
	}
}

template<typename TheType>
void ResizeableArray<TheType>::RemoveAt(int myIndex)
{
	if (myIndex >= myLength) //Check index for validity
	{
		cerr << "Error: this array only has length " << myLength << "." << endl;
	}
	else if (myIndex < 0)
	{
		cerr << "Error: given index can't be negative." << endl;
	}
	else if (myArray[myIndex] == 0)
	{
		cerr << "Error: there is nothing to remove at index " << myIndex << "." << endl;
	}
	else
	{
		for (int i = myIndex; i < myLength - 1; i++) // Loop only between gap and end of array
			{										//Shifting all elements backwards one index
				myArray[i] = myArray[i+1];
			}

		myArray[myLength - 1] = NULL; //make sure last element is not duplicated
		numItems--;

		if (numItems * 2 < myLength) //Halve the array size if array is less than half full
		{
			Half();
		}
	}
}

template<typename TheType>
int ResizeableArray<TheType>::getMyLength() //total number of slots in array
{
	return myLength;
}

template<typename TheType>
int ResizeableArray<TheType>::getNumItems() //total number of items in array
{
	return numItems;
}

template<typename TheType>
TheType ResizeableArray<TheType>::operator[](int index) //allows for reading of array content
{
	return myArray[index];
}

template<typename TheType>
void ResizeableArray<TheType>::clear()
{
	numItems = 0;
}

template<typename TheType>
void ResizeableArray<TheType>::Double()
{
	ResizeableArray<TheType> *myTempResizeableArray = new ResizeableArray<TheType>(myLength); //using a temp array
	for (int i = 0; i < myLength; i++)														//to store data
	{
		myTempResizeableArray->myArray[i] = this->myArray[i]; //fill up temp array with data
		myTempResizeableArray->numItems++;
	}

	delete[] myArray; //delete old array and double length paramater
	this->myLength *= 2;

	myArray = new TheType[myLength];
	for (int i = 0; i < myLength / 2; i++)
	{
		myArray[i] = myTempResizeableArray->myArray[i]; //put data back into newly created array
	}

	delete myTempResizeableArray; //remove the temp array
}

template<typename TheType>
void ResizeableArray<TheType>::Half() //same ideas as in Double()
{
	ResizeableArray<TheType> *myTempResizeableArray = new ResizeableArray<TheType>(myLength);
	for (int i = 0; i < myLength; i++)
	{
		myTempResizeableArray->myArray[i] = this->myArray[i];
		myTempResizeableArray->numItems++;
	}

	delete[] myArray;
	myLength /= 2;

	myArray = new TheType[myLength];
	for (int i = 0; i < myLength; i++)
	{
		myArray[i] = myTempResizeableArray->myArray[i];
	}

	delete[] myTempResizeableArray;
}
#endif /* RESIZEABLEARRAY_H_*/
