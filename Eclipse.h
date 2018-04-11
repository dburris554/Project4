/*
 * Eclipse.h
 *
 *  Created on: Dec 15, 2017
 *      Author: david
 */

#ifndef ECLIPSE_H_
#define ECLIPSE_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

class Eclipse
{
	friend ostream& operator<< (ostream& os, const Eclipse& ecl);

	public:
		Eclipse();
		Eclipse(string* linePointer);
		Eclipse(const Eclipse &oldEclipse);
		virtual ~Eclipse();
		void setLinePointer(string *linePointer);
		string* getLinePointer();
		string getVal(int index);
		int getID();
		bool getIsBlank();
		Eclipse* operator=(const Eclipse& myEclipse);
		int compareId(Eclipse* myEclipse);
		int convertToInt(string str);

	private:
		string *linePointer; //Pointer for storing an array of strings
		bool isBlank; //true if empty Eclipse, false if filled with data
};
#endif /* ECLIPSE_H_ */
