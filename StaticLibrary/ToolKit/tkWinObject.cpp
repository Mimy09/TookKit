#include "tkWinObjects.h"

namespace tk {
	namespace win {	
		
		/************************************************************************************************************************
		************************************************************************************************************************/

		WinObject::WinObject() { _hwnd = nullptr; }

		WinObject::WinObject(HWND hwnd, tk::String classType, tk::String text, RECT rect) {
			HWND hwndObject = CreateWindow(
				classType.data, text.data,
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				rect.left, rect.top,
				rect.left + rect.right,
				rect.top + rect.bottom,
				hwnd,
				NULL,
				GetModuleHandle(NULL),
				NULL
			); _hwnd = hwndObject;
		}

		void WinObject::CreateWnd(HWND hwnd, tk::String classType, tk::String text, RECT rect) {
			HWND hwndObject = CreateWindow(
				classType.data, text.data,
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				rect.left, rect.top,
				rect.left + rect.right,
				rect.top + rect.bottom,
				hwnd,
				NULL,
				GetModuleHandle(NULL),
				NULL
			); _hwnd = hwndObject;
		}

		void WinObject::SetTextSize(int Size) {
			HFONT hFont = CreateFont(
				Size, 0, 0, 0,
				FW_DONTCARE,
				FALSE, FALSE, FALSE,
				ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_SWISS,
				"Arial"
			);
			SendMessage(_hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
		}

		void WinObject::SetPosition(RECT rect) {
			MoveWindow(
				_hwnd,
				rect.left, rect.top,
				rect.right, rect.bottom,
				true
			);
		}
		HWND WinObject::hwnd() { return _hwnd; }

		/************************************************************************************************************************
		************************************************************************************************************************/

		WinImage::WinImage() {
			bmpSource = NULL;
			hdcSource = NULL;
		}

		void WinImage::Load(tk::String file) {
			bmpSource = (HBITMAP)LoadImage(NULL, file.data, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			hdcSource = CreateCompatibleDC(GetDC(0));
		}

		void WinImage::Select() { SelectObject(hdcSource, bmpSource); }

		void WinImage::Draw(HDC hdc, RECT rect) {
			BitBlt(
				hdc,
				rect.left, rect.top,
				rect.right, rect.bottom,
				hdcSource, 0, 0, SRCCOPY
			);
		}

		/************************************************************************************************************************
		************************************************************************************************************************/

		WinText::WinText() {
			font = NULL;
			hFontOld = NULL;
		}
		WinText::WinText(HDC hdc, tk::String Text, RECT Position) {
			pos = {
				Position.left, Position.top,
				Position.left + Position.right,
				Position.top + Position.bottom
			};
			SelectObject(hdc, font);
			DrawText(hdc, Text.data, strlen(Text.data), &pos, DT_CENTER);
			SelectObject(hdc, hFontOld);
		}
		void WinText::Draw(HDC hdc, tk::String Text, RECT Position) {
			if (hFontOld == NULL)hFontOld = (HFONT)SelectObject(hdc, font);
			pos = {
				Position.left, Position.top,
				Position.left + Position.right,
				Position.top + Position.bottom
			};
			if (font) SelectObject(hdc, font);
			DrawText(hdc, Text.data, strlen(Text.data), &pos, DT_CENTER);
			if (hFontOld) SelectObject(hdc, hFontOld);
		}
		void WinText::SetFont(int size) {
			font = CreateFont(
				size, 0, 0, 0,
				FW_DONTCARE,
				FALSE, FALSE, FALSE,
				ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_SWISS,
				"Arial"
			);
		}
		/************************************************************************************************************************
		************************************************************************************************************************/

	}
}