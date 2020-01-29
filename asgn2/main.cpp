/** ---------------------------------------------
*
* @file		main.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-202 - Assignment 2 - Inheritance & Polymorphism
*		   Quiz that loads questions from file
*
* -------------------------------------------- */

#include <string>
#include <iostream>
#include "quiz.h"

using namespace std;

/** ---------------------------------------------
* 	
* parseArgs - Checks for command line arguments
*			  and sets configs accordingly.
*
* @param	Argument count 
* @param 	Argument array
* @param	String to store data file name 
* @param 	Bool to store dump config
*
* @return  	True if all arguments where valid,
*			false otherwise.
*
* -------------------------------------------- */
bool parseArgs(int argc, char* argv[], string &dataFileName, bool &dump);

// ----------------------------------------------
int main(int argc, char* argv[]) {
	string dataFileName;
	bool dump = false;

	if (parseArgs(argc, argv, dataFileName, dump)) {
		Quiz myQuiz;
		if (!myQuiz.loadQuestions(dataFileName)) {
			return -1;
		}

		if (dump) {
			myQuiz.dumpQuestions();
		}

		myQuiz.deliverQuiz();
	}

	return 0;
}

// ----------------------------------------------
bool parseArgs(int argc, char* argv[], string &dataFileName, bool &dump) {
	for (int i = 1; i < argc; i++) {
		// Check if this is a command line switch
		string arg = string(argv[i]);
		if (arg.at(0) == '-') {
			if (arg.compare("-d") == 0) {
				dump = true;
			}
			else {
				cerr << "Invalid option: " << argv[i] << endl;
				return false;
			}
		}
		else {
			dataFileName = argv[i];
		}
	}

	if (dataFileName.empty()) {
		cerr << "Please provide a questions file\n";
		cerr << "Usage: " << argv[0] << " filename [-d]\n";
		return false;
	}
	return true;
}
