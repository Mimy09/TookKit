// ################################################################## //
// ##							WINDOW							   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 May 12 - AIE			   ## //
// ################################################################## //
#pragma once
#pragma warning(disable: 4008)
#pragma warning(disable: 4302)
#pragma warning(disable: 4244)
#define BPD_WINDEF
#include "Core\bpdwindef.h"

BPD_BEGIN
class Window {
public:
	//##################################//
	// PUBLIC VARIABLES
	//##################################//
	//Stores the Bitmap of the whole screen to alow for double buffering 
	HBITMAP hBitmat;
	//The second HDC to swap to whilse double buffering 
	HDC memDC;
	//Screen Width
	int screenWidth = 0;
	//Screen Height
	int screenHeight = 0;

	//##################################//
	// CONSTRUCTOR
	//##################################//
	// Defalt constructor
	Window(){}
	// Defalt virtual deconstructor
	virtual ~Window() = 0 {}

	//##################################//
	// PUBLIC FUNCTIONS
	//##################################/

	/* ---- Create ----
	* #param className - Sets the class name of the WINCLASS 
	* #param winTitle - Sets the title of the main HWND window
	* #param winPos - Sets the position of the main HWND window */
	virtual void Create(const_string className, const_string winTitle, RECT winPos, bool console = true);
	
	/* ---- Show ---- 
	Sets the main HWND window to visable */
	virtual void Show();
			
	/* ---- Hide ----
	Set the main HWND window to hidden */
	virtual void Hide();

	/* ---- Run ---- 
	Runs the main message loop
	#return int (-1) - If WM_QUIT was posted
	#return int (0) - If all messages have been dispatched
	#return int (1) - If messages are being dispatched*/
	virtual int Run();

	/* ---- Update ----
	virtual Update loop
	#param deltaTime - The delta time of the app*/
	virtual void Update(double deltaTime);

	/* ---- RunWindow ----
	Runs the update loop for the window*/
	virtual void RunWindow();

	/* ---- ScreenRectWidth ----
	Gets the Screen width
	#return int - Returns the screen width*/
	virtual inline int ScreenRectWidth() { GetClientRect(m_hwnd, &m_rc); return m_rc.right - m_rc.left; }

	/* ---- ScreenRectHeight ----
	Gets the Screen height
	#return int - Returns the screen height*/
	virtual inline int ScreenRectHeight() { GetClientRect(m_hwnd, &m_rc); return m_rc.bottom - m_rc.top; }

	// Sets the WinProc as a friend of this class
	friend LRESULT BPD_WinProc();

	/* ---- hwnd ----
	Gets the hwnd
	#return HWND - Returns the hwnd*/
	inline HWND hwnd() { return m_hwnd; }

	/* ---- UpdateTime ----
	Updates the prevTime of the deltaTime */
	inline void UpdateTime() { prevTime = m_timer.elapsed(); }

	void MessageSend(bpd::String winClass, bpd::String winName, UINT msg, ULONG dataMsg);
protected:
	//##################################//
	// POLYMOPHIC FUNCTIONS
	//##################################//

	/* ---- OnCreate ----
	Called when the WM_CREATE message is dispatched
	#param hwnd - The window handle of the current window
	#return bool (true) - If no error in window
	#return bool (false) - If error in window*/
	virtual bool OnCreate(HWND hwnd) { return true; } // return false if error / close window


	/* ---- OnDestroy ----
	Called when the WM_DESTROY message is dispatched
	#defalt body - PostQuitMessage(0); */
	virtual void OnDestroy() { PostQuitMessage(0); }

	/* ---- OnClose ----
	Called when the WM_CLOSE message is dispatched*/
	virtual void OnClose() {}


	/* ---- OnPaint ----
	Called when the WM_PAINT message is dispatched
	#param hdc - The device context*/
	virtual void OnPaint(HDC hdc) {}
			
	/* ---- OnMessage ----
	Called when reciving a message
	#param param - The messgage that was recieved*/
	virtual void OnMessage( UINT message, ULONG dataMsg) {}
			
	// ---- MOUSE EVENTS ----
	virtual void OnMouseDown(int x, int y, UINT param) {}
	virtual void OnMouseUp(int x, int y, UINT param) {}
	virtual void OnMouseMove(int x, int y, UINT param) {}
	virtual void OnMouseDClick(int x, int y, UINT param) {}
			
	// ---- BUTTON EVENTS ----
	virtual void OnBtnClicked(HWND wndHandle) {}
	virtual void OnBtnDBClicked(HWND wndHandle) {}
	virtual void OnBtnPushed(HWND wndHandle) {}
	virtual void OnBtnUnpushed(HWND wndHandle) {}

	// ---- KEYBOARD EVENTS ----
	virtual void OnKeyDown(UINT key) {}
	virtual void OnKeyUp(UINT key) {}

	// ---- WINDOW EVENTS ----
	virtual void OnWindowMinamize() {}
	virtual void OnWindowMaximize() {}
	virtual void OnScreenSave(){}
	virtual void OnWindowMove(){}
	virtual void OnWindowStopMoving(){}
	virtual void OnWindowResize(){}

	// ---- GSM EVENTS ----
	virtual void GSMUpdate(double deltaTime) {}
	virtual void GSMDraw(HDC hdc) {}

	bpd::ObjectPool<HPEN> m_penPool;
	bpd::ObjectPool<HBRUSH> m_brushPool;
	bpd::String m_version;
	bpd::Timer m_timer;

private:
	MSG m_msg;
	RECT m_rc;
	HWND m_hwnd;
	WNDCLASSEX m_wc;
	COPYDATASTRUCT pcds;

	//tk::IO m_versionFile;

	double prevTime = 0;
};
BPD_END