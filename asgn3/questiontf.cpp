/** ---------------------------------------------
*
* @file		questiontf.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-202 - Assignment 3 - Abstract Classes
*		   QuestionTF class implementation
*
* -------------------------------------------- */

#include <iostream>
#include "questiontf.h"

using namespace std;

// ----------------------------------------------
QuestionTF::QuestionTF(string questionText = "", string answerText = "")
	: Question(questionText, answerText)
{
	this->questionText = questionText;
	this->answerText = answerText;
	correct = false;
}

// ----------------------------------------------
void QuestionTF::showQuestion() {
	cout << questionText;
	cout << ". (True or False)";
}

// ----------------------------------------------
bool QuestionTF::checkAnswer(string givenAnswer) {
	string actualAnswer = answerText;

	// Remove whitespace and convert to lower
	removeWhitespace(actualAnswer);
	removeWhitespace(givenAnswer);
	toLowerCase(actualAnswer);
	toLowerCase(givenAnswer);

	if (givenAnswer.size() == 1 && givenAnswer.at(0) == actualAnswer.at(0)) {
		markCorrect();
		return true;
	}
	if (givenAnswer.compare(actualAnswer) == 0) {
		markCorrect();
		return true;
	}
	return false;
}
