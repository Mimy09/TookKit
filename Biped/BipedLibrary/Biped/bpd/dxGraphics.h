#ifndef _DXGRAPHICS_H_
#define _DXGRAPHICS_H_
#include <windows.h>
#include "dxdef.h"
#include "dxd3d.h"

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
};
BPD_END
#endif // !_DXGRAPHICS_H_