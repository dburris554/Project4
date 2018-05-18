/*
 * Eclipse.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: david
 */

#include "Eclipse.h"
#include <cstring>

using namespace std;

ostream& operator<< (ostream& os, const Eclipse& ecl) //Overloaded output for making Eclipse data look like input file
{
	os << setw(4)  << right << ecl.linePointer[0];
	os << setw(5)  << right << ecl.linePointer[1];
	os << setw(7)  << right << ecl.linePointer[2];
	os << setw(4)  << right << ecl.linePointer[3];
	os << setw(3)  << right << ecl.linePointer[4];
	os << setw(10) << right << ecl.linePointer[5];
	os << setw(7)  << right << ecl.linePointer[6];
	os << setw(7)  << right << ecl.linePointer[7];
	os << setw(5)  << right << ecl.linePointer[8];

	if (ecl.linePointer[9].length() == 1)
	{
		os << setw(4)  << right << ecl.linePointer[9] << setw(1);
	}
	else
	{
		os << setw(5)  << right << ecl.linePointer[9];
	}

	if (ecl.linePointer[9].length() > 1)
	{
		os << setw(9) << right << ecl.linePointer[10];
	}
	else
	{
		os << setw(10) << right << ecl.linePointer[10];
	}

	os << setw(8)  << right << ecl.linePointer[11];
	os << setw(7)  << right << ecl.linePointer[12];
	os << setw(7)  << right << ecl.linePointer[13];
	os << setw(4)  << right << ecl.linePointer[14];
	os << setw(5)  << right << ecl.linePointer[15];

	if (ecl.linePointer[16].length() > 0 && ecl.linePointer[17].length() > 0)
	{
		os << setw(5) << right << ecl.linePointer[16];
		os << setw(8) << right << ecl.linePointer[17];
	}

	os << endl;
	return os;
}

Eclipse* Eclipse::operator= (const Eclipse& myEclipse) //Overloaded assignment operator
{
	this->linePointer = myEclipse.linePointer;
	this->isBlank = myEclipse.isBlank;
	return this;
}

bool Eclipse::operator==(Eclipse myEclipse)
{
	if (this->getID() == myEclipse.getID())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Eclipse::operator<(Eclipse myEclipse)
{
	if (this->getID() < myEclipse.getID())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Eclipse::operator>(Eclipse myEclipse)
{
	if (this->getID() > myEclipse.getID())
	{
		return true;
	}
	else
	{
		return false;
	}
}

Eclipse::Eclipse()
{
	this->linePointer = 0;
	isBlank = true;
}

Eclipse::Eclipse(string* linePointer)
{
	this->linePointer = linePointer;
	isBlank = false;
}

Eclipse::Eclipse(const Eclipse& oldEclipse) //Copy constructor for pointers' sakes
{
	this->linePointer = oldEclipse.linePointer;
	this->isBlank = oldEclipse.isBlank;
}

Eclipse::~Eclipse()
{}

void Eclipse::setLinePointer(string *linePointer) //Eclipse data is stored in a string*
{
	this->linePointer = linePointer;
}

string* Eclipse::getLinePointer()
{
	return this->linePointer;
}

string Eclipse::getVal(int index) //returns a value within the LinePointer
{
	return this->linePointer[index];
}

int Eclipse::getID() //returns the ID of the Eclipse as an int
{
	return convertToInt(linePointer[0]);
}

bool Eclipse::getIsBlank()
{
	return isBlank;
}

int Eclipse::compareId(Eclipse* myEclipse)
{
	int A = 0;
	int B = 1;
	A = convertToInt(this->getVal(0));
	B = convertToInt(myEclipse->getVal(0));
	if (A < B)
	{
		return -1; //ThisID is smaller than myEclipseID
	}
	else if (A == B)
	{
		return 0; //ThisID is equal to myEclipseID
	}
	else
	{
		return 1; //ThisID is greater than myEclipseID
	}
}

int Eclipse::convertToInt(string str) //Converts strings to integers
{
	float num;
	num = atoi(str.c_str());
	return static_cast<int>(num);
}
