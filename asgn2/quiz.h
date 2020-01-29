/** ---------------------------------------------
 *
 * @file	quiz.h
 * @author	Nick McCollum
 * @version	1.0
 *
 * CS-202 - Assignment 2 - Inheritance & Polymorphism
 *		    Quiz class definition
 *
 * -------------------------------------------- */

#ifndef QUIZ_H
#define QUIZ_H

#include <vector>
#include <string>
#include "question.h"

using namespace std;

class Quiz {
	public:
		//Constructors
		Quiz();
		Quiz(string dataFileName);

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
		int deliverQuiz();

	private:
		std::vector<Question> questions;
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
};

#endif	// QUIZ_H
