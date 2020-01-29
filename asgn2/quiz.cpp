#include <iostream>
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
			questions[i].showQuestion();
			cout << endl;
			questions[i].showAnswer();
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
	float percentage;

	cout << "Hope your brain's warmed up, it's Quiz Time!!!\n";
	cout << "After each answer is displayed, press Enter to see the next question.\n\n";

	for (int i = 0; i < numQuestions; i++) {
		questions[i].showQuestion();
		cout << "\n> ";
		getline(cin, givenAnswer);
		if (questions[i].checkAnswer(givenAnswer)) {
			cout << "Correct!  Great Job!\n\n";
			numCorrect++;
		}
		else {
			cout << "Sorry, the answer is ";
			questions[i].showAnswer();
			cout << ".\n\n";
		}
	}

	percentage = ((float) numCorrect / (float) numQuestions) * 100;
	cout << "You got " << numCorrect << " of " << numQuestions << " correct: " << percentage << "%.";
	if (percentage < 70) {
		cout << "\tBetter study more!\n";
	}
	else {
		cout << "\tGood job!\n";
	}

	return numCorrect;	
}

// ----------------------------------------------
bool Quiz::parseQuestions(vector<string> rawQuestions) {
	string type;
	string difficulty;
	string question;
	string answer;

	for (unsigned int i = 0; i < rawQuestions.size(); i++) {
		istringstream q(rawQuestions[i]);
		string token;

		getline(q, type, '|');
		getline(q, difficulty, '|');
		getline(q, question, '|');
		getline(q, answer, '|');

		// Confirm no issues with input stream before instantiating new Question
		if (q.fail()) {
			cerr << "ERROR: Failed reading question from file.\n";
			q.clear();
			return false;
		}

		questions.push_back(Question(question, answer));
	}

	questionsLoaded = true;
	return true;	
}
