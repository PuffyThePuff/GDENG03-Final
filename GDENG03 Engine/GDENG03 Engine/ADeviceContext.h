#pragma once
#include<d3d11.h>

class ASwapChain;
class AVertexBuffer;
class AIndexBuffer;
class AConstantBuffer;
class AVertexShader;
class APixelShader;
class Texture;

class ADeviceContext
{
public:
	ADeviceContext(ID3D11DeviceContext* device_context);
	~ADeviceContext();

	void clearRenderTargetColor(ASwapChain* swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(AVertexBuffer* vertex_buffer);
	void setIndexBuffer(AIndexBuffer* index_buffer);
	void setViewportSize(UINT width, UINT height);
	void setVertexShader(AVertexShader* vertex_shader);
	void setPixelShader(APixelShader* pixel_shader);
	void setConstantBuffer(AConstantBuffer* constant_buffer, AVertexShader* vertex_shader);
	void setConstantBuffer(AConstantBuffer* constant_buffer, APixelShader* pixel_shader);
	void setTexture(Texture* texture);
	void setRenderConfig(AVertexShader* vertexShader, APixelShader* pixelShader);

	ID3D11DeviceContext* getD3DDeviceContext();

	void drawTriangleList(UINT vertex_count, UINT initial_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_index_location, UINT base_vertex_location);
	void drawTriangleStrip(UINT vertex_count, UINT initial_vertex_index);
	void drawShape(D3D_PRIMITIVE_TOPOLOGY topology_type, UINT vertex_count, UINT initial_vertex_index);

	bool release();

protected:
	ID3D11DeviceContext* mDeviceContext;

	friend class AConstantBuffer;
};