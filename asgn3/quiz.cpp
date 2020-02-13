/** ---------------------------------------------
 *
 * @file	quiz.cpp
 * @author	Nick McCollum
 * @version	1.0
 *
 * CS-202 - Assignment 3 - Abstract Classes
 *		   Quiz class implementation
 *
 * -------------------------------------------- */

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "quiz.h"

using namespace std;

// ----------------------------------------------
Quiz::Quiz() {
	filename = string();
	filenameIsValid = false;
	questionsLoaded = false;
}

// ----------------------------------------------
Quiz::Quiz(string dataFileName) {
	filename = dataFileName;

	if (loadQuestions(dataFileName)) {
		questionsLoaded = true;
	}
	else {
		questionsLoaded = false;
	}
}

// ----------------------------------------------
Quiz::~Quiz() {
	for (unsigned int i = 0; i < questions.size(); i++) {
		delete questions.at(i);
	}
}

// ----------------------------------------------
bool Quiz::loadQuestions(string dataFileName) {
	filename = dataFileName;
	string question;
	vector<string> rawQuestions;
	ifstream dataFile(dataFileName.c_str());

	if (questionsLoaded) {
		questions.clear();
	}

	if (dataFile.is_open()) {
		filenameIsValid = true;
		while (getline(dataFile, question)) {
			rawQuestions.push_back(question);
		}
		dataFile.close();
	}
	else {
		filenameIsValid = false;
		string error = "Error: Unable to open " + dataFileName;
		throw error;
	}

	return parseQuestions(rawQuestions);
}

// ----------------------------------------------
void Quiz::dumpQuestions() {
	if (!questionsLoaded) {
		cerr << "ERROR: Cannot dump quiz questions.\n";
		cerr << "No questions have been loaded.\n";
	}
	else {
		for (unsigned int i = 0; i < questions.size(); i++) {
			questions.at(i)->showQuestion();
			cout << endl;
			questions.at(i)->showAnswer();
			cout << endl << endl;
		}
	}
}

// ----------------------------------------------
int Quiz::deliverQuiz(bool showIncorrectOnly) {
	if (!questionsLoaded) {
		cerr << "ERROR: Cannot deliver quiz.\n";
		cerr << "No questions have been loaded.\n";
		return -1;
	}

	string givenAnswer;
	int numQuestions = questions.size();

	if (!showIncorrectOnly) {
		cout << "Hope your brain's warmed up, it's Quiz Time!!!\n";
		cout << "After each answer is displayed, press Enter to see the next question.\n\n";
	}

	for (int i = 0; i < numQuestions; i++) {
		if (!showIncorrectOnly || (showIncorrectOnly && !questions.at(i)->isCorrect())) {
			questions.at(i)->showQuestion();
			cout << "\n> ";
			getline(cin, givenAnswer);
			if (questions.at(i)->checkAnswer(givenAnswer)) {
				cout << "Correct!  Great Job!\n\n";
				questions.at(i)->markCorrect();
			}
			else {
				cout << "Sorry, the answer is ";
				questions.at(i)->showAnswer();
				cout << ".\n\n";
			}
		}
	}

	int numCorrect = getNumCorrect();
	displayGrade(numQuestions, numCorrect);

	return numCorrect;	
}

// ----------------------------------------------
int Quiz::getNumCorrect() {
	int numCorrect = 0;
	for (unsigned int i = 0; i < questions.size(); i++) {
		if (questions.at(i)->isCorrect()) {
			numCorrect++;
		}
	}

	return numCorrect;
}

// ----------------------------------------------
int Quiz::getNumIncorrect() {
	return questions.size() - getNumCorrect();
}

// ----------------------------------------------
bool Quiz::parseQuestions(vector<string> rawQuestions) {
	string type;
	string difficulty;
	string question;
	string choices;
	string answer;

	for (unsigned int i = 0; i < rawQuestions.size(); i++) {
		if (ignoreLine(rawQuestions[i])) {
			continue;
		}

		istringstream q(rawQuestions[i]);
		getline(q, type, '|');
		getline(q, difficulty, '|');
		getline(q, question, '|');
		removeWhitespace(type);
		toUpperCase(type);
		if (type == "M") {
			getline(q, choices, '|');
		}
		getline(q, answer, '|');

		removeWhitespace(difficulty);
		if (!isValidLine(q, i + 1) || !isValidDifficulty(difficulty, i + 1)) {
			q.clear();
			continue;
		}

		if (type == "S") {
			questions.push_back(new QuestionSA(question, answer));
		}
		else if (type == "T") {
			removeWhitespace(answer);
			if (isValidTF(answer, i + 1)) {
				questions.push_back(new QuestionTF(question, answer));
			}
		}
		else if (type == "M") {
			removeWhitespace(answer);
			toUpperCase(answer);
			if (isValidMC(answer, choices, i + 1)) {
				questions.push_back(new QuestionMC(question, answer, choices));
			}	
		}
		else {
			// Question type was not one of the expected values
			cerr << "ERROR: Line " << i + 1 << " - Failed reading question from file.";
			cerr << " Unknown question type.\n";
		}
	}

	if (questions.size() == 0) {
		questionsLoaded = false;
		return false;
	}

	questionsLoaded = true;
	return true;	
}

// ----------------------------------------------
void Quiz::displayGrade(int numQuestions, int numCorrect) {
	float percentage;

	percentage = ((float) numCorrect / (float) numQuestions) * 100;
	cout << "You got " << numCorrect << " of " << numQuestions << " correct: ";
	cout << round(percentage) << "%.";
	if (percentage < 70) {
		cout << "\tBetter study more!\n";
	}
	else {
		cout << "\tGood job!\n";
	}
}

// ----------------------------------------------
void Quiz::removeWhitespace(string &str) {
	str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}

// ----------------------------------------------
void Quiz::toUpperCase(string &str) {
	transform(str.begin(), str.end(), str.begin(), ::toupper);
}

// ----------------------------------------------
bool Quiz::ignoreLine(string lineFromFile) {
	removeWhitespace(lineFromFile);

	// Check for blank line
	if (lineFromFile.length() == 0) {
		return true;
	}

	// Check for comment
	if (lineFromFile.length() > 0 && lineFromFile.at(0) == '#') {
		return true;
	}

	return false;
}

// ----------------------------------------------
bool Quiz::isValidLine(istringstream &q, int lineNum) {
	// Check if there are too many fields
	if (q.rdbuf()->in_avail() != 0) {
		cerr << "ERROR: Line " << lineNum << " - Failed reading question from file.";
		cerr << " Too many fields.\n";
		return false;
	}

	if (q.fail()) {
		// Check for too few fields
		if (q.eof()) {
			cerr << "ERROR: Line " << lineNum << " - Failed reading question from file.";
			cerr << " Too few fields.\n";
		}
		// Check for other issues with input stream
		else {
			cerr << "ERROR: Line " << lineNum << " - Failed reading question from file.\n";
		}
		return false;
	}
	return true;
}

// ----------------------------------------------
bool Quiz::isValidDifficulty(string difficulty, int lineNum) {
	// Check that difficulty is between 1 - 9
	if (difficulty.length() < 1 || stoi(difficulty) < 1 || stoi(difficulty) > 9) {
		cerr << "ERROR: Line " << lineNum << " - Failed reading question from file.";
		cerr << " Invalid difficulty. Expected 1 - 9.\n";
		return false;
	}
	return true;
}

// ----------------------------------------------
bool Quiz::isValidMC(string answer, string choices, int lineNum) {
	// MC answer can't be more than one character
	if (answer.length() != 1) {
		cerr << "ERROR: Line " << lineNum << " - Failed reading question from file.";
		cerr << " Invalid multiple choice answer.\n";
		return false;
	}

	// Check that there are at least two MC answers
	int numChoices = countChar(choices, ':') + 1;
	if (numChoices <= 1) {
		cerr << "ERROR: Line " << lineNum << " - Failed reading question from file.";
		cerr << " Multiple choice questions need at least two answers.\n";
		return false;
	}

	// Check that the MC answer matches the nuymber of choices.
	// e.g. If four possible answers, then E is invalid.
	if ((answer.at(0) - 'A') >= numChoices) {
		cerr << "ERROR: Line " << lineNum << " - Failed reading question from file.";
		cerr << " The multiple choice answer is not one of the choices.\n";
		return false;
	}
	return true;
}

// ----------------------------------------------
bool Quiz::isValidTF(string answer, int lineNum) {
	// Check for valid true/false answer values
	toUpperCase(answer);
	vector<string> validAnswers = {"TRUE", "T", "FALSE", "F"};
	for (unsigned int i = 0; i < validAnswers.size(); i++) {
		if (validAnswers.at(i) == answer) {
			return true;
		}
	}
	cerr << "ERROR: Line " << lineNum << " - Failed reading question from file.";
	cerr << " Invalid True/False answer.\n";
	return false;
}

// ----------------------------------------------
int Quiz::countChar(string str, char c) {
	int count = 0;

	for (unsigned int i = 0; i < str.length(); i++) {
		if (str.at(i) == c) {
			count++;
		}
	}
	return count;
}
