#pragma once

struct BpdWindowInfo
{
	short width;
	short height;
	const char * name;
};


bool bpdCreateWindow(BpdWindow * object, BpdWindowInfo * info);
