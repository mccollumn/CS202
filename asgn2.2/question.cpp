/** ---------------------------------------------
*
* @file		question.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-202 - Assignment 2 - Inheritance & Polymorphism
*		   Question class implementation
*
* -------------------------------------------- */

#include <iostream>
#include <algorithm>
#include "question.h"

using namespace std;

// ----------------------------------------------
Question::Question(string questionText = "", string answerText = "") {
	this->questionText = questionText;
	this->answerText = answerText;
	correct = false;

	// These are not currently used
	type = "";
	difficulty = 0;
}

// ----------------------------------------------
void Question::showQuestion() {
	cout << questionText;
	cout << "?";
}

void Question::showAnswer() {
	cout << answerText;
}

// ----------------------------------------------
bool Question::checkAnswer(string givenAnswer) {
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

// ----------------------------------------------
void Question::markCorrect() {
	correct = true;
}

// ----------------------------------------------
void Question::removeWhitespace(string &str) {
	str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}

// ----------------------------------------------
void Question::toLowerCase(string &str) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}
