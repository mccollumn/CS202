/** ---------------------------------------------
*
* @file		questiontf.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-202 - Assignment 2 - Inheritance & Polymorphism
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

void QuestionTF::showAnswer() {
	cout << answerText;
}

// ----------------------------------------------
bool QuestionTF::checkAnswer(string givenAnswer) {
	string actualAnswer = answerText;

	// Remove whitespace and convert to lower
	removeWhitespace(actualAnswer);
	removeWhitespace(givenAnswer);
	toLowerCase(actualAnswer);
	toLowerCase(givenAnswer);

	if (givenAnswer[0] != actualAnswer[0]) {
		return false;
	}

	markCorrect();
	return true;
}
