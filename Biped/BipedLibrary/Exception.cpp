#include "Biped\bpd\Exception.h"

BPD_BEGIN
Exception::Exception(String arg, const char *file, int line){
	msg = file;
	msg = msg.cSplit('\\', msg.countChar('\\'));
	msg += (String)":" + (String)line + (String)": " + arg;
}
Exception::~Exception() throw() {}
const char* Exception::what() const throw(){ return msg.data; }
const void Exception::msgWhat() const{
	MessageBox(NULL, what(), "#### FATAL ERROR ####", MB_ICONERROR | MB_OK);
}
const void Exception::msgWhat(char* title) const{
	MessageBox(NULL, what(), title, MB_ICONERROR | MB_OK);
}
int Exception::msgWhat(char* title, size_type type) const{
	int msgboxID = MessageBox(NULL, what(), title, type);
	return msgboxID;
}
BPD_END