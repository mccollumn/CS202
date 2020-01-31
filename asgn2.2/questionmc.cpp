/** ---------------------------------------------
*
* @file		questionmc.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-202 - Assignment 2 - Inheritance & Polymorphism
*		   QuestionMC class implementation
*
* -------------------------------------------- */

#include <iostream>
#include <sstream>
#include "questionmc.h"

using namespace std;

// ----------------------------------------------
QuestionMC::QuestionMC(string questionText = "", string answerText = "", string answerChoices = "")
	: Question(questionText, answerText)
{
	this->questionText = questionText;
	this->answerText = answerText;
	this->answerChoices = answerChoices;
	correct = false;
}

// ----------------------------------------------
void QuestionMC::showQuestion() {
	vector<string> choices;
	parseChoices(choices);

	cout << questionText;
	cout << "?";

	char choiceLetter = 'a';
	for (unsigned int i = 0; i < choices.size(); i++) {
		cout << "\n   " << choiceLetter << ") ";
		cout << choices[i];
		choiceLetter++;
	}
}

void QuestionMC::showAnswer() {
	cout << answerText;
}

// ----------------------------------------------
bool QuestionMC::checkAnswer(string givenAnswer) {
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

// ----------------------------------------------
bool QuestionMC::parseChoices(vector<string> &choices) {
	istringstream choiceStream(answerChoices);
	string token;

	while (!choiceStream.eof()) {
		getline(choiceStream, token, ':');
		choices.push_back(token);
	}

	if (choiceStream.fail()) {
		cerr << "ERROR: Failed reading multiple choice answers.\n";
		choiceStream.clear();
		return false;
	}

	return true;
}
