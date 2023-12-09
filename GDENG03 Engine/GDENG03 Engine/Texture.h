#pragma once
#include "Resource.h"
#include <d3d11.h>

class Texture : public AResource
{
public:
	Texture(const wchar_t* fullPath);
	~Texture();
	AResource::String getPath();
	ID3D11ShaderResourceView* getShaderResource();

private:
	ID3D11Resource* m_texture = nullptr;
	ID3D11ShaderResourceView* m_shader_res_view = nullptr;

	friend class ADeviceContext;
};

/*
#pragma once
#include <d3d11.h>

class Texture
{
public:
	Texture(const wchar_t* full_path);
	~Texture();

private:
	ID3D11Resource* m_texture = nullptr;
	ID3D11ShaderResourceView* m_shader_res_view = nullptr;
private:
	friend class ADeviceContext;
};
*/
