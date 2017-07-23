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
#define WIN_DIRECT2D
#define WIN_DIRECT2D_FALLSCREEN_WINDOWED
#include "Core\bpdwindef.h"

BPD_BEGIN
class Window {
public:
	//##################################//
	// PUBLIC VARIABLES
	//##################################//
	//Stores the Bitmap of the whole screen to allow for double buffering 
	HBITMAP hBitmat;
	//The second HDC to swap to whiles double buffering 
	HDC memDC;
	//Screen Width
	int screenWidth = 0;
	//Screen Height
	int screenHeight = 0;

	//##################################//
	// CONSTRUCTOR
	//##################################//
	// Default constructor
	Window(){}
	// Default virtual deconstruction
	virtual ~Window() = 0 {}

	//##################################//
	// PUBLIC FUNCTIONS
	//##################################/

	/* ---- Initialize ----
	Initialize Direct2D */
	void Initialize();

	/* ---- Create ----
	* #param className - Sets the class name of the WINCLASS 
	* #param winTitle - Sets the title of the main HWND window
	* #param winPos - Sets the position of the main HWND window */
	virtual void Create(const_string className, const_string winTitle, RECT winPos, bool console = true);
	
	/* ---- Release ---- 
	Do the safe releases for all the direct2d objects */
	virtual void Release();

	/* ---- Show ---- 
	Sets the main HWND window to viable */
	virtual void Show();
			
	/* ---- Hide ----
	Set the main HWND window to hidden */
	virtual void Hide();

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

	/* ---- MessageSend ----
	Send a message*/
	void MessageSend(bpd::String winClass, bpd::String winName, UINT msg, ULONG dataMsg);
private:
	//##################################//
	// PRIVATE FUNCTIONS
	//##################################//
	/* ---- Run ----
	Runs the main message loop
	#return int (-1) - If WM_QUIT was posted
	#return int (0) - If all messages have been dispatched
	#return int (1) - If messages are being dispatched*/
	virtual int Run();

	//##################################//
	// PRIVATE DIRECT2D FUNCTIONS
	//##################################//
	/* ---- CreateDeviceIndependentResources ---- */
	HRESULT CreateDeviceIndependentResources();

	/* ---- CreateDeviceResources ---- */
	HRESULT CreateDeviceResources();

	/* ---- DiscardDeviceResources ---- */
	void DiscardDeviceResources();

	/* ---- OnRender ---- */
	HRESULT OnRender();

	/* ---- OnResize ---- */
	void OnResize( UINT width, UINT height );
private:
	//##################################//
	// PRIVATE DIRECT2D VARIABLES
	//##################################//
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IDWriteFactory* m_pWriteFactory;
protected:
	IDWriteTextFormat* m_pDebugTextFormat;
	//##################################//
	// POLYMOPHIC FUNCTIONS
	//##################################//

	/* ---- UpdateTime ----
	Updates the prevTime of the deltaTime */
	inline void UpdateTime() { prevTime = m_timer.elapsed(); }

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

	/* ---- OnPaint ----
	Called when the WM_PAINT message is dispatched
	#param hdc - The device context*/
	virtual void OnPaint(ID2D1HwndRenderTarget*) {}
	
	/* ---- OnDeviceResources ----
	Called when creating device resources*/
	virtual void OnDeviceResources(ID2D1HwndRenderTarget*) {}

	/* ---- OnDiscardDeviceResources ----
	Called when discarding device resources*/
	virtual void OnDiscardDeviceResources() {}

	/* ---- OnMessage ----
	Called when receiving a message
	#param param - The message that was received*/
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

	//##################################//
	// PROTECTED VARIABLES
	//##################################//
	bpd::ObjectPool<HPEN> m_penPool;
	bpd::ObjectPool<HBRUSH> m_brushPool;
	bpd::String m_version;
	bpd::Timer m_timer;

private:
	//##################################//
	// PRIVATE VARIABLES
	//##################################//
	MSG m_msg;
	RECT m_rc;
	HWND m_hwnd;
	WNDCLASSEX m_wc;
	COPYDATASTRUCT pcds;

	//tk::IO m_versionFile;

	double prevTime = 0;
};
BPD_END