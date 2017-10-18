#include "..\bpd-def.h"
#include <iostream>
#include <gl/GL.h>

bpd::Window_bpd* BoundWindow = nullptr;
bpdApplication* bpd_validation_link = nullptr;

void ShowConsole() { ::ShowWindow(::GetConsoleWindow(), SW_SHOW); }
void HideConsole() { ::ShowWindow(::GetConsoleWindow(), SW_HIDE); }
bool IsConsoleVisible() { return (::IsWindowVisible(::GetConsoleWindow()) != FALSE); }

int main();
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int cCmdShow) { main();
}
#if defined(_BPD_FCB_CLASSCALLBACK)

#endif
_BPD_BEGIN
///////////////////////////////////////////////////
//// MAIN CALLS
template<class app> inline // START
_BPD_CONST_FUN void _bpd_start(app **ppApp)
_BPD_NOEXCEPT { if(*ppApp != NULL) { (*ppApp)->Start(); } }
template<class app> inline // UPDATE
_BPD_CONST_FUN void _bpd_update(app **ppApp, double deltaTime)
_BPD_NOEXCEPT { if(*ppApp != NULL) { (*ppApp)->Update(deltaTime); } }
template<class app> inline // DRAW
_BPD_CONST_FUN void _bpd_draw(app **ppApp, HDC hdc)
_BPD_NOEXCEPT {	if(*ppApp != NULL) { (*ppApp)->Draw(hdc); } }
///////////////////////////////////////////////////


///////////////////////////////////////////////////
//// KEY EVENTS
template<class app> inline // KEY DOWN
_BPD_CONST_FUN void _bpd_keyDown(app **ppApp, keyboard e)
_BPD_NOEXCEPT {	if(*ppApp != NULL) { (*ppApp)->OnKeyDown(e); } }
template<class app> inline // KEY UP
_BPD_CONST_FUN void _bpd_keyUp(app **ppApp, keyboard e)
_BPD_NOEXCEPT {	if(*ppApp != NULL) { (*ppApp)->OnKeyUp(e); } }
///////////////////////////////////////////////////


///////////////////////////////////////////////////
//// MOUSE EVENTS
template<class app> inline // MOUSE DOWN
_BPD_CONST_FUN void _bpd_mouseDown(app **ppApp, mouse e)
_BPD_NOEXCEPT {	if(*ppApp != NULL) { (*ppApp)->OnMouseDown(e); } }
template<class app> inline // MOUSE UP
_BPD_CONST_FUN void _bpd_mouseUp(app **ppApp, mouse e)
_BPD_NOEXCEPT {	if(*ppApp != NULL) { (*ppApp)->OnMouseUp(e); } }
template<class app> inline // MOUSE MOVE
_BPD_CONST_FUN void _bpd_mouseMove(app **ppApp, mouse e)
_BPD_NOEXCEPT {	if(*ppApp != NULL) { (*ppApp)->OnMouseMove(e); } }
///////////////////////////////////////////////////


///////////////////////////////////////////////////
//// OTHER EVENTS
template<class app> inline // On Command
_BPD_CONST_FUN void _bpd_onCommand(app **ppApp, char* arg1, char* arg2)
_BPD_NOEXCEPT { if (*ppApp != NULL) { (*ppApp)->OnCommand(arg1, arg2); } }
///////////////////////////////////////////////////
_BPD_END

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	bpd::Window* win = (bpd::Window *) GetWindowLongPtr(hwnd, 0);

	switch (msg) {
	case WM_NCCREATE:
	{
		CREATESTRUCT * cs = (CREATESTRUCT *)lParam;
		SetWindowLongPtr(hwnd, 0, (LONG_PTR)cs->lpCreateParams);
		break;
	}
	case WM_ERASEBKGND: return 1;
	case WM_CREATE:
	{
		HDC hdc = GetDC(hwnd);
		(*win)->memDC = CreateCompatibleDC(hdc);
		(*win)->hBitmat = CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		SelectObject((*win)->memDC, (*win)->hBitmat);
		ReleaseDC(hwnd, hdc);
	}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		
		// Main draw call
		if(bpd_validation_link != nullptr) bpd::_bpd_draw(&bpd_validation_link, (*win)->memDC);

		BitBlt(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), (*win)->memDC, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
	} break;
	case WM_DISPLAYCHANGE:
	{
		InvalidateRect(hwnd, NULL, FALSE);
	} break;
	case WM_CLOSE:
		bpd::ReleaseBrushs((*win)->brushes);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYUP:
		if(bpd_validation_link != nullptr) {
			keyboard key_event{wParam};
			bpd::_bpd_keyUp(&bpd_validation_link, key_event);
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) { PostQuitMessage(0); }
		if (wParam == 'C') { if(IsConsoleVisible()) { HideConsole(); } else { ShowConsole(); } }
		if (wParam == 192 && bpd_validation_link != nullptr) {
			printf("\n >> ");
			char* arg1 = new char[124];
			char* arg2 = new char[10];
			std::cin >> arg1; std::cin >> arg2; printf("\n");
			bpd::_bpd_onCommand(&bpd_validation_link, arg1, arg2);
		}
		(*win)->e_keyboard.key = wParam;
		if(bpd_validation_link != nullptr) {
			keyboard key_event{ wParam };
			bpd::_bpd_keyDown(&bpd_validation_link, key_event);
		}
		(*win)->e_keyboard = {};
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
		(*win)->e_mouse.x = LOWORD(lParam);
		(*win)->e_mouse.y = HIWORD(lParam);
		(*win)->e_mouse.key = wParam;
		if(bpd_validation_link != nullptr) {
			mouse mouse_event{LOWORD(lParam), HIWORD(lParam), wParam};
			bpd::_bpd_mouseUp(&bpd_validation_link, mouse_event);
		}
		(*win)->e_keyboard = {};
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		(*win)->e_mouse.x = LOWORD(lParam);
		(*win)->e_mouse.y = HIWORD(lParam);
		(*win)->e_mouse.key = wParam;
		if(bpd_validation_link != nullptr) {
			mouse mouse_event{ LOWORD(lParam), HIWORD(lParam), wParam };
			bpd::_bpd_mouseDown(&bpd_validation_link, mouse_event);
		}
		(*win)->e_keyboard = {};
		break;
	case WM_MOUSEMOVE:
		(*win)->e_mouse.x = LOWORD(lParam);
		(*win)->e_mouse.y = HIWORD(lParam);
		(*win)->e_mouse.key = wParam;
		if(bpd_validation_link != nullptr) {
			mouse mouse_event{ LOWORD(lParam), HIWORD(lParam), wParam };
			bpd::_bpd_mouseMove(&bpd_validation_link, mouse_event);
		}
		(*win)->e_keyboard = {};
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

_BPD_BEGIN

BPD_RESULT WindowCreate(Window& win, WindowInfo info) {
	
	win = new Window_bpd{};
	ZeroMemory(&win->WinClass, sizeof(WNDCLASSEX));
	HINSTANCE hInstance = GetModuleHandle(NULL);

	if (info.ShowDebugConsole) {
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);

		printf(" ----------------------\n");
		printf(" ---- BIPED WINDOW ----\n");
		printf(" ----------------------\n\n\n");
		printf("Creating Window\n");
		printf("-----------------------------------\n");
		printf("ClassName: %s\n", info.ClassName);
		printf("TitleName: %s\n", info.TitleName);
		printf("X: %i\n", info.x);
		printf("Y: %i\n", info.y);
		printf("Width: %i\n", info.Width);
		printf("Height: %i\n", info.Height);
		printf("FullScreen: %i\n", info.FullScreen);
		printf("ShowConsole: %i\n", info.ShowDebugConsole);
		printf("-----------------------------------\n\n");
	}


	win->WinClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	win->WinClass.style = CS_HREDRAW | CS_VREDRAW;
	win->WinClass.cbSize = sizeof(WNDCLASSEX);
	win->WinClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	win->WinClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	win->WinClass.hInstance = hInstance;
	win->WinClass.cbClsExtra = 0;
	win->WinClass.cbWndExtra = sizeof(void*);
	win->WinClass.lpfnWndProc = WinProc;
	win->WinClass.lpszMenuName = NULL;
	win->WinClass.lpszClassName = info.ClassName.begin();
	win->WinClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClassEx(&win->WinClass)) {
		BPD_EXCEPTION("Window not registered");
	}

	RECT rectPos = { info.x, info.y, info.Width, info.Height };
	AdjustWindowRectEx(&rectPos, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	DWORD winStyle = WS_OVERLAPPEDWINDOW;
	if(!info.FullScreen) {
		if(!info.Resizable) winStyle = winStyle ^ WS_THICKFRAME;
		if(!info.Maximize) winStyle = winStyle ^ WS_MAXIMIZEBOX;
		if(!info.Minamize) winStyle = winStyle ^ WS_MINIMIZEBOX;
		winStyle = winStyle | WS_CLIPCHILDREN | WS_VISIBLE;
	}

	win->hWnd = CreateWindowEx(
		0,
		info.ClassName.begin(),
		info.TitleName.begin(),
		info.FullScreen == true ? WS_POPUP : winStyle,
		info.FullScreen == true ? 0 : info.x == -1 ? CW_USEDEFAULT : rectPos.left,
		info.FullScreen == true ? 0 : info.y == -1 ? CW_USEDEFAULT : rectPos.top,
		info.FullScreen == true ? GetSystemMetrics(SM_CXSCREEN) : rectPos.right - rectPos.left,
		info.FullScreen == true ? GetSystemMetrics(SM_CYSCREEN) : rectPos.bottom - rectPos.top,
		NULL, NULL, hInstance, (LPVOID)&win
	);
	if (!win->hWnd) { BPD_EXCEPTION("Window not created"); }
	

	if (!info.FullScreen) {
		win->Width = rectPos.right;
		win->Height = rectPos.bottom;
		
		if (info.x == -1){
			RECT pos = {}; GetWindowRect(win->hWnd, &pos);
			info.x = pos.left;
		} else info.x = rectPos.left;
		if (info.y == -1){
			RECT pos = {}; GetWindowRect(win->hWnd, &pos);
			info.y = pos.top;
		} else info.y = rectPos.top;
	} else {
		info.x = info.y = 0;
		win->Width = info.Width = BPD_SCREEN_WIDTH;
		win->Height = info.Height = BPD_SCREEN_HEIGHT;
	}

	win->time.start();
	win->brushes = {};

	

	return BPD_RESULT::SUCCESS;
}

void WindowShow(Window& win) {
	if(bpd_validation_link != nullptr) bpd::_bpd_start(&bpd_validation_link);

	ShowWindow(win->hWnd, SW_SHOW);
	UpdateWindow(win->hWnd);

	printf(" >> Showing Window\n");
}

void WindowRun(Window& win) {
	printf(" >> Starting message loop...\n\n");
	printf("-----------------------------------\n\n");
	ZeroMemory(&win->Msg, sizeof(MSG));

	while (win->Msg.message != WM_QUIT) {
		if (::PeekMessage(&win->Msg, 0, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&win->Msg);
			::DispatchMessage(&win->Msg);
		}
		else {
			double now = win->time.elapsed();
			double deltaTime = now - win->prevTime;

			// Main update call
			if(bpd_validation_link != nullptr) bpd::_bpd_update(&bpd_validation_link, deltaTime);

			win->deltaTime = deltaTime;
			win->prevTime = now;
		}
	}
}

void WindowRun() { WindowRun(BoundWindow); }
void WindowShow() {	WindowShow(BoundWindow); }

void bind(Window& win) { BoundWindow = win; }
void linkClass(bpdApplication* _class) { bpd_validation_link = _class; }

int getWidth() { return BoundWindow->Width; }
int getHeight(){ return BoundWindow->Height; }
Timer* getTimer() { return &BoundWindow->time; }
HWND* getHWND() { return &BoundWindow->hWnd; }

keyboard* Keyboard() { return &BoundWindow->e_keyboard; }
mouse* Mouse() { return &BoundWindow->e_mouse; }
HDC* getHDC() { return &BoundWindow->memDC; }

_BPD_END