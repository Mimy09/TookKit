// ################################################################## //
// ##							EXEPTIONS						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Feb 15 - AIE			   ## //
// ################################################################## //
#pragma once

_BPD_BEGIN
/* ---- EXCEPTION ---- */
class Exception {
	/* msg is for storing the argument, file and line number */
	char* msg;
public:
	/* ---- CONSTRUCTOR ----
	Constructor for Exception
	@param arg - Argument for the exception
	@param file - What file was the exception found in
	@param line - The line the exception was found on */
	Exception(char* arg, const char *file, int line);
	/* ---- DECONSTRUCTOR ----
	Deconstructor for Exception */
	~Exception() throw();
	/* ---- WHAT ----
	Returns the message that was populated in the constructor
	@return char* - The exception message */
	const char* what() const throw();

	/* ---- MSG WHAT ---- 
	Displays a message box on the screen showing what the error is */
	const void msgWhat() const;
	/* ---- MSG WHAT ----
	Displays a message box on the screen showing what the error is
	@param title - The title that will be displayed in message box */
	const void msgWhat(char* title) const;
	/* ---- MSG WHAT ----
	Displays a message box on the screen showing what the error was
	@param title - The title that will be displayed in message box
	@param type - The type of message box */
	int msgWhat(char* title, size_t type) const;
};
_BPD_END
/*CALLS THE EXEPTION CLASS AND PASSES THROUGH THE ARGUMENT, FILE PATH AND THE LINE NUMBER*/
#define BPD_EXCEPTION(arg) throw bpd::Exception(arg, __FILE__, __LINE__);