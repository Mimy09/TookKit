#pragma once
#ifdef BPD_WINDEF
#include "bpddef.h"
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "../Exception.h"
#include "../IList.h"
#include "../ObjectPool.h"
#include "../HashTable.h"
#include "../bpdWinObjects.h"
#include "../Timer.h"
#define BPD_WinMain() WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cCmdShow)
#define BPD_WinProc() CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#define BPD_BtnWinProc() CALLBACK WinProcBtn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#define BPD_DEFWINPROC DefWindowProc(hwnd, msg, wParam, lParam)
#define BPD_UPDATE_RECT(_hwnd_,_rect_) InvalidateRect(_hwnd_, _rect_, false);UpdateWindow(_hwnd_);

#define BPD_MSG_EXIT -1
#define BPD_MSG_UPDATE 0
#define BPD_MSG_DISPATCH 1

#define BPD_BRUSH_BLACK *m_brushPool.ReturnObjectIndex(0)
#define BPD_BRUSH_WHITE *m_brushPool.ReturnObjectIndex(1)
#define BPD_BRUSH_RED *m_brushPool.ReturnObjectIndex(2)
#define BPD_BRUSH_GREEN *m_brushPool.ReturnObjectIndex(3)
#define BPD_BRUSH_BLUE *m_brushPool.ReturnObjectIndex(4)
#define BPD_BRUSH_YELLOW *m_brushPool.ReturnObjectIndex(5)
#define BPD_BRUSH_PURPLE *m_brushPool.ReturnObjectIndex(6)
#define BPD_BRUSH_CYAN *m_brushPool.ReturnObjectIndex(7)

#define BPD_PEN_BLACK *m_penPool.ReturnObjectIndex(0)
#define BPD_PEN_WHITE *m_penPool.ReturnObjectIndex(1)
#define BPD_PEN_RED *m_penPool.ReturnObjectIndex(2)
#define BPD_PEN_GREEN *m_penPool.ReturnObjectIndex(3)
#define BPD_PEN_BLUE *m_penPool.ReturnObjectIndex(4)
#define BPD_PEN_YELLOW *m_penPool.ReturnObjectIndex(5)
#define BPD_PEN_PURPLE *m_penPool.ReturnObjectIndex(6)
#define BPD_PEN_CYAN *m_penPool.ReturnObjectIndex(7)
#endif // !BPD_WINDEF
