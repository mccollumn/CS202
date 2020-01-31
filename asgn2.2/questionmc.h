/** ---------------------------------------------
 *
 * @file	questionmc.h
 * @author	Nick McCollum
 * @version	1.0
 *
 * CS-202 - Assignment 2 - Inheritance & Polymorphism
 *		    QuestionMC class definition
 *
 * -------------------------------------------- */

#ifndef QUESTIONMC_H
#define QUESTIONMC_H

#include <string>
#include <vector>
#include "question.h"

using namespace std;

class QuestionMC : public Question {
	public:
		// Default constructor
		QuestionMC(string questionText, string answerText, string answerChoices);

		virtual ~QuestionMC() = default;

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

	private:
		string answerChoices;

		/** ---------------------------------------------
		 * 	
		 * parseChoices - Populates vector with multiple
		 *				 choice answers
		 *
		 * @param	The vector to be populated
		 *
		 * @return	True if data parsed successfully,
		 *			false if not
		 *
		 * -------------------------------------------- */
		bool parseChoices(vector<string> &choices);
};

#endif	// QUESTIONMC_H
