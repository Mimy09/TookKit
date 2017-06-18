#include "tkWindow.h"
#include <stdlib.h>


int main();

namespace tk {
	namespace win {

		LRESULT TK_WinProc() {
			tk::win::Window* win = (tk::win::Window *) GetWindowLong(hwnd, 0);

			switch (msg) {
			case WM_NCCREATE:
			{
				CREATESTRUCT * cs = (CREATESTRUCT *)lParam;
				SetWindowLong(hwnd, 0, (LONG)cs->lpCreateParams);
				break;
			}
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
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				win->OnPaint(win->memDC);
				BitBlt(hdc, 0, 0, win->screenWidth, win->screenHeight, win->memDC, 0, 0, SRCCOPY);
				EndPaint(hwnd, &ps);
				break;
			}
			case WM_ERASEBKGND: return 1;
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
			case WM_KEYDOWN: win->OnKeyDown(wParam); break;
			case WM_KEYUP: win->OnKeyUp(wParam); break;
			case WM_MOVE: win->OnWindowMove(); break;
			case WM_EXITSIZEMOVE: win->UpdateTime(); win->OnWindowStopMoving(); break;
			case WM_SIZING: win->OnWindowResize(); break;
			}
			return TK_DEFWINPROC;
		}

		void Window::Create(tk::String className, tk::String winTitle, RECT winPos) {
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
			this->m_wc.lpszClassName = className.data;
			this->m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			if (!RegisterClassEx(&m_wc)) TK_EXCEPTION("WINDOW ERROR");

			RECT rectPos = { winPos.left, winPos.top, 0, 0 };
			AdjustWindowRectEx(&winPos, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

			this->m_hwnd = CreateWindowEx(
				WS_EX_OVERLAPPEDWINDOW,
				className.data,
				winTitle.data,
				WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_CLIPCHILDREN,
				rectPos.left == 0 ? CW_USEDEFAULT : rectPos.left,
				rectPos.top == 0 ? CW_USEDEFAULT : rectPos.top,
				winPos.right - winPos.left,
				winPos.bottom - winPos.top,
				NULL,
				NULL,
				this->m_wc.hInstance,
				(LPVOID) this
			);
			if (!m_hwnd) TK_EXCEPTION("WINDOW ERROR");

			// Add brushes
			m_brushPool.AddObject(CreateSolidBrush(RGB(0, 0, 0)));
			m_brushPool.AddObject(CreateSolidBrush(RGB(255, 255, 255)));
			m_brushPool.AddObject(CreateSolidBrush(RGB(255, 0, 0)));
			m_brushPool.AddObject(CreateSolidBrush(RGB(0, 255, 0)));
			m_brushPool.AddObject(CreateSolidBrush(RGB(0, 0, 255)));

			// Add pens
			m_penPool.AddObject(CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
			m_penPool.AddObject(CreatePen(PS_SOLID, 1, RGB(255, 255, 255)));
			m_penPool.AddObject(CreatePen(PS_SOLID, 1, RGB(255, 0, 0)));
			m_penPool.AddObject(CreatePen(PS_SOLID, 1, RGB(0, 255, 0)));
			m_penPool.AddObject(CreatePen(PS_SOLID, 1, RGB(0, 0, 255)));

			m_timer.start();
			prevTime = 0;
			m_version = "VERSION 0.5";

			//m_versionFile.SetPath("../../VERSION.txt");
			//m_versionFile.Open(tk::IO::ReadWrite);
			//m_versionFile.Write("VERSION=0.4");
			//m_versionFile.Open(tk::IO::ReadOnly);
			//m_versionFile.Read(m_version, 0);
			//m_versionFile.Close();

		}
		void Window::Show() {
			if (!m_hwnd) TK_EXCEPTION("WINDOW HANDLE ERROR");
			ShowWindow(m_hwnd, SW_SHOW);
			UpdateWindow(m_hwnd);
		}
		void Window::Hide() {
			if (!m_hwnd) TK_EXCEPTION("WINDOW HANDLE ERROR");
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
			TK_UPDATE_RECT(m_hwnd, NULL);
		}
		void Window::RunWindow() {
			while (Run() != TK_MSG_EXIT) {}
		}
		void Window::MessageSend(tk::String winClass, tk::String winName, UINT msg, ULONG dataMsg) {
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
			} else { TK_EXCEPTION("SEND MESSAGE ERROR"); }
		}
	}
}

inline int TK_WinMain() {
	main();
}