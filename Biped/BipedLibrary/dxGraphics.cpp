#include "Biped\bpd\dxGraphics.h"
BPD_BEGIN
dxGraphics::dxGraphics() {
	m_D3D = 0;
}
dxGraphics::dxGraphics(const dxGraphics& other) {}
dxGraphics::~dxGraphics() {}

bool dxGraphics::initialize(int screenW, int screenH, HWND hwnd) {
	bool result;

	m_D3D = new dxD3D;
	if (!m_D3D) { return false; }

	result = m_D3D->initialize(screenW, screenH, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result) {
		MessageBox(hwnd, "Could not initialize Direct3D", "Error", MB_OK);
		return false;
	}
	return true;
}
void dxGraphics::shutdown() {
	if (m_D3D) {
		m_D3D->shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	return;
}
bool dxGraphics::frame() {
	bool result;
	result = render();
	if (!result) {
		return false;
	}
	return true;
}
bool dxGraphics::render() { 
	m_D3D->beginScene(0.8f, 0.8f, 0.8f, 1.0f);
	m_D3D->endScene();
	return true;
}
BPD_END