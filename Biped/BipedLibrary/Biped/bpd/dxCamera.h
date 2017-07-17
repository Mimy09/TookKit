#ifndef _DXCAMERA_H_
#define _DXCAMERA_H_
#include "Core\dxdef.h"
#include <D3DX10math.h>

BPD_BEGIN
class dxCamera{
public:
	dxCamera();
	dxCamera(const dxCamera&);
	~dxCamera();

	void setPosition(float, float, float);
	void setRotation(float, float, float);

	D3DXVECTOR3 getPosition();
	D3DXVECTOR3 getRotation();

	void render();
	void getViewMatrix(D3DXMATRIX&);
private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXMATRIX m_viewMatrix;
};
BPD_END
#endif // !_DXCAMERA_H_
