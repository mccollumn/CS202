/** ---------------------------------------------
 *
 * @file	questionsa.h
 * @author	Nick McCollum
 * @version	1.0
 *
 * CS-202 - Assignment 3 - Abstract Classes
 *		    Question class definition
 *
 * -------------------------------------------- */

#ifndef QUESTIONSA_H
#define QUESTIONSA_H

#include <string>
#include "question.h"

using namespace std;

class QuestionSA : public Question {
	public:
		// Default constructor
		QuestionSA(string questionText, string answerText);

		virtual ~QuestionSA() = default;

		/** ---------------------------------------------
		 * 	
		 * showQuestion - Outputs question text
		 *
		 * -------------------------------------------- */
		virtual void showQuestion();

		/** ---------------------------------------------
		 * 	
		 * checkAnswer - Checks if given answer is correct,
		 *				 and marks it accordingly.
		 *
		 * @param	The answer input by user
		 *
		 * @return 	True if correct, otherwise false 
		 *
		 * -------------------------------------------- */
		virtual bool checkAnswer(string givenAnswer);
};

#endif	// QUESTIONSA_H
