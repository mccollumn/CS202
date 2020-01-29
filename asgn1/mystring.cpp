/** ---------------------------------------------
*
* @file		mystring.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-202 - Assignment 1 - Operator Overloading
*		   MyString class implementation
*
* -------------------------------------------- */

#include <iostream>
#include "mystring.h"

// If true, all strings print in uppercase
bool MyString::printAsUppercase = false;

// ----------------------------------------------
MyString::MyString(const char data[]) {
	length = strLength(data);
	this->data = new char[length];
	strCopy(this->data, data);
}

// ----------------------------------------------
MyString::MyString(MyString& string) {
	length = string.length;
	data = new char[string.length];
	strCopy(data, string.data);
}

// ----------------------------------------------
MyString::~MyString() {
	delete[] data;
}

// ----------------------------------------------
MyString MyString::operator+(const MyString& string2) {
	MyString newString;
	if (length + string2.length > 0) {
		char* newData = new char[(length + string2.length)];
		int currentIndex;

		for (currentIndex = 0; currentIndex < length; currentIndex++) {
			newData[currentIndex] = data[currentIndex];
		}
		for (int str2Index = 0; str2Index < string2.length; str2Index++) {
			newData[currentIndex++] = string2.data[str2Index];
		}
		newString = newData;
	}

	return newString;
}

// ----------------------------------------------
MyString& MyString::operator=(const MyString& src) {
	if (this == &src) {
		return *this;
	}

	delete[] data;
	data = new char[src.length];
	strCopy(data, src.data);
	length = src.length;

	return *this;
}

// ----------------------------------------------
bool operator==(MyString& string1, const MyString& string2) {
	if (string1.strCompare(string2) == 0) {
		return true;
	}
	return false;
}

// ----------------------------------------------
bool operator>(const MyString& string1, const MyString& string2) {
	if (string1.strCompare(string2) > 0) {
		return true;
	}
	return false;
}

// ----------------------------------------------
bool operator<(const MyString& string1, const MyString& string2) {
	if (string1.strCompare(string2) < 0) {
		return true;
	}
	return false;
}

// ----------------------------------------------
MyString& MyString::operator--() {
	if (length > 0) {
		length--;
	}
	return *this;
}

// ----------------------------------------------
MyString MyString::operator--(int) {
	MyString tmp(*this);
	operator--();
	return tmp;
}

// ----------------------------------------------
std::ostream& operator<<(std::ostream& os, const MyString& string) {
	const unsigned char* strChar;
	MyString upper;

	if (MyString::printAsUppercase) {
		upper = string.uppercase();
		strChar = (const unsigned char*) upper.data;
	}
	else {
		strChar = (const unsigned char*) string.data;
	}

	for (int strPosition = 1; strPosition <= string.length; strPosition++) {
		os << *strChar;
		strChar++;
	}
	os << "(" << string.length << ")";

	return os;
}

// ----------------------------------------------
std::istream& operator>>(std::istream& is, MyString& string) {
	is >> string.data;
	return is;
}

// ----------------------------------------------
MyString MyString::uppercase() const{
	if (length <= 0) {
		MyString blank;
		return blank;
//		return this;
	}

	char * newString = new char[length];
	const unsigned char* srcChar = (const unsigned char*) data;
	unsigned char* destChar = (unsigned char*) newString;

	for (int strPosition = 1; strPosition <= length; strPosition++) {
		if (*srcChar > 96 && *srcChar < 123) {
			*destChar = *srcChar - 32;
		}
		else {
			*destChar = *srcChar;
		}
		srcChar++;
		destChar++;
	}
	MyString upperString(newString);
	upperString.length = length;
	return upperString;
}

// ----------------------------------------------
int MyString::getLength() {
	return length;
}

// ----------------------------------------------
int MyString::strLength(const char string[]) {
	int length = 0;
	const unsigned char* strLocation = (const unsigned char*) string;
	for (; *strLocation != '\0'; strLocation++) {
		length++;
	}
	return length;
}

// ----------------------------------------------
bool MyString::strCopy(char* destString, const char* srcString) {
	return memcpy(destString, srcString, strLength(srcString));
}

// ----------------------------------------------
int MyString::strCompare(const MyString& string2) const {
	const unsigned char* str1Char = (const unsigned char*) data;
	const unsigned char* str2Char = (const unsigned char*) string2.data;
	int strLoc = 1;

	while (strLoc <= length && strLoc <= string2.length) {
		if (*str1Char > *str2Char) {
			return 1;
		}
		if (*str2Char > *str1Char) {
			return -1;
		}
		str1Char++;
		str2Char++;
		strLoc++;
	}

	if (length == string2.length) {
		return 0;
	}
	if (length > string2.length) {
		return 1;
	}
	return -1;
}

// ----------------------------------------------
void MyString::setPrintAsUppercase(bool trueFalse) {
	printAsUppercase = trueFalse;
}


// Test code for class functions
/*
   int main() {
   MyString str1("test");
// Test getLength method
std::cout << "getLength()" << std::endl;
std::cout << "getLength test: " << str1.getLength() << std::endl << std::endl;

// Test copy constructor and output stream
MyString copyStr(str1);
std::cout << "Copy (constructor) length: " << copyStr.getLength() << std::endl;
std::cout << "Copy (constructor) value: " << copyStr << std::endl;

// Test assignment overload
MyString newStr("foo");
copyStr = newStr;
std::cout << "Copy (Assignment) length: " << copyStr.getLength() << std::endl;
std::cout << "Copy (Assugnment) value: " << copyStr << std::endl;

// Test input stream and confirm deep copy
std::cout << "Enter value to replace copied string (confirm deep copy): " << std::endl;
std::cin >> copyStr;
std::cout << "Source string: " << newStr << std::endl;
std::cout << "Copy string: " << copyStr << std::endl;

// Test + overload
MyString str2("ing");
newStr = str1 + str2;
std::cout << "+ test (str1 + str2): " << newStr << std::endl;
std::cout << newStr.getLength() << std::endl << std::endl;

// Test ==
std::cout << "==" << std::endl;
MyString str3("testing2");
if (newStr == str3)
std::cout << "newStr (" << newStr << ") equals str3 (" << str3 << ")" << std::endl;
else
std::cout << "newStr (" << newStr << ") does not equal str3 (" << str3 << ")" << std::endl << std::endl;

// Test >
std::cout << ">" << std::endl;
if (newStr > str3)
std::cout << "newStr (" << newStr << ") > str3 (" << str3 << ")" << std::endl;
else
std::cout << "newStr (" << newStr << ") not > str3 (" << str3 << ")" << std::endl;

// Test strCompare
std::cout << "strCompare" << std::endl;
if (newStr.strCompare(str3) > 0) {
std::cout << "newStr (" << newStr << ") > str3 (" << str3 << ")" << std::endl;
}
if (newStr.strCompare(str3) < 0) {
std::cout << "newStr (" << newStr << ") < str3 (" << str3 << ")" << std::endl;
}
if (newStr.strCompare(str3) == 0) {
std::cout << "newStr (" << newStr << ") == str3 (" << str3 << ")" << std::endl;
}

// Test Uppercase
std::cout << "Uppercase: " << newStr.uppercase() << std::endl << std::endl;

// Test setPrintAsUppercase
MyString::setPrintAsUppercase(true);
std::cout << "Uppercase (setPrintAsUppercase): " << newStr << std::endl << std::endl;

// Test predecrement
std::cout << "Pre decrement: " << --newStr << std::endl;

// Test post decrement
std::cout << "Post decrement: " << newStr-- << std::endl;


return 0;
}
*/
