#pragma once
#ifdef BPD_WINDEF
#pragma comment(lib, "d2d1")
#pragma comment(lib, "Dwrite")

#include "bpddef.h"
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

//#include <fcntl.h>
//#include <io.h>
//#include <iostream>
//#include <fstream>

#include "../Exception.h"
#include "../IList.h"
#include "../ObjectPool.h"
#include "../bpdWinObjects.h"
#include "../Timer.h"
#define BPD_WinMain() WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cCmdShow)
#define BPD_WinProc() CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#define BPD_BtnWinProc() CALLBACK WinProcBtn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#define BPD_DEFWINPROC DefWindowProc(hwnd, msg, wParam, lParam)
#define BPD_UPDATE_RECT(_hwnd_,_rect_) InvalidateRect(_hwnd_, _rect_, false);UpdateWindow(_hwnd_);

BPD_BEGIN
template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease) {
	if (*ppInterfaceToRelease != NULL) {
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}
BPD_END

#ifndef BPD_DEBUGMODE
#if defined( DEBUG ) || defined ( _DEBUG )
#define BPD_DEBUGMODE 
#endif
#endif // !BPD_CONSOLE

#ifndef BPD_ASSERT
#if defined( DEBUG ) || defined ( _DEBUG )
#define BPD_ASSERT(b) do {if (!(b)){OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define BPD_ASSERT(b)
#endif
#endif // !BPD_ASSERT

#ifndef BPD_CONSOLE
#if defined( DEBUG ) || defined ( _DEBUG )
#define BPD_CONSOLE 1
#else
#define BPD_CONSOLE 0
#endif
#endif // !BPD_CONSOLE

#if defined ( WIN_DIRECT2D )
BPD_BEGIN
static const bool isDirect2D = true;
BPD_END
#else
BPD_BEGIN
static const bool isDirect2D = false;
BPD_END
#endif
#define BPD_DIRECT2D isDirect2D

#if defined ( WIN_DIRECT2D_FULLSCREEN_WINDOWED )
BPD_BEGIN
static const bool isFullscreenWindowed = true;
BPD_END
#else
BPD_BEGIN
static const bool isFullscreenWindowed = false;
BPD_END
#endif
#define WIN_DIRECT2D_FULLSCREEN_WINDOWED isFullscreenWindowed

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

#if defined ( WIN_DIRECT2D_FALLSCREEN_WINDOWED )
BPD_BEGIN
inline bool isPointInRect(D2D1_POINT_2F point, D2D1_RECT_F rect){
	if(point.x < (rect.left + (.5*(rect.right-rect.left))) && point.x >(rect.left - (.5*(rect.right - rect.left))) &&
		point.y < (rect.top + (.5*(rect.top - rect.bottom))) && point.y >(rect.top - (.5*(rect.top - rect.bottom))))
		return true;
	else return false;
}
BPD_END
#endif //  WIN_DIRECT2D_FALLSCREEN_WINDOWED

#define BPD_MSG_EXIT -1
#define BPD_MSG_UPDATE 0
#define BPD_MSG_DISPATCH 1
#endif // !BPD_WINDEF
