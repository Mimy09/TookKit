#pragma once
#ifndef _DXD3D_H_
#define _DXD3D_H_
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include "Core\bpddef.h"
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <D3DX10math.h>

BPD_BEGIN
class dxD3D {
public:
	dxD3D();
	dxD3D(const dxD3D&);
	~dxD3D();

	bool initialize(int, int, bool, HWND, bool, float, float);
	void shutdown();

	void beginScene(float, float, float, float);
	void endScene();

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

	void getProjectionMatrix(D3DXMATRIX&);
	void getWorldMatrix(D3DXMATRIX&);
	void getOrthoMatrix(D3DXMATRIX&);

	void getVideoCardInfo(char*, int&);

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_worldMatrix;
	D3DXMATRIX m_orthoMatrix;
};
BPD_END
#endif // !_DXD3D_H_