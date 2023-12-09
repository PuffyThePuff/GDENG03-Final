#pragma once
#include<d3d11.h>
#include"Vertex.h"

class ADeviceContext;

class AConstantBuffer
{
public:
	AConstantBuffer();
	~AConstantBuffer();

	bool load(void* buffer, UINT buffer_size);
	void update(ADeviceContext* device_context, void* buffer);
	bool release();

private:
	ID3D11Buffer* mBuffer;

	friend class ADeviceContext;
};