/** ---------------------------------------------
 *
 * @file	question.h
 * @author	Nick McCollum
 * @version	1.0
 *
 * CS-202 - Assignment 3 - Abstract Classes 
 *		    Question class definition
 *
 * -------------------------------------------- */

#ifndef QUESTION_H
#define QUESTION_H

#include <string>

using namespace std;

class Question {
	public:
		// Default constructor
		Question(string questionText, string answerText);

		virtual ~Question() = default;

		/** ---------------------------------------------
		 * 	
		 * showQuestion - Outputs question text
		 *
		 * -------------------------------------------- */
		virtual void showQuestion() = 0;

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
		virtual bool checkAnswer(string givenAnswer) = 0;

		/** ---------------------------------------------
		 * 	
		 * markCorrect - Marks an answer correct
		 *
		 * -------------------------------------------- */
		void markCorrect();

		/** ---------------------------------------------
		 * 	
		 * isCorrect - Indicates whether the question has
		 *			  been marked correct.
		 *
		 * @return	True if correct, otherwise false
		 *
		 * -------------------------------------------- */
		bool isCorrect();

	protected:
		string type;
		int difficulty;
		string questionText;
		string answerText;
		bool correct;

		/** ---------------------------------------------
		 * 	
		 * removeWhiteSpace - Removes all whitespace from a string
		 *
		 * @param 	The string to modify
		 *
		 * -------------------------------------------- */
		void removeWhitespace(string &str);

		/** ---------------------------------------------
		 * 	
		 * toLowerCase - Converts string to lower case
		 *
		 * @param 	The string to convert
		 *
		 * -------------------------------------------- */
		void toLowerCase(string &str);
};

#endif	// QUESTION_H
