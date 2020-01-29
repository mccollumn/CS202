/** ---------------------------------------------
*
* @file		stringTest.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-202 - Assignment 1 - Operator Overloading
*		   Demonstrates MyString class functionality
*
* -------------------------------------------- */

#include <iostream>
#include "mystring.h"

int main(int argc, char* argv[]) {

	// Read cmd line args into strings array
	MyString* strings;
	int numStrings = argc - 1;
	if (argc > 1) {
		strings = new MyString[numStrings];
		for (int i = 0; i < numStrings; i++) {
			strings[i] = MyString(argv[i + 1]);
		}
	}
	else {
		std::cerr << "Usage: stringTest <strings>" << std::endl;
		return 1;
	}

	//Print the strings
	for (int i = 0; i < numStrings; i++) {
		std::cout << strings[i] << " ";
	}
	std::cout << std::endl;

	// Print how first string compares to last
	std::cout << "The first string (" << strings[0] << ") is ";
	if (strings[0] < strings[numStrings - 1]) {
		std::cout << "less than ";
	}
	else if (strings[0] > strings[numStrings - 1]) {
		std::cout << "greater than ";
	}
	else if (strings[0] == strings[numStrings - 1]) {	//Do this one to test ==
		std::cout << "equal to ";
	}
	std::cout << "the last string (" << strings[numStrings - 1] << ")." << std::endl;

	// Remove last letter and reprint
	for (int i = 0; i < numStrings; i++) {
		std::cout << --strings[i] << " ";
	}
	std::cout << std::endl;

	// Add first and last string
	MyString combined;
	combined = strings[0]-- + --strings[numStrings - 1];
	std::cout << combined << std::endl;

	// Capitalize and print again
	std::cout << combined.uppercase() << std::endl;

	// Change printAsUppercase = true and reprint
	MyString::setPrintAsUppercase(true);
	for (int i = 0; i < numStrings; i++) {
		std::cout << strings[i] << " ";
	}
	std::cout << std::endl;
	
	return 0;
}
