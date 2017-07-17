#include "Biped\bpd\dxSystem.h"

BPD_BEGIN
dxSystem::dxSystem() {
	m_input = BPD_NULL;
	m_graphics = BPD_NULL;
}
dxSystem::dxSystem(const dxSystem& other) {}
dxSystem::~dxSystem() {}

bool dxSystem::initialize() {
	int screenW = 0, screenH = 0;
	bool result;

	// Initalize window
	initalizeWindow(screenW, screenH);

	// Create a new input object and initalize it
	m_input = new dxInput;
	if (!m_input) return false;
	m_input->initalize();

	// Create a new graphic object and initalize it
	m_graphics = new dxGraphics();
	if (!m_graphics) return false;
	result = m_graphics->initialize(screenW, screenH, m_hwnd);
	if (!result) return false;

	return true;
}

void dxSystem::shutdown() {
	// Release graphics
	if (m_graphics) {
		m_graphics->shutdown();
		BPD_SAFE_DELETE(m_graphics);
		m_graphics = 0;
	}
	// Release input
	if (m_input) {
		BPD_SAFE_DELETE(m_input);
		m_input = 0;
	}
	//Shutdown the window
	shutdownWindow();
	return;
}

void dxSystem::shutdownWindow() {
	ShowCursor(true);

	if (FULL_SCREEN) {
		ChangeDisplaySettings(BPD_NULL, 0);
	}

	DestroyWindow(m_hwnd);
	m_hwnd = BPD_NULL;

	UnregisterClass(m_appName, m_hinstance);
	m_hinstance = BPD_NULL;

	ApplicationHandle = BPD_NULL;
	return;
}

void dxSystem::run() {
	MSG msg;
	bool done = false, result;

	ZeroMemory(&msg, sizeof(msg));

	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT) { done = true; }
		else {
			result = frame();
			if (!result) done = true;
		}
	} return;
}

bool dxSystem::frame() {
	bool result;

	if (m_input->isKeyDown(VK_ESCAPE)) {
		return false;
	}
	result = m_graphics->frame();
	if (!result) return false;
	return true;
}

LRESULT CALLBACK dxSystem::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	switch (umsg) {
	case WM_KEYDOWN:
		m_input->keyDown((size_type)wparam);
		return 0;
	case WM_KEYUP:
		m_input->keyUp((size_type)wparam);
		return 0;
	default: return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

void dxSystem::initalizeWindow(int& screenW, int& screenH) {
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	ApplicationHandle = this;
	m_hinstance = GetModuleHandle(NULL);
	m_appName = "Engine";

	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.lpszClassName = m_appName;
	wc.hInstance = m_hinstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;
	wc.hIconSm = wc.hIcon;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);
	screenW = GetSystemMetrics(SM_CXSCREEN);
	screenH = GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN) {
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (size_type)screenW;
		dmScreenSettings.dmPelsHeight = (size_type)screenH;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		posX = posY = 0;
	} else {
		screenW = 800;
		screenH = 600;
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenW) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenH) / 2;
	}

	m_hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		m_appName,
		m_appName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenW, screenH, NULL, NULL, m_hinstance, NULL
	);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	ShowCursor(false);

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	switch (umessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default: return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
}


BPD_END