#include "Biped\bpd\dxCamera.h"
BPD_BEGIN
dxCamera::dxCamera(){
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}
dxCamera::dxCamera(const dxCamera& other){}
dxCamera::~dxCamera(){}

void dxCamera::setPosition(float x, float y, float z){
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}
void dxCamera::setRotation(float x, float y, float z){
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

D3DXVECTOR3 dxCamera::getPosition(){
	return D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
}
D3DXVECTOR3 dxCamera::getRotation(){
	return D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);
}

void dxCamera::render(){
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
	lookAt = position + lookAt;
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);
	return;
}
void dxCamera::getViewMatrix(D3DXMATRIX& viewMatrix){
	viewMatrix = m_viewMatrix;
	return;
}

BPD_END