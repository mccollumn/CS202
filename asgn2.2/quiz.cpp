#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "quiz.h"

using namespace std;

// ----------------------------------------------
Quiz::Quiz() {
	questionsLoaded = false;
}

// ----------------------------------------------
Quiz::Quiz(string dataFileName) {
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
		delete questions[i];
	}
}

// ----------------------------------------------
bool Quiz::loadQuestions(string dataFileName) {
	string question;
	vector<string> rawQuestions;
	ifstream dataFile(dataFileName.c_str());

	if (dataFile.is_open()) {
		while (getline(dataFile, question)) {
			rawQuestions.push_back(question);
		}
		dataFile.close();
	}
	else {
		cerr << "ERROR: Unable to open file: " << dataFileName << endl;
		return false;
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
			questions[i]->showQuestion();
			cout << endl;
			questions[i]->showAnswer();
			cout << endl << endl;
		}
	}
}

// ----------------------------------------------
int Quiz::deliverQuiz() {
	if (!questionsLoaded) {
		cerr << "ERROR: Cannot deliver quiz.\n";
		cerr << "No questions have been loaded.\n";
		return -1;
	}

	string givenAnswer;
	int numQuestions = questions.size();
	int numCorrect = 0;

	cout << "Hope your brain's warmed up, it's Quiz Time!!!\n";
	cout << "After each answer is displayed, press Enter to see the next question.\n\n";

	for (int i = 0; i < numQuestions; i++) {
		questions[i]->showQuestion();
		cout << "\n> ";
		getline(cin, givenAnswer);
		if (questions[i]->checkAnswer(givenAnswer)) {
			cout << "Correct!  Great Job!\n\n";
			numCorrect++;
		}
		else {
			cout << "Sorry, the answer is ";
			questions[i]->showAnswer();
			cout << ".\n\n";
		}
	}

	displayGrade(numQuestions, numCorrect);

	return numCorrect;	
}

// ----------------------------------------------
bool Quiz::parseQuestions(vector<string> rawQuestions) {
	string type;
	string difficulty;
	string question;
	string choices;
	string answer;

	for (unsigned int i = 0; i < rawQuestions.size(); i++) {
		istringstream q(rawQuestions[i]);

		getline(q, type, '|');
		getline(q, difficulty, '|');
		getline(q, question, '|');
		if (type == "M" || type == "m") {
			getline(q, choices, '|');
		}
		getline(q, answer, '|');

		// Confirm no issues with input stream before instantiating new Question
		if (q.fail()) {
			cerr << "ERROR: Failed reading question from file.\n";
			q.clear();
			return false;
		}

		if (type == "S" || type == "s") {
			questions.push_back(new Question(question, answer));
		}
		else if (type == "T" || type == "t") {
			questions.push_back(new QuestionTF(question, answer));
		}
		else if (type == "M" || type == "m") {
			questions.push_back(new QuestionMC(question, answer, choices));
		}
		else {
			cerr << "ERROR: Unknown question type.\n";
			return false;
		}
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
