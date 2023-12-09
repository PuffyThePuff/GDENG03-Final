#pragma once
#include<d3d11.h>

class AGraphicsEngine;
class ADeviceContext;

class AVertexShader
{
public:
	AVertexShader();
	~AVertexShader();

	void release();
	ID3D11VertexShader* getShader();
private:
	bool initialize(const void* shader_byte_code, size_t byte_code_size);

	ID3D11VertexShader* mVertexShader;

	friend class AGraphicsEngine;
	friend class ADeviceContext;
};