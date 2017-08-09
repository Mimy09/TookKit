#pragma comment(lib, "d2d1")
#pragma comment(lib, "Dwrite")

#include <d2d1.h>
#include <dwrite.h>


struct d2d1Handle_bpd {
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IDWriteFactory* m_pWriteFactory;
};

struct WindowHandle_bpd {
	int width, height;
	bool fullscreen;
};