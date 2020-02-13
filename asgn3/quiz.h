/** ---------------------------------------------
 *
 * @file	quiz.h
 * @author	Nick McCollum
 * @version	1.0
 *
 * CS-202 - Assignment 3 - Abstract Classes
 *		    Quiz class definition
 *
 * -------------------------------------------- */

#ifndef QUIZ_H
#define QUIZ_H

#include <vector>
#include <string>
#include <sstream>
#include "question.h"
#include "questiontf.h"
#include "questionmc.h"
#include "questionsa.h"

using namespace std;

class Quiz {
	public:
		//Constructors
		Quiz();
		Quiz(string dataFileName);

		// Destructor
		~Quiz();

		/** ---------------------------------------------
		 * 	
		 * loadQuestions - Loads quiz questions from specified file
		 *
		 * @param 	Name of file with questions
		 *
		 * @return 	True if questions loaded successfully,
		 *		    false if not
		 *
		 * -------------------------------------------- */
		bool loadQuestions(string dataFileName);

		/** ---------------------------------------------
		 * 	
		 * dumpQuestions - Outputs all questions and answers
		 *
		 * -------------------------------------------- */
		void dumpQuestions();

		/** ---------------------------------------------
		 * 	
		 * deliverQuiz - Presents quiz questions, accepts
		 *			     answers, and grades results.
		 *
		 * @return	Number of correct answers.
		 *			-1 if quiz could not be delivered.
		 *
		 * -------------------------------------------- */
		int deliverQuiz(bool showIncorrectOnly = false);

		/** ---------------------------------------------
		 * 	
		 * getNumCorrect - Indicates number of correct answers.
		 *				  Unanswered questions default to incorrect.
		 *
		 * @return	Number of correct answers
		 *
		 * -------------------------------------------- */
		int getNumCorrect();

		/** ---------------------------------------------
		 * 	
		 * getNumIncorrect - Indicates number of incorrect answers.
		 *				  Unanswered questions default to incorrect.
		 *					
		 * @return	Number of incorrect answers
		 *
		 * -------------------------------------------- */
		int getNumIncorrect();

	private:
		vector<Question*> questions;
		string filename;
		bool filenameIsValid;
		bool questionsLoaded;

		/** ---------------------------------------------
		 * 	
		 * parseQuestions - Parses lines from the questions
		 *				    file and generates Question objects
		 *
		 * @param 	Vector of lines from the questions file
		 *
		 * @return 	True if questions were parsed successfully,
		 *			false if not
		 *
		 * -------------------------------------------- */
		bool parseQuestions(vector<string> rawQuestions);

		/** ---------------------------------------------
		 * 	
		 * displayGrade - Outputs the % of correct answers
		 *
		 * @param	Number of questions answered
		 * @param	Number of correct answers
		 *
		 * -------------------------------------------- */
		void displayGrade(int numQuestions, int numCorrect);

		/** ---------------------------------------------
		 * 	
		 * removeWhitespace - Removes all whitespace from string.
		 *					 Overwrites the provided string.
		 *
		 * @param	String to trim
		 *
		 * -------------------------------------------- */
		void removeWhitespace(string &str);

		/** ---------------------------------------------
		 * 	
		 * toUpperCase - Converts string to all uppercase.
		 *	    		Overwrites the provided string.
		 *
		 * @param	String to convert
		 *
		 * -------------------------------------------- */
		void toUpperCase(string &str);

		/** ---------------------------------------------
		 * 	
		 * ignoreLine - Check if the line should be processed.
		 *
		 * @param	String containing line from file.
		 *
		 * @return	True if line should be ignored,
		 *			False if it should be processed.
		 *
		 * -------------------------------------------- */
		bool ignoreLine(string lineFromFile);

		/** ---------------------------------------------
		 * 	
		 * isValidLine - Check if the line is valid quiz question.
		 *
		 * @param	Input stream object to check.
		 * @param	Line number being validated.
		 *
		 * @return	True if line should be processed,
		 *			False if it is invalid.
		 *
		 * -------------------------------------------- */
		bool isValidLine(istringstream &q, int lineNum);

		/** ---------------------------------------------
		 * 	
		 * isValidDifficulty - Check if difficulty value is valid.
		 *
		 * @param	Difficulty value as a string.
		 * @param	Line number being validated.
		 *
		 * @return	True if diffculty is valid,
		 *			False if not.
		 *
		 * -------------------------------------------- */
		bool isValidDifficulty(string difficulty, int lineNum);

		/** ---------------------------------------------
		 * 	
		 * isValidMC - Check if MC answer is valid.
		 *
		 * @param	MC answer.
		 * @param	Line number being validated.
		 *
		 * @return	True if answer is valid,
		 *			False if not.
		 *
		 * -------------------------------------------- */
		bool isValidMC(string answer, string choices, int lineNum);

		/** ---------------------------------------------
		 * 	
		 * isValidTF - Check if TF answer is valid.
		 *
		 * @param	TF answer.
		 * @param 	Line number being validated.
		 *
		 * @return	True if anser is valid,
		 *			False if not.
		 *
		 * -------------------------------------------- */
		bool isValidTF(string answer, int lineNum);

		/** ---------------------------------------------
		 * 	
		 * countChar - Count the occurrences of a character
		 *			  within a string.
		 *
		 * @param	String containing characters to count.
		 * @param	Character to count.
		 *
		 * @return 	Number of times char was found in string.
		 *
		 * -------------------------------------------- */
		int countChar(string str, char c);
};

#endif	// QUIZ_H
