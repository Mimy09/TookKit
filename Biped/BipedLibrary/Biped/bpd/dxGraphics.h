#ifndef _DXGRAPHICS_H_
#define _DXGRAPHICS_H_
#include <windows.h>
#include "Core/dxdef.h"
#include "dxd3d.h"
#include "dxCamera.h"
#include "dxColorShader.h"
#include "dxModel.h"

BPD_BEGIN
class dxGraphics {
public:
	dxGraphics();
	dxGraphics(const dxGraphics&);
	~dxGraphics();

	bool initialize(int, int, HWND);
	void shutdown();
	bool frame();
private:
	bool render();
private:
	dxD3D* m_D3D;
	dxCamera* m_Camera;
	dxModel* m_Model;
	dxColorShader* m_ColorShader;
};
BPD_END
#endif // !_DXGRAPHICS_H_