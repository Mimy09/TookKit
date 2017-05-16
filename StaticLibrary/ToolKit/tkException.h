// ################################################################## //
// ##							TOOL KIT						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Feb 15 - AIE			   ## //
// ################################################################## //
#pragma once
#include "tkString.h"

namespace tk {
	// -------------------------- TK_EXCEPTION -------------------------- //
	class Exception {
		// msg is for storing the argument, file and line number
		tk::String msg;
	public:
		// Constructor
		Exception(const String arg, const char *file, int line) {
			// Get the file path
			msg = file;
			// Split the file path to only show the last file
			msg = msg.cSplit('\\', msg.countChar('\\'));
			// Add the line number and the argument to the message
			msg += (String)":" + (String)line + (String)": " + arg;
		}
		// Deconstructor
		~Exception() throw() {}
		// Returns the message that was populated in the constructor
		const char* what() const throw() { return msg.data; }

		// Displays a message box on the screen showing what the error was
		const void msgWhat() const {
			// Creates and displays a message box
			MessageBox(NULL, what(), "#### FATAL ERROR ####", MB_ICONERROR | MB_OK);
		}
		// Displays a message box on the screen showing what the error was
		// Overloaded to alow change of the message box title
		const void msgWhat(char* title) const {
			// Creates and displays a message box
			MessageBox(NULL, what(), title, MB_ICONERROR | MB_OK);
		}
		// Displays a message box on the screen showing what the error was
		// Overloaded to alow change of the message box title and change the type of message box
		int msgWhat(char* title, UINT type) const {
			// Creates and displays a message box
			int msgboxID = MessageBox(NULL, what(), title, type);
			return msgboxID;
		}
	};
}
// CALLS THE EXEPTION CLASS AND PASSES THROUGH THE ARGUMENT, FILE PATH AND THE LINE NUMBER
#define TK_EXCEPTION(arg) throw tk::Exception(arg, __FILE__, __LINE__);