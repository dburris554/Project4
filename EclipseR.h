/*
 * EclipseR.h
 *
 *  Created on: Sep 13, 2017
 *      Author: David
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "ResizeableArray.h"
#include "LinkedList.h"
#include "HashMap.h"
#include "AvlTree.h"

using namespace std;

#ifndef ECLIPSER_H_
#define ECLIPSER_H_

const int NUMCOLUMNS = 24; //Incoming data is guaranteed to have no more than 24 columns
bool processLine(string tmp, int lineNum, AvlTree* myTree, Eclipse* myEclipse, int& numDuplicates, bool toAdd);
void option_O(string tmp, ofstream& output, char* oFilename, string* header[],
		ResizeableArray<Eclipse>& myEclipses, int totalLinesRead, int totalValidLinesRead);
int option_S(ResizeableArray<Eclipse>& myEclipses, int sortedCol);
void quickSort(int pivot, int lPart, int rPart, ResizeableArray<Eclipse>& myEclipses,Eclipse temp, int userCol);
bool customCompare(string A, string B, int colChoice);
void option_F(ResizeableArray<Eclipse>& myEclipses, int sortedCol, string* header[], HashMap* myMap);
void option_M(string tmp,ifstream& input,char iFilename[],AvlTree* myTree,Eclipse* myEclipse,int lineNum,int& numDuplicates,
	int& totalLinesRead,int& totalValidLinesRead);
void option_P(string tmp,ifstream& input,char iFilename[],AvlTree* myTree,Eclipse* myEclipse,int lineNum,
	int& totalLinesRead, int& totalValidLinesRead);
void option_R(AvlTree* myTree);
void option_C(AvlTree* myTree);
void option_T(AvlTree* myTree);
void option_H(HashMap* myMap);
void option_L(HashMap* myMap);
void binaryS(int lPart, int rPart, ResizeableArray<Eclipse>& myEclipses, string searchValue, string* header[], int colChoice);
void linearS(ResizeableArray<Eclipse>& myEclipses, string searchValue, string* header[], int colChoice);
bool testWholeNumber(string str);
bool testDecNumber(string str);
int convertToInteger(string str);

#endif /* ECLIPSER_H_ */
