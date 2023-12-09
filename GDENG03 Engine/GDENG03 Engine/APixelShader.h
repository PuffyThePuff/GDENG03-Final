#pragma once
#include<d3d11.h>

class AGraphicsEngine;
class ADeviceContext;

class APixelShader
{
public:
	APixelShader();
	~APixelShader();
	void release();

	ID3D11PixelShader* getShader();

private:
	bool initialize(const void* shader_byte_code, size_t byte_code_size);

	ID3D11PixelShader* mPixelShader;

	friend class AGraphicsEngine;
	friend class ADeviceContext;
};