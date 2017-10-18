#include "../bpd-def.h"

_BPD_BEGIN
Exception::Exception(char* arg, const char *file, int line){
	msg = arg;
}
Exception::~Exception() throw() {}
const char* Exception::what() const throw(){ return msg; }
const void Exception::msgWhat() const{
	MessageBox(NULL, what(), "#### FATAL ERROR ####", MB_ICONERROR | MB_OK);
}
const void Exception::msgWhat(char* title) const{
	MessageBox(NULL, what(), title, MB_ICONERROR | MB_OK);
}
int Exception::msgWhat(char* title, size_t type) const{
	int msgboxID = MessageBox(NULL, what(), title, type);
	return msgboxID;
}
_BPD_END