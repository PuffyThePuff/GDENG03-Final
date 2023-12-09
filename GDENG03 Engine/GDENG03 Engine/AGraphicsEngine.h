#pragma once
#include<d3d11.h>
#include<d3dcompiler.h>

class ASwapChain;
class ADeviceContext;
class AVertexBuffer;
class AIndexBuffer;
class AConstantBuffer;
class AVertexShader;
class APixelShader;
class TexturedVertexBuffer;

class AGraphicsEngine
{
public:
	AGraphicsEngine();
	~AGraphicsEngine();

	bool initialize();
	bool release();

	ASwapChain* createSwapChain();
	AVertexBuffer* createVertexBuffer();
	TexturedVertexBuffer* createTexturedVertexBuffer();
	AIndexBuffer* createIndexBuffer();
	AConstantBuffer* createConstantBuffer();
	AVertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	
	APixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);

	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledVertexShader();
	void releaseCompiledPixelShader();

	ID3D11Device* getD3DDevice();
	ADeviceContext* getImmediateDeviceContext();

public:
	static AGraphicsEngine* getInstance();

protected:
	ID3D11Device* mDevice;
	D3D_FEATURE_LEVEL* mFeatureLevel;
	ADeviceContext* mImmediateContext;

	IDXGIDevice* mdxgiDevice;
	IDXGIAdapter* mdxgiAdapter;
	IDXGIFactory* mdxgiFactory;
	ID3D11DeviceContext* mInnerImmContext;

	ID3DBlob* mVertexBlob = nullptr;
	ID3DBlob* mPixelBlob = nullptr;
	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;

	ID3DBlob* mCustomVertexBlob = nullptr;
	ID3DBlob* mCustomPixelBlob = nullptr;

	friend class ASwapChain;
	friend class AVertexBuffer;
	friend class AIndexBuffer;
	friend class AConstantBuffer;
	friend class AVertexShader;
	friend class APixelShader;
	friend class TexturedVertexBuffer;
};