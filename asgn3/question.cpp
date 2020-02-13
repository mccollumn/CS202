/** ---------------------------------------------
*
* @file		question.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-202 - Assignment 3 - Abstract Classes
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
void Question::showAnswer() {
	cout << answerText;
}

// ----------------------------------------------
void Question::markCorrect() {
	correct = true;
}

// ----------------------------------------------
bool Question::isCorrect() {
	return correct;
}

// ----------------------------------------------
void Question::removeWhitespace(string &str) {
	str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}

// ----------------------------------------------
void Question::toLowerCase(string &str) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}
