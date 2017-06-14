#pragma once
#include "tkString.h"


namespace tk {
	namespace win {
		struct WinObject {
			WinObject();
			/* ---- WinObject ----
			Constructor for the WinObject
			#param hwnd - The window handler
			#param classType - The type of window that will be created
			e.g. "BUTTON", "LISTBOX"
			#param text - The text that will be displayed in the window
			#param rect - The local position that the window will be created at */
			WinObject(HWND hwnd, tk::String classType, tk::String text, RECT rect);
			/* ---- CreateWnd ----
			Creates a WinObject
			#param hwnd - The window handler
			#param classType - The type of window that will be created
			e.g. "BUTTON", "LISTBOX"
			#param text - The text that will be displayed in the window
			#param rect - The local position that the window will be created at */
			void CreateWnd(HWND hwnd, tk::String classType, tk::String text, RECT rect);
			/* ---- SetTextSize ----
			Sets the size of text that will be displayed inside the window
			#param Size - The size of text */
			void SetTextSize(int Size);
			/* ---- SetPosition ----
			Sets the position of the window
			#param rect - The rect that will be used to set the position*/
			void SetPosition(RECT rect);
			/* ---- hwnd ----
			Return the window handle of this window
			#return HWND - returns the window handle*/
			HWND hwnd();
		private:
			// Stores the window handle of the created window
			HWND _hwnd;
		};

		/************************************************************************************************************************
		************************************************************************************************************************/

		struct WinImage {
			/* ---- WinImage ----
			Creates an image to be drawn on screen */
			WinImage();
			/* ---- Load ----
			Loads a selected file in to draw
			#param file - The path to the image*/
			void Load(tk::String file);
			/* ---- Secect ----
			Selects the image so it can be drawn
			@NOTE - This needs to be called befor drawing*/
			void Select();
			/* ---- Draw ----
			Draws the image to screen
			#param hdc - The handle to the display
			#param rect - The rect that the image is drawn to
			@NOTE - Select() needs to be called befor drawing*/
			void Draw(HDC hdc, RECT rect);
		private:
			// Stores the bitmap of the image
			HBITMAP bmpSource;
			// Stores the handle to the display
			HDC hdcSource;
		};

		/************************************************************************************************************************
		************************************************************************************************************************/

		struct WinText {
			WinText();
			/* ---- WinText ----
			Default constructor for WinText
			#param hdc -The handle to the display
			#param Text - The text that will be displayed
			#param Position - The position that the text will be displayed at*/
			WinText(HDC hdc, tk::String Text, RECT Position);
			void Draw(HDC hdc, tk::String Text, RECT Position);
			void SetFont(int size);
			HFONT font;
		private:
			// Stores the position of the text
			RECT pos;
			HFONT hFontOld;
		};

		/************************************************************************************************************************
		************************************************************************************************************************/

	}
}