// ################################################################## //
// ##							Window							   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Sep 5 - AIE			   ## //
// ################################################################## //
#pragma once
#include <Windows.h>

_BPD_BEGIN
_BPD_DEF_HANDLE(Window);

struct WindowInfo {
	containers::const_string ClassName;
	containers::const_string TitleName;
	
	int x = -1;
	int y = -1;
	int Width = 800;
	int Height = 600;
	bool FullScreen = false;
	bool ShowDebugConsole = true;
	bool Resizable = true;
	bool Minamize = true;
	bool Maximize = true;
};
BPD_RESULT WindowCreate(Window& win, WindowInfo info);

void WindowShow(Window& win);
void WindowRun(Window& win);

void WindowRun();
void WindowShow();
void bind(Window& win);

void linkClass(bpdApplication* _class);

int getWidth();
int getHeight();
Timer* getTimer();
HWND* getHWND();
HDC* getHDC();

keyboard* Keyboard();
mouse* Mouse();

_BPD_END