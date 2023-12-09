#pragma once
#include<d3d11.h>
#include"Vertex.h"

class ADeviceContext;

class AVertexBuffer
{
public:
	AVertexBuffer();
	~AVertexBuffer();

	virtual bool load(void* vertex_list, UINT vertex_size, UINT vertex_count, void* shader_byte_code, UINT shader_byte_size);
	UINT getVertexCount();
	bool release();

protected:
	UINT mVertexSize;
	UINT mVertexCount;
	ID3D11Buffer* mBuffer;
	ID3D11InputLayout* mLayout;

	friend class ADeviceContext;
};