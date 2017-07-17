#ifndef _DXMODEL_H_
#define _DXMODEL_H_
#include "Core\bpddef.h"
#include <D3D11.h>
#include <D3DX10math.h>

BPD_BEGIN
class dxModel{
private:
	struct VertexType{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};
public:
	dxModel();
	dxModel(const dxModel&);
	~dxModel();

	bool initialize(ID3D11Device*);
	void shutdown();
	void render(ID3D11DeviceContext*);

	int getIndexCount();
private:
	bool initializeBuffers(ID3D11Device*);
	void shutdownBuffers();
	void renderBuffers(ID3D11DeviceContext*);
private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
};
BPD_END
#endif // !_DXMODEL_H_
