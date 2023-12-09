#pragma once
#include<d3d11.h>

class ADeviceContext;

class AIndexBuffer
{
public:
	AIndexBuffer();
	~AIndexBuffer();

	bool load(void* index_list, UINT index_count);
	UINT getIndexCount();
	bool release();

private:
	UINT mIndexCount;
	ID3D11Buffer* mBuffer;

	friend class ADeviceContext;
};