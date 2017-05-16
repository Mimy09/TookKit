// ################################################################## //
// ##							TOOL KIT						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Feb 15 - AIE			   ## //
// ################################################################## //

#pragma once
#include <stdio.h>
#include <Windows.h>
#pragma warning(disable: 4996)

// MEMORY SAFE DELETE FOR CHAR ARRAY POINTER // #### DO NOT DELETE #### //
#define SAFE_ARRAY_DELETE(p_)   \
{                               \
    if(p_ != nullptr)           \
    {                           \
        delete[] p_;            \
        p_ = nullptr;           \
    }                           \
}

// Limit for the creation of char pointers in memory
#define tk_CHAR_LIMIT 16
#define tk_BIT_LIMIT 32

namespace tk {
	// -------------------------- STRING -------------------------- //
	class String {
	public:

		// Storse the string data that will be used for getting the data form the
		// overloaded operaters
		char* data = new char[tk_CHAR_LIMIT];



		String(); // Defalt constructor
		String(const String& other); // Copy constructor
		String(const char* str); // Copy constructor
		String(const char str); // Copy constructor

		// Does type conversion inside copy constructor
		String(const int value);
		String(const float value);
		String(const double value);


		~String(); // Defalt deconstructor


		// Overloads the = operater to copy the data across for the other string
		void operator=(const char* str);
		void operator=(const String& other);
		void operator=(const int other);
		void operator=(const float other);
		void operator=(const double other);

		// Overloads the += operater alowing addtion onto the end on the string
		void operator+=(const char* str);
		void operator+=(const String& other);
		void operator+=(const int other);
		void operator+=(const float other);
		void operator+=(const double other);

		// Overloads the + operater alowing addtion onto the end on the string but does not change the data
		String operator+(const char* str);
		String operator+(const String& other);

		// Gets the length of a string by looking for the nul terminator
		int length(const char* str);
		int length(const String& str);
		int length();

		// Print data to console using STD::COUT
		void print_tk();
		void println_tk();

		// Returns a char array of this string data
		char* toChar();

		// Returns a int
		int toInt();

		// Splits a string at a char
		char* cSplit(char stopChar, int position);
		String sSplit(char stopChar, int position);

		// Replace a word in a string
		void replace(char splitChar, char* value);
		void replace(char splitChar, String& value);

		// Find out how many of this character is in the string
		int countChar(char character);

	private:

		// Copys a char across bit by bit and changes the data length of the char to the
		// new chars length
		void strCopy(char** dest, const char* str);
		void strCopy(char* dest, const char* str);
		void strCopy(char** dest, const char str);


		// Adds a array of chars to the end of the oraigonal data in the string
		void strAdd(char** dest, const char* str);
		String strAddS(const char* dest, const char* str);
	};
}