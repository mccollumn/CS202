/** ---------------------------------------------
*
* @file		questionsa.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-202 - Assignment 3 - Abstract Classes
*		   Question class implementation
*
* -------------------------------------------- */

#include <iostream>
#include <algorithm>
#include "questionsa.h"

using namespace std;

// ----------------------------------------------
QuestionSA::QuestionSA(string questionText = "", string answerText = "")
	: Question(questionText, answerText)
{
	this->questionText = questionText;
	this->answerText = answerText;
	correct = false;
}

// ----------------------------------------------
void QuestionSA::showQuestion() {
	cout << questionText;
	cout << "?";
}

// ----------------------------------------------
bool QuestionSA::checkAnswer(string givenAnswer) {
	string actualAnswer = answerText;

	// Remove whitespace and convert to lower
	removeWhitespace(actualAnswer);
	removeWhitespace(givenAnswer);
	toLowerCase(actualAnswer);
	toLowerCase(givenAnswer);

	if (givenAnswer.compare(actualAnswer) != 0) {
		return false;
	}

	markCorrect();
	return true;
}
