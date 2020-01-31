/** ---------------------------------------------
 *
 * @file	questiontf.h
 * @author	Nick McCollum
 * @version	1.0
 *
 * CS-202 - Assignment 2 - Inheritance & Polymorphism
 *		    QuestionTF class definition
 *
 * -------------------------------------------- */

#ifndef QUESTIONTF_H
#define QUESTIONTF_H

#include <string>
#include "question.h"

using namespace std;

class QuestionTF : public Question {
	public:
		// Default constructor
		QuestionTF(string questionText, string answerText);

		virtual ~QuestionTF() = default;

		/** ---------------------------------------------
		 * 	
		 * showQuestion - Outputs question text
		 *
		 * -------------------------------------------- */
		virtual void showQuestion();

		/** ---------------------------------------------
		 * 	
		 * showAnswer - Output answer text
		 *
		 * -------------------------------------------- */
		virtual void showAnswer();

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

		/** ---------------------------------------------
		 * 	
		 * markCorrect - Marks an answer correct
		 *
		 * -------------------------------------------- */
};

#endif	// QUESTIONTF_H
