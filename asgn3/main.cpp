/** ---------------------------------------------
 *
 * @file		main.cpp
 * @author	Nick McCollum
 * @version	1.0
 *
 * CS-202 - Assignment 3 - Abstract Classes
 *		   Quiz that loads questions from file
 *
 * -------------------------------------------- */

#include <string>
#include <iostream>
#include <exception>
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

/** ---------------------------------------------
 * 	
 * takeAgain - Prompts user to retry missed questions
 *
 * @param	Number of incorrect answers
 *
 * @return	True if user wants to retake,
 *			false if not.
 *
 * -------------------------------------------- */
bool takeAgain(int numIncorrect);

// ----------------------------------------------
int main(int argc, char* argv[]) {
	string dataFileName;
	bool dump = false;

	if (!parseArgs(argc, argv, dataFileName, dump)) {
		return -1;
	}

	try {
		Quiz myQuiz(dataFileName);

		if (dump) {
			myQuiz.dumpQuestions();
			return 0;
		}

		bool again = false;
		do {
			myQuiz.deliverQuiz(again);
			int numIncorrect = myQuiz.getNumIncorrect();
			if (numIncorrect > 0) {
				again = takeAgain(numIncorrect);
			}
			else {
				again = false;
			}
		} while (again);

	}
	catch (string e) {
		cerr << e << endl;
		return -1;
	}
	catch (exception& e) {
		cerr << "Error: " << e.what() << endl;
		return -1;
	}
	catch (...) {
		cerr << "Error: Something has gone terribly wrong" << endl;
		return -1;
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

// ----------------------------------------------
bool takeAgain(int numIncorrect) {
	char s = '\0';
	if (numIncorrect > 1) {
		s = 's';
	}

	cout << "\nYou got " << numIncorrect << " question" << s << " wrong.";
	cout << "\nWould you like to try the one" << s << " you missed again? (Yes / No)\n";

	char yn = cin.get();
	cin.clear();
	cin.ignore(256, '\n');
	if (yn == 'y' || yn == 'Y') {
		cout << endl;
		return true;
	}
	else {
		return false;
	}
}
