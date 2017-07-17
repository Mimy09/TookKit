#include "Biped\bpd\dxGraphics.h"
BPD_BEGIN
dxGraphics::dxGraphics() {
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_ColorShader = 0;

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
	m_Camera = new dxCamera;
	if(!m_Camera){ return false; }

	m_Camera->setPosition(0.0f, 0.0f, -10.0f);

	m_Model = new dxModel;
	if(!m_Model){ return false;	}

	result = m_Model->initialize(m_D3D->getDevice());
	if(!result){
		MessageBoxW(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_ColorShader = new dxColorShader;
	if(!m_ColorShader){ return false; }

	// Initialize the color shader object.
	result = m_ColorShader->initialize(m_D3D->getDevice(), hwnd);
	if(!result){
		MessageBoxW(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}
void dxGraphics::shutdown() {
	if(m_ColorShader){
		m_ColorShader->shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	if(m_Model){
		m_Model->shutdown();
		delete m_Model;
		m_Model = 0;
	}

	if(m_Camera){
		delete m_Camera;
		m_Camera = 0;
	}

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
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;
	bool result;
	m_D3D->beginScene(0.0f, 0.0f, 0.0f, 1.0f);
	m_Camera->render();

	m_Camera->getViewMatrix(viewMatrix);
	m_D3D->getWorldMatrix(worldMatrix);
	m_D3D->getProjectionMatrix(projectionMatrix);

	m_Model->render(m_D3D->getDeviceContext());

	result = m_ColorShader->render(m_D3D->getDeviceContext(), m_Model->getIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if(!result){ return false; }
	m_D3D->endScene();
	return true;
}
BPD_END