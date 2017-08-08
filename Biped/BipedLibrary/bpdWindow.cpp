#include "Biped\bpd\bpdWindow.h"

int main();

BPD_BEGIN
LRESULT BPD_WinProc() {
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
		win->screenWidth = GetSystemMetrics(SM_CXSCREEN);
		win->screenHeight = GetSystemMetrics(SM_CYSCREEN);

		HDC hdc = GetDC(hwnd);
		win->memDC = CreateCompatibleDC(hdc);
		win->hBitmat = CreateCompatibleBitmap(hdc, win->screenWidth, win->screenHeight);
		SelectObject(win->memDC, win->hBitmat);
		ReleaseDC(hwnd, hdc);
		
		if (win->OnCreate(hwnd)) break; return -1;
	}
	case WM_PAINT:
	{
		if (!BPD_DIRECT2D) {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			win->OnPaint(win->memDC);
			win->GSMDraw(win->memDC);
			BitBlt(hdc, 0, 0, win->screenWidth, win->screenHeight, win->memDC, 0, 0, SRCCOPY);
			EndPaint(hwnd, &ps);
		} else {
			win->OnRender();
			ValidateRect(hwnd, NULL);
		}
		break;
	}
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		win->OnResize(width, height);
	} break;
	case WM_DISPLAYCHANGE:
	{
		InvalidateRect(hwnd, NULL, FALSE);
	} break;
	case WM_DESTROY: win->OnDestroy(); break;
	case WM_CLOSE: win->OnClose(); break;
	case WM_SYSCOMMAND:
		if ((wParam & 0xFFF0) == SC_MINIMIZE) { win->OnWindowMinamize(); }
		if ((wParam & 0xFFF0) == SC_MAXIMIZE) { win->UpdateTime(); win->OnWindowMaximize(); }
		if ((wParam & 0xFFF0) == SC_SCREENSAVE) { win->UpdateTime(); win->OnScreenSave(); }
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case BN_CLICKED: win->OnBtnClicked((HWND)lParam); break;
		case BN_DBLCLK: win->OnBtnDBClicked((HWND)lParam); break;
		case BN_PUSHED: win->OnBtnPushed((HWND)lParam); break;
		case BN_UNPUSHED: win->OnBtnUnpushed((HWND)lParam); break;
		}
		break;
	case WM_COPYDATA:
		{
			PCOPYDATASTRUCT data = (PCOPYDATASTRUCT)lParam;
			win->OnMessage(*((UINT*)data->lpData), *((ULONG*)data->dwData));
		}
		break;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP: win->OnMouseUp(LOWORD(lParam), HIWORD(lParam), wParam); break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN: win->OnMouseDown(LOWORD(lParam), HIWORD(lParam), wParam); break;
	case WM_LBUTTONDBLCLK: win->OnMouseDClick(LOWORD(lParam), HIWORD(lParam), wParam); break;
	case WM_MOUSEMOVE: win->OnMouseMove(LOWORD(lParam), HIWORD(lParam), wParam); break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		win->OnKeyDown(wParam); break;
	case WM_KEYUP: win->OnKeyUp(wParam); break;
	case WM_MOVE: win->OnWindowMove(); break;
	case WM_EXITSIZEMOVE: win->UpdateTime(); win->OnWindowStopMoving(); break;
	case WM_SIZING: win->OnWindowResize(); break;
	}
	return BPD_DEFWINPROC;
}

void Window::Create(const_string className, const_string winTitle, RECT winPos, bool console) {
	HRESULT result;
	Initialize();
	result = CreateDeviceIndependentResources();

	if (!SUCCEEDED(result)) BPD_EXCEPTION("Failed to Create Device Independent Resources");

	ZeroMemory(&m_wc, sizeof(WNDCLASSEX));
	ZeroMemory(&m_msg, sizeof(MSG));
	HINSTANCE hInstance = GetModuleHandle(NULL);

	this->m_wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	this->m_wc.style = CS_HREDRAW | CS_VREDRAW;
	this->m_wc.cbSize = sizeof(WNDCLASSEX);
	this->m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	this->m_wc.hIconSm = LoadIcon(m_wc.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	this->m_wc.hInstance = hInstance;
	this->m_wc.cbClsExtra = 0;
	this->m_wc.cbWndExtra = sizeof(void*);
	this->m_wc.lpfnWndProc = WinProc;
	this->m_wc.lpszMenuName = NULL;
	this->m_wc.lpszClassName = className.data();
	this->m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClassEx(&m_wc)) BPD_EXCEPTION("WINDOW ERROR");

	RECT rectPos = { winPos.left, winPos.top, 0, 0 };
	AdjustWindowRectEx(&winPos, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	this->m_hwnd = CreateWindowEx(
		0,
		className.data(),
		winTitle.data(),
		WIN_DIRECT2D_FULLSCREEN_WINDOWED == true ?
		WS_POPUP : WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX | WS_CLIPCHILDREN,
		WIN_DIRECT2D_FULLSCREEN_WINDOWED == true ? 0 : rectPos.left == 0 ? CW_USEDEFAULT : rectPos.left,
		WIN_DIRECT2D_FULLSCREEN_WINDOWED == true ? 0 : rectPos.top == 0 ? CW_USEDEFAULT : rectPos.top,
		WIN_DIRECT2D_FULLSCREEN_WINDOWED == true ? GetSystemMetrics(SM_CXSCREEN): winPos.right - winPos.left,
		WIN_DIRECT2D_FULLSCREEN_WINDOWED == true ? GetSystemMetrics(SM_CYSCREEN): winPos.bottom - winPos.top,
		NULL, NULL, this->m_wc.hInstance,
		(LPVOID) this
	);
	if (!m_hwnd) BPD_EXCEPTION("WINDOW ERROR");

	/* ---- Start the console ---- */
	if(BPD_CONSOLE) {
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CON", "w", stdin);

		printf(" ---- ToolKit Debug Console ----\n\n\n");
		printf("Creating Window\n");
		printf("-----------------------------------\n");
		printf(" Window Class: %s \n", className.data());
		printf(" Window Title: %s \n", winTitle.data());
		printf(" Window Full screen: %i \n", WIN_DIRECT2D_FULLSCREEN_WINDOWED);
		printf("-----------------------------------\n\n");
	} else { FreeConsole(); }

	m_timer.start();
	prevTime = 0;
	m_version = "VERSION 0.7";

}
void Window::Initialize() {
	m_pDirect2dFactory = NULL;
	m_pWriteFactory = NULL;
	m_pRenderTarget = NULL;
	m_pDebugTextFormat = NULL;
}

void Window::Release() {
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pWriteFactory);
	SafeRelease(&m_pDebugTextFormat);
	OnDiscardDeviceResources();
}
void Window::Show() {
	if (!m_hwnd) BPD_EXCEPTION("WINDOW HANDLE ERROR");
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);
}
void Window::Hide() {
	if (!m_hwnd) BPD_EXCEPTION("WINDOW HANDLE ERROR");
	ShowWindow(m_hwnd, SW_HIDE);
	UpdateWindow(m_hwnd);
}
int Window::Run() {
	if (m_msg.message != WM_QUIT) {
		if (PeekMessage(&m_msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
			return 1;
		}
		else {
			double now = m_timer.elapsed();
			double deltaTime = now - prevTime;
					
			Update(deltaTime);

			prevTime = now;
			return 0;
		}
	} else { return -1; }
}
void Window::Update(double deltaTime) {
	BPD_UPDATE_RECT(m_hwnd, NULL);
}
void Window::RunWindow() {
	while (Run() != BPD_MSG_EXIT) { }
}
void Window::MessageSend(bpd::String winClass, bpd::String winName, UINT msg, ULONG dataMsg) {
	COPYDATASTRUCT cds;
	cds.dwData = dataMsg;
	cds.cbData = sizeof(UINT);
	cds.lpData = &msg;
	HWND hWindow = FindWindow(winClass.data, winName.data);
	if (hWindow != NULL) {
		SendMessage(
			hWindow,
			WM_COPYDATA,
			(WPARAM)(HWND)m_hwnd,
			(LPARAM)(LPVOID)&cds
		);
	} else { BPD_EXCEPTION("SEND MESSAGE ERROR"); }
}
HRESULT Window::CreateDeviceIndependentResources() {
	HRESULT result = S_OK;
	result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
	if(SUCCEEDED(result)) result = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pWriteFactory),
		reinterpret_cast<IUnknown **>(&m_pWriteFactory)
	);
	return result;
}

HRESULT Window::CreateDeviceResources() {
	HRESULT result = S_OK;

	if (!m_pRenderTarget) {
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		result = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&m_pRenderTarget
		);

		if(SUCCEEDED(result)) result = m_pWriteFactory->CreateTextFormat(
			L"Verdana",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			12,
			L"",
			&m_pDebugTextFormat
		);
		if (SUCCEEDED(result)){
			//m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			//m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			OnDeviceResources(m_pRenderTarget);
		}
	}
	return result;
}

void Window::DiscardDeviceResources() {
	SafeRelease(&m_pRenderTarget);
	OnDiscardDeviceResources();
}
HRESULT Window::OnRender() {
	HRESULT result = S_OK;
	result = CreateDeviceResources();
	if (SUCCEEDED(result)) {
		m_pRenderTarget->BeginDraw();
		OnPaint(m_pRenderTarget);
		result = m_pRenderTarget->EndDraw();
	}
	if (result == D2DERR_RECREATE_TARGET) {
		result = S_OK;
		DiscardDeviceResources();
	} return result;
}

void Window::OnResize(UINT width, UINT height) {
	if (m_pRenderTarget) {
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
	}
}
BPD_END

inline int BPD_WinMain() {
	main();
}