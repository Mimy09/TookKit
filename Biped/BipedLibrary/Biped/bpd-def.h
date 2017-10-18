#pragma once
// ################################################################## //
// ##							Biped Def						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Sep 5 - AIE			   ## //
// ################################################################## //
#include <stdio.h>
#include "bpd.h"

_BPD_BEGIN
struct Window_bpd {
	WNDCLASSEX WinClass;
	RECT RectPos;
	Timer time;
	HWND hWnd;
	MSG Msg;
	HDC memDC;
	HBITMAP hBitmat;
	Brush brushes;
	keyboard e_keyboard;
	mouse e_mouse;
	int Width;
	int Height;
	int cCmdShow;
	double prevTime;
	double deltaTime;
};

struct Validation_bpd {
	bool layer_windows = false;
	bool layer_graphic = false;
};
_BPD_END