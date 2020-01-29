/** ---------------------------------------------
 *
 * @file	mystring.h
 * @author	Nick McCollum
 * @version	1.0
 *
 * CS-202 - Assignment 1 - Operator Overloading
 *		   MyString call definition
 *
 * -------------------------------------------- */

#include <iostream>
#include <cstring>

class MyString	{
	public:
		MyString(const char data[] = "");
		MyString(MyString& string);
		~MyString();

		// Overloads
		MyString operator+(const MyString& string2);
		MyString& operator=(const MyString& src);
		friend bool operator==(MyString& string1, const MyString& string2);
		friend bool operator>(const MyString& string1, const MyString& string2);
		friend bool operator<(const MyString& string1, const MyString& string2);
		MyString& operator--();
		MyString operator--(int);

		// Output stream will include the string length
		friend std::ostream& operator<<(std::ostream& os, const MyString& string);
		friend std::istream& operator>>(std::istream& is, MyString& string);


		/** ---------------------------------------------
		 * 	
		 * uppercase - Converts the string to all uppercase
		 *
		 * @return  A new string object in uppercase
		 *
		 * -------------------------------------------- */
		MyString uppercase() const;


		/** ---------------------------------------------
		 * 	
		 * getLength - Gets the length of the string.
		 *			  No terminating null character.
		 *
		 * @return  The number of characters in string
		 *
		 * -------------------------------------------- */
		int getLength();


		/** ---------------------------------------------
		 * 	
		 * strCompare - Compares the value of a string object
		 *			   with the value of the string it was called on.
		 *
		 * @param   String object to compare
		 *
		 * @return  An int indicating how string 2 compares to string 1
		 *		   <0 string 1 is smaller
		 *		   0 strings are equaal
		 *		   >0 string 1 is larger
		 *
		 * -------------------------------------------- */
		int strCompare(const MyString& string2) const;


		/** ---------------------------------------------
		 * 	
		 * setPrintAsUppercase - Sets whether strings will
		 *						all uppercase
		 *
		 * @param 	True if all uppercase, false if not
		 *
		 * -------------------------------------------- */
		static void setPrintAsUppercase(bool trueFalse);

	private:
		char* data;
		int length;
		static bool printAsUppercase;


		/** ---------------------------------------------
		 * 	
		 * strLength - Counts the number of characters in string
		 *
		 * @param 	Pointer to string
		 *
		 * @return 	Length of string
		 *
		 * -------------------------------------------- */
		int strLength(const char string[]);


		/** ---------------------------------------------
		 * 	
		 * strCopy - Copies a string
		 *
		 * @param 	destString - string to copy into
		 * @param 	srcString - string to copy from
		 *
		 * @return  	True if copy was successful,
		 *			false otherwise
		 *
		 * -------------------------------------------- */
		bool strCopy(char* destString, const char* srcString);
};
