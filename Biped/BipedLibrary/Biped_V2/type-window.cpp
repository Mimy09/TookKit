#include "macros.h"
#include "detail.h"
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif
BPD_DEF_HANDLE(BpdWindow);


struct BpdWindow_bpd {
	char * test;
	
};


bool bpdCreateWindow(void * object, BpdWindowInfo * info) {
	return false;
}
