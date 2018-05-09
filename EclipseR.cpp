/*
 * EclipseR.cpp
 *
 *  Created on: Sep 13, 2017
 *      Author: David Burris
 *      		112898009
 */
#include "EclipseR.h"
#include <cstring> //Basic C++11 string functions aren't always working, had to use a character string conversion
#include "Eclipse.h"

using namespace std;

int main()
{
	string* header[10]; //holds header data for output
	string tmp = ""; //string placeholder often used in user input
	string userChoice; //string used for menu selection
	int numDuplicates = 0; //used in calculating number of valid lines
	int lineNum = 1; //start line number for processline at 1 for error checking
	int totalLinesRead = 0; //total read lines in input file
	int totalValidLinesRead = 0; //total valid lines in input file
	int sortedCol = -1; //column previously sorted
	ResizeableArray<Eclipse> myEclipses; //Data structure used for searching and sorting
	AvlTree* myTree = new AvlTree(); //Data structure used to store Eclipse data and for Merging/Purging
	LinkedList* myList = new LinkedList(); //Data structure sent into HashMap to initialize the map
	HashMap* myMap; //HashMap for Eclipse ID constant search time, declare here and initialize later
	Eclipse* myEclipse = 0; //Eclipse sent into processLine to store Eclipses into LinkedList
	ifstream input; // Input file stream
	ofstream output;// Output file stream
	char iFilename[100]; // char [] used to hold the iFilename
	char oFilename[100]; // char [] used to hold the oFilename

	do
	{
		cout << "Please enter an input file name or press Enter to continue: " << endl;
		getline(cin,tmp); //Puts user input in a temporary string
		strcpy(iFilename,tmp.c_str()); //Converts the string into a Char array for fstream readability

		if (tmp.length() == 0) //User entered nothing, so this will look to go to Main Menu
		{
			continue;
		}

		input.open(iFilename);

		if(!input.is_open()) //Check to see that the file opened correctly
		{
			cerr << "File '" << iFilename << "' is not available." << endl;
			continue; //Ask for another file after CERR
		}
			//Now we know the file read in is valid.
		for (int i = 0; i < 10; i++) // Store the first 10 lines as the header
		{
			getline(input,tmp);
			header[i] = new string(tmp);
		}

		lineNum = 1; // Reset line number before processing the input file
		while (input.good() && tmp != "") // Begin to process the input file
		{
			//Read the rest of the file
			getline(input,tmp);
			myEclipse = new Eclipse();
			if (processLine(tmp,lineNum++,myTree,myEclipse,numDuplicates,true)) //returns goodData boolean
			{
				totalValidLinesRead++;
			}
			totalLinesRead++;

			delete myEclipse;
		}
		totalValidLinesRead -= numDuplicates; //subtract all of the duplicate entries from valid lines read
		input.close(); //input file is done being read

	} while(strlen(iFilename) != 0); //If user doesn't enter anything, proceed to Main Menu

	//Now make the ResizeableArray
	myTree->copyToArray(myEclipses);

	//Now make the LinkedList
	myEclipse = new Eclipse();
	myList = new LinkedList(myEclipses,myEclipse);
	delete myEclipse;

	//Now make the HashMap
	myMap = new HashMap(*myList,5); //2nd arg is bucket depth

	if (myEclipses.getNumItems() > 0)	//If there is data read in, start the Main Menu, else exit
	{
		cout << "***** Main Menu *****" << endl << endl << "Please choose from the following:" <<endl;
		do
		{
			cout << "'O' to Output" << endl << "'S' to Sort" << endl << "'F' to Find"
				<< endl << "'M' to Merge" << endl << "'P' to Purge" << endl << "'R' for Pre-Order print"
				<< endl << "'C' for In-Order print" << endl << "'T' for Post-Order print"
				<< endl << "'H' for Hash display" << endl << "'L' for Linked display" << endl << "'Q' to Quit"
				<< endl;

			getline(cin,userChoice); //get user selection, case doesn't matter

			if(userChoice == "O" || userChoice == "o") //outputs data to a file or the console
			{
				option_O(tmp, output, oFilename, header, myEclipses, totalLinesRead, totalValidLinesRead);
			}
			else if (userChoice == "S" || userChoice == "s") //sorts data based on a user-selected column
			{
				sortedCol = option_S(myEclipses,sortedCol);
			}
			else if (userChoice == "F" || userChoice == "f") //finds data based on a user-selected column and text
			{
				option_F(myEclipses, sortedCol, header, myMap);
			}
			else if (userChoice == "M" || userChoice == "m") //merges files into dataset
			{
				option_M(tmp,input,iFilename,myTree,myEclipse,lineNum,numDuplicates,totalLinesRead,totalValidLinesRead);

				//Now remake the ResizeableArray
				myEclipses.clear();
				myTree->copyToArray(myEclipses);

				//Now remake the LinkedList
				delete myList;
				myEclipse = new Eclipse();
				myList = new LinkedList(myEclipses,myEclipse);
				delete myEclipse;

				//Now remake the HashMap
				myMap = new HashMap(*myList,5); //2nd arg is bucket depth
			}
			else if (userChoice == "P" || userChoice == "p") //purges files from dataset
			{
				myTree = option_P(tmp,input,iFilename,myTree,myEclipse,lineNum,
						totalLinesRead,totalValidLinesRead);

				//Now remake the ResizeableArray
				myEclipses.clear();
				myTree->copyToArray(myEclipses);

				//Now make the LinkedList
				delete myList;
				myEclipse = new Eclipse();
				myList = new LinkedList(myEclipses,myEclipse);
				delete myEclipse;

				//Now remake the HashMap
				myMap = new HashMap(*myList,5); //2nd arg is bucket depth
			}
			else if (userChoice == "R" || userChoice == "r") //prints AVLtree contents pre-ordered to console
			{
				option_R(myTree);
			}
			else if (userChoice == "C" || userChoice == "c") //prints AVLtree contents in-order to console
			{
				option_C(myTree);
			}
			else if (userChoice == "T" || userChoice == "t") //prints AVLtree contents post-order to console
			{
				option_T(myTree);
			}
			else if (userChoice == "H" || userChoice == "h") //prints the HashMap by bucket order
			{
				option_H(myMap);
			}
			else if (userChoice == "L" || userChoice == "l") //prints the LinkedList contents within the HashMap
			{
				option_L(myMap);
			}
			else if (userChoice == "Q" || userChoice == "q") //quits the program
			{
				cout << "Goodbye!";
				continue;
			}
			else
			{
				cout << "'" << userChoice << "' is not a valid option. Please try again." << endl << endl;
			}
		} while(userChoice != "Q" && userChoice != "q");
	}
	return 0;
}
/////////////////////////// Method Implementations ////////////////////////////
bool processLine(string tmp, int lineNum, AvlTree* myTree, Eclipse* myEclipse, int& numDuplicates, bool toAdd)
{
	if (tmp == "") //If the line of the file is empty, return 'badData'
	{
		return false;
	}

	string *linePointer; //setup pointer for string [] for eclipse data cells
	linePointer = new string[NUMCOLUMNS]; //initialize array for one eclipse (up to 24 columns)
	//Eclipse* myEclipse; //Eclipse pointer used when adding to LinkedList

	string::iterator it; 		//setup for capturing string 'tmp' elements
	bool isLeadingSpace = false;
	int index = 0;
	bool isValidCharacter = false;
	string capture = "";

	for (it = tmp.begin(); it < tmp.end();++it)
		{
			if (isspace(*it))      //Only capture elements that are not spaces
			{
				isLeadingSpace = true;
				isValidCharacter = false;
			}

			else                             //test whether the element is a space
			{
				isLeadingSpace = false;
				isValidCharacter = true;
			}

			if (isValidCharacter)           //if is a valid char, begin concatenating it to capture
			{
				capture += *it;
			}

			if ((isLeadingSpace && capture.length() > 0) || (capture.length() > 0 && it + 1 >= tmp.end()))
			{
				//Now lets put the 'captured' items into an array during the loop
				linePointer[index] = capture;
				capture = "";
				index++;
			}
		}
	//Now we test the data integrity of the eclipse entry

	//first test is on column 10. If starts with 'P', must be 16 columns. Else, 18 columns.
	bool goodData = true;
	bool typePartial = false;

	if (linePointer[9].at(0) == 'P')
	{
		//should be 16 columns
		typePartial = true;

		if (index != 16)
		{
			goodData = false;
			cerr << "Error in data row " << lineNum << ": " << index << " columns found. Should be 16." << endl;
		}
	}
	else //else, 18 columns
	{
		if (index != 18)
		{
			goodData = false;
			cerr << "Error in data row " << lineNum << ": " << index << " columns found. Should be 18." << endl;
		}
	}

	//Next, need to check to see if col 1, 2, 3, 5, 7, 8, 9, 15, 16, and (if present) 17 are whole numbers.
	//Also, check if col 11 and 12 are decimals.
	for (int colNum = 0; colNum < (typePartial ? 16 : 17); colNum++)
	{
		if (colNum == 10 || colNum == 11)
		{
			//Check if a decimal
			if (testDecNumber(linePointer[colNum]) == false)
			{
				goodData = false;
				cerr << "Error in data row " << lineNum << ": " << "Column " << colNum+1 << " is not a decimal number." << endl;
			}
		}
		else if (colNum == 3 || colNum == 5 || colNum == 9 || colNum == 12 || colNum == 13 )
		{
			continue; //These columns don't need to be checked
		}
		else
		{
			//Check if a whole number
			if (testWholeNumber(linePointer[colNum]) == false)
			{
				goodData = false;
				cerr << "Error in data row " << lineNum << ": " << "Column " << colNum+1 << " is not a whole number." << endl;
			}
		}
	}

	//If all tests pass, return true and either add/remove Eclipse to/from database
	if (goodData)
	{
		myEclipse = new Eclipse(linePointer);

		if (toAdd) //Add to database
		{
			Eclipse* tempEclipse = myTree->findEclipse(myEclipse->getID());
			bool isDuplicate = false;

			if (!(tempEclipse->getIsBlank())) //only compare if returns a valid Eclipse
			{
				isDuplicate = (myEclipse->getID() == tempEclipse->getID()); //If eclipse is found, already exists in tree
			}
			if (isDuplicate) //if a duplicate, increment counter, change that node's eclipse value
			{
				numDuplicates++;
				myTree->setTempNode(myTree->findNode(myEclipse->getID()));
				myTree->getTempNode()->setKey(myEclipse->getID());
				myTree->getTempNode()->setEclipse(myEclipse);
			}
			else //otherwise, add as a new entry
			{
				myTree->addItem(myEclipse);
			}
		}
		else //Remove from database
		{
			myTree->removeItem(myEclipse);
		}
	}
	return goodData;
}

void option_O(string tmp, ofstream& output, char* oFilename, string* header[],
		ResizeableArray<Eclipse>& myEclipses, int totalLinesRead, int totalValidLinesRead) //Prints information
{
	do
	{
		cout << "Please enter the output file name or press Enter to print to console: " << endl;
		getline(cin,tmp); //Puts user input in a temporary string
		strcpy(oFilename,tmp.c_str()); //Converts the string into a Char array for fstream readability

		if (tmp.length() == 0)
		{
			continue;
		}

		output.open(oFilename);

		if(!output.is_open()) //Check to see that the file opened correctly
		{
			cerr << "File '" << oFilename << "' is not available." << endl;
			continue;
		}
	} while (!output.is_open() && tmp != ""); //If user doesn't enter anything, print to console

	//Now we know the file read in is valid.
	//If printing to file, use output stream
	if (tmp != "")
	{
		for (int i = 0; i < 10; i++) // Print the header
		{
			output << *header[i] << endl;
		}

		for (int i = 0; i < myEclipses.getNumItems(); ++i) // Print the body
		{
			output << myEclipses[i];
		}

		//Print the footer
		output << "Data lines read: " << totalLinesRead << "; Valid eclipses read: "
			   << totalValidLinesRead << "; Eclipses in memory: " << myEclipses.getNumItems()
			   << endl;
		output.close();

		cout << endl; //Add an extra blank line to console output
	}
	else //otherwise, print to console
	{
		if (myEclipses.getNumItems() > 0) //print this way if there is data to print
		{
			for (int i = 0; i < 10; i++) // Print the header
			{
				cout << *(header[i]);
			}

			for (int i = 0; i < myEclipses.getNumItems(); ++i) // Print the body
			{
				cout << myEclipses[i];
			}

			//Print the footer
			cout << "Data lines read: " << totalLinesRead << "; Valid eclipses read: "
				 << totalValidLinesRead << "; Eclipses in memory: " << myEclipses.getNumItems()
				 << endl << endl;
		}
		else //print this way if no data to print
		{
			for (int i = 0; i < 10; i++) // Print the header
			{
				cout << *(header[i]);
			}

			//Print the footer
			cout << "Data lines read: " << totalLinesRead << "; Valid eclipses read: "
				 << totalValidLinesRead << "; Eclipses in memory: " << myEclipses.getNumItems()
				 << endl << endl;
		}
	}
}

int option_S(ResizeableArray<Eclipse>& myEclipses, int sortedCol) //Sorts data based on user-selected column
{
	string tmp = ""; //used in user input
	Eclipse temp; //Given to QuickSort so that QS doesn't use up all the memory
	int colChoice; //user-selected column
	do
	{
		cout << "Please select which field to sort (1 - 18):" << endl;
		getline(cin,tmp);
		colChoice = convertToInteger(tmp) - 1; //make the column zero-indexed for code processing
	} while(colChoice < 0 || colChoice > 17); //loop continues until user enters a number within the range

	if (sortedCol == colChoice) //Don't sort if the data is already sorted by the chosen column
	{
		cout << "Data is already sorted by column " << colChoice+1 << endl << endl;
		return colChoice;
	}

	cout << "Sorting..." << endl; //Put text before and after the sort
	quickSort(0,1,myEclipses.getNumItems()-1,myEclipses,temp,colChoice);
	cout << "done." << endl << endl;
	return colChoice; //return user-selected column so that option_F will know how to search
}

void quickSort(int pivot, int lPart, int rPart, ResizeableArray<Eclipse>& myEclipses, Eclipse temp, int colChoice)
{															//Sorts the data, also Pivot is always the first element
	int origRPart = rPart; //keep track of the original index of the right partition
	if (lPart > rPart) //if recursion starts and lPart is larger than rPart, return out
	{
		return;
	}

	while (lPart <= rPart) //main comparative statement. Also qsCompare computes (is A <= B?)
	{
		while (customCompare(myEclipses[lPart].getVal(colChoice),myEclipses[pivot].getVal(colChoice),colChoice))
		{
			if (lPart == origRPart && customCompare(myEclipses[lPart].getVal(colChoice),myEclipses[pivot].getVal(colChoice),colChoice))
			{											//if lPart goes to the end and the last element is switchable
				temp = myEclipses[lPart];				//switch lPart with pivot
				myEclipses.ReplaceAt(myEclipses[pivot],lPart);
				myEclipses.ReplaceAt(temp,pivot);

				quickSort(pivot,pivot+1,lPart-1,myEclipses,temp,colChoice); //and recurse excluding the previous pivot
				return;
			}
			lPart++; //keep incrementing lPart until it finds something to switch or reaches the end
		}

		while (customCompare(myEclipses[pivot].getVal(colChoice),myEclipses[rPart].getVal(colChoice),colChoice))
		{
			rPart--; //keep decrementing rPart until it finds something to switch or reaches the end
			if (rPart == pivot) //if rPart reaches the end, pivot is in the right place
			{					//so recurse excluding the pivot
				quickSort(pivot+1,lPart+1,origRPart,myEclipses,temp,colChoice);
				return;
			}
		}

		if (lPart > rPart) //if lPart crosses rPart and they are ready to switch
		{
			break; //switch lpart-1 with the pivot
		}
			//Assuming no special cases happen, lPart finds something, rPart find something, and they switch elements
		temp = myEclipses[lPart];
		myEclipses.ReplaceAt(myEclipses[rPart],lPart);
		myEclipses.ReplaceAt(temp,rPart);

		lPart++; //Then place lPart and rPart one step closer and repeat main comparative statement
		rPart--;
	}

	temp = myEclipses[lPart-1]; //switch lpart-1 with the pivot
	myEclipses.ReplaceAt(myEclipses[pivot],lPart-1);
	myEclipses.ReplaceAt(temp,pivot);

	//Array left-half recursion
	quickSort(pivot,pivot+1,lPart-2,myEclipses,temp,colChoice);

	//Array right-half recursion
	quickSort(lPart,lPart+1,origRPart,myEclipses,temp,colChoice);
}

bool customCompare(string A, string B, int colChoice)
{
	int lexArray[] = {5, 10, 11, 12, 13, 17}; //array of lexicographic column indexes
	bool isLex = false; //flag for if a lex column

	for (int i = 0; i < 6; i++) //check to see if colChoice is a lex column
	{
		if (colChoice == lexArray[i])
		{
			isLex = true; //set flag if a lex column
			break;
		}
	}

	if (colChoice == 3) //if comparing by months, do the following
	{
		string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
		//have to initialize i1 and i2 or compiler will complain when comparing them later
		//because it thinks they may not be set in the for loop
		//but they always will, unless monthA or monthB are invalid
		int index1 = 0;
		int index2 = 0;
		for (int i = 0; i < 12; i++)
		{
			if(months[i] == A) //set indexes of the comparable months to index1 and index2
			{
				index1 = i;
			}

			if(months[i] == B)
			{
				index2 = i;
			}
		}
		return (index1 <= index2); //compare the month's indexes in the months[]
	}
	else if (isLex) //if lexicographic, return a normal string comparison
	{
		return (A <= B);
	}
	else //otherwise, apply an integer comparison
	{
		return(convertToInteger(A) <= convertToInteger(B));
	}
}

void option_F(ResizeableArray<Eclipse>& myEclipses, int sortedCol, string* header[], HashMap* myMap)
{
	bool validData = false; //flag for validating user-input
	string tmp = ""; //used to gather user-input
	string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; //list of possible months in dataset
	int colChoice; //user-entered column to find on
	int counter = 0; //used to return from HashMap

	do
	{
		cout << "Please select which field to find on (1 - 18):" << endl;
		getline(cin,tmp);
		colChoice = convertToInteger(tmp) - 1; //convert colChoice to zero-indexed for code processing
	} while (colChoice < 0 || colChoice > 17); //user must enter a value within the range

	do //now ask for text to search for
	{
		cout << "Please enter search value: " << endl;
		if (colChoice == 16 || colChoice == 17)
		{
			getline(cin,tmp); //allow return characters as input on the last two columns
		}
		else
		{
			do
			{
				getline(cin,tmp);
			} while(tmp == ""); //keep looping until text is entered
		}

		switch (colChoice) //switch case for validating the search text on the chosen column
		{
		case 3:
			for (int i = 0; i < 12; i++) //Check if user input is a month
			{
				if (tmp == months[i]) //If compares true, input is valid
				{
					validData = true;
					break;
				}
			}
			if (!validData)
			{
				cout << "Please enter months as 'Jan', 'Feb', 'Mar', etc." << endl << endl;
			}
			break;
		case 0: //apply a whole number test on these cases
		case 1:
		case 2:
		case 4:
		case 6:
		case 7:
		case 8:
		case 14:
		case 15:
		case 16:
			if (testWholeNumber(tmp))
			{
				validData = true;
			}
			break;
		case 10: //apply a decimal number test on these cases
		case 11:
			if (testDecNumber(tmp))
			{
				validData = true;
			}
			break;
		default:
			validData = true; //Default case is lexicographic, which does not need to be tested
			break;
		}
	} while (!validData);
	//This is the end of the data validation process

	if (colChoice == 0) //Use HashMap for ID lookup
	{
		if (myMap->getSize() != 0) //Only try to find if map is populated
		{
			Eclipse* myEclipse = myMap->findInMap(convertToInteger(tmp));
			if (!myEclipse->getIsBlank())
			{
				cout << *myEclipse;
				counter++;
			}
		}
		cout << "Eclipses found: " << counter << endl << endl; //append line stating how many Eclipses were found to user
	}
	else if (colChoice == sortedCol) //if searching on a sorted column, use binary search
	{
		binaryS(0,myEclipses.getNumItems()-1,myEclipses,tmp,header,colChoice);
	}
	else //otherwise, use linear search
	{
		linearS(myEclipses,tmp,header,colChoice);
	}
}

void option_M(string tmp,ifstream& input,char iFilename[],AvlTree* myTree,Eclipse* myEclipse,int lineNum,int& numDuplicates,
		int& totalLinesRead, int& totalValidLinesRead)
{
	//Prompt for a data file, verify the file, and attempt to merge the eclipses into existing LinkedList
	// then remake the ResizeableArray
	tmp = "";
	lineNum = 1; // Reset line number before processing the input file
	numDuplicates = 0;

	cout << "Please enter a merge file name: " << endl;
	getline(cin,tmp); //Puts user input in a temporary string
	strcpy(iFilename,tmp.c_str()); //Converts the string into a Char array for fstream readability

	input.open(iFilename);

	if(!input.is_open()) //Check to see that the file opened correctly
	{
		cerr << "File '" << iFilename << "' is not available." << endl << endl;
		return; //Go back to the main menu
	}
		//Now we know the file read in is valid.
	for (int i = 0; i < 10; i++) // Read through the first 10 lines
	{
		getline(input,tmp);
	}

	while (input.good() && tmp != "") //Begin to process the input file
	{
		//Read the rest of the file
		getline(input,tmp);
		if (processLine(tmp,lineNum++,myTree,myEclipse,numDuplicates,true)) //returns goodData boolean
		{
			totalValidLinesRead++;
		}
		totalLinesRead++;
	}
	totalValidLinesRead -= numDuplicates;
	input.close(); //input file is done being read
}

AvlTree* option_P(string tmp,ifstream& input,char iFilename[],AvlTree* myTree,Eclipse* myEclipse,int lineNum,
		int& totalLinesRead, int& totalValidLinesRead)
{
	//Prompt for a data file, verify the file, and attempt to purge the eclipses from LinkedList. If the
	// eclipse to be purged is not in the list, cout "Eclipse catalog #XX not found"
	// then remake the ResizeableArray
	tmp = ""; //used as user input string
	int numDuplicates = 0; //will be incremented if a duplicate is found
	lineNum = 1; // Reset line number before processing the input file

	//If there is no data in the AvlTree, return
	if (myTree->getRootNode() == 0)
	{
		cerr << "There is no data to purge!" << endl;
		return myTree;
	}

	cout << "Please enter a purge file name: " << endl;
	getline(cin,tmp); //Puts user input in a temporary string
	strcpy(iFilename,tmp.c_str()); //Converts the string into a Char array for fstream readability

	input.open(iFilename);

	if(!input.is_open()) //Check to see that the file opened correctly
	{
		cerr << "File '" << iFilename << "' is not available." << endl << endl;
		return myTree; //Go back to the main menu
	}
		//Now we know the file read in is valid.
	for (int i = 0; i < 10; i++) // Read through the first 10 lines
	{
		getline(input,tmp);
	}

	while (input.good() && tmp != "") //Begin to process the input file
	{
		//Read the rest of the file
		getline(input,tmp);
		if (processLine(tmp,lineNum++,myTree,myEclipse,numDuplicates,false)) //returns goodData boolean
		{
			totalValidLinesRead++;
		}
		totalLinesRead++;
	}
	input.close(); //input file is done being read
	return myTree;
}

void option_R(AvlTree* myTree) //prints AVLtree contents pre-order
{
	myTree->printPreOrder();
	cout << endl;
}

void option_C(AvlTree* myTree) //prints AVLtree contents in-order
{
	myTree->printInOrder();
	cout << endl;
}

void option_T(AvlTree* myTree) //prints AVLtree contents post-order
{
	myTree->printPostOrder();
	cout << endl;
}

void option_H(HashMap* myMap) //prints the bucket contents of a HashMap
{
	myMap->printMap();
}

void option_L(HashMap* myMap) //option C for HashMap's LinkedList
{
	myMap->getHashLinkedList()->print();
	cout << endl;
}

void binaryS(int lPart, int rPart, ResizeableArray<Eclipse>& myEclipses, string searchValue, string* header[], int colChoice)
{
	int numFound = 0; //number of Eclipses found in search
	bool printHeader = true; //initializes 'true' to show that the header has not been printed yet
	int middle = (lPart + rPart)/2; //Middle element of the array, is compared to the search value
	int temp = 0; //variable used to check for duplicates
	cout << myEclipses[middle].getVal(colChoice) << endl;
	if (searchValue == myEclipses[middle].getVal(colChoice)) //Compare the search value to the middle of array
	{
		if (printHeader)
		{
			for (int i = 0; i < 10; i++) //If not yet printed, print the header
			{
				cout << *header[i];
			}
			printHeader = false;
		}

		cout << myEclipses[middle];
		numFound++;
		//If a match to 'middle', check for duplicate entries
		temp = middle - 1;

		while (searchValue == myEclipses[temp].getVal(colChoice))
		{
			cout << myEclipses[temp--]; //This checks from the middle to the left
			numFound++;
		}
		temp = middle + 1;

		while (searchValue == myEclipses[temp].getVal(colChoice))
		{
			cout << myEclipses[temp++]; //This checks from the middle to the right
			numFound++;
		}

		cout << "Eclipses found: " << numFound << endl << endl; //ending print containing number of finds
		return;
	}
	else if (rPart - lPart == 1) //With 2 elements left, this will check the other and return out
	{
		cout << myEclipses[middle].getVal(colChoice) << endl;
		if (searchValue == myEclipses[rPart].getVal(colChoice))
		{
			//Print entry at rPart
			if (printHeader)
			{
				for (int i = 0; i < 10; i++) // Print the header
				{
					cout << *header[i] << endl;
				}
				printHeader = false;
			}
			cout << myEclipses[rPart];
			numFound++;
		}

		cout << "Eclipses found: " << numFound << endl << endl;
		return;
	}
	else //Recursive steps made for the left half or right half
	{
		if (customCompare(searchValue,myEclipses[middle].getVal(colChoice),colChoice))
		{
			binaryS(lPart,middle-1,myEclipses,searchValue,header,colChoice);
		}
		else
		{
			binaryS(middle+1,rPart,myEclipses,searchValue,header,colChoice);
		}
	}
}

void linearS(ResizeableArray<Eclipse>& myEclipses, string searchValue, string* header[], int colChoice)
{
	int numFound = 0; //number of Eclipses found in search
	bool printHeader = true; //initializes 'true' to show that the header has not been printed yet

	for (int i = 0; i < myEclipses.getNumItems(); i++) //Search the entire array for the search value
	{
		if (searchValue == myEclipses[i].getVal(colChoice)) //If a match, check to see if header is printed
		{
			if (printHeader)
			{
				for (int i = 0; i < 10; i++) // Print the header
				{
					cout << *header[i];
				}
				printHeader = false;
			}
			cout << myEclipses[i]; //Then print the data line and increment 'numFound'
			numFound++;
		}
	}
	cout << "Eclipses found: " << numFound << endl << endl; //Result print line
}

/////////////Credit to Johnathan Smith///////////
bool testWholeNumber(string str)
{
	float test;
	string myString;
	test = atof(str.c_str());

	if (test == static_cast<int>(test))
	{
		return true;
	}
	else if (str == myString)
	{
		return false;
	}
	else
	{
		return false;
	}
}

bool testDecNumber(string str)
{
	float test;
	string myString;
	test = atof(str.c_str());

	if ((test == static_cast<int>(test)) && (static_cast<int>(test) != 0)
										 && (static_cast<int>(test) != 1)
										 && (static_cast<int>(test) != -1))
	{
		return false;
	}
	else if (str == myString)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int convertToInteger(string str)
{
	float num;
	num = atoi(str.c_str());
	return static_cast<int>(num);
}
