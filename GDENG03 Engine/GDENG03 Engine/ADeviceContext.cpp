#include"ADeviceContext.h"
#include"ASwapChain.h"
#include"AVertexBuffer.h"
#include"AIndexBuffer.h"
#include"AConstantBuffer.h"
#include"AVertexShader.h"
#include"APixelShader.h"
#include "Texture.h"

ADeviceContext::ADeviceContext(ID3D11DeviceContext* device_context) {
	mDeviceContext = device_context;
}

ADeviceContext::~ADeviceContext() {}

void ADeviceContext::clearRenderTargetColor(ASwapChain* swap_chain, float red, float green, float blue, float alpha) {
	FLOAT clearColor[] = { red, green, blue, alpha };
	mDeviceContext->ClearRenderTargetView(swap_chain->mRenderTargetView, clearColor);
	mDeviceContext->ClearDepthStencilView(swap_chain->mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	mDeviceContext->OMSetRenderTargets(1, &(swap_chain->mRenderTargetView), swap_chain->mDepthStencilView);
}

void ADeviceContext::setVertexBuffer(AVertexBuffer* vertex_buffer) {
	UINT stride = vertex_buffer->mVertexSize;
	UINT offset = 0;
	mDeviceContext->IASetVertexBuffers(0, 1, &(vertex_buffer->mBuffer), &stride, &offset);
	mDeviceContext->IASetInputLayout(vertex_buffer->mLayout);
}

void ADeviceContext::setIndexBuffer(AIndexBuffer* index_buffer) {
	mDeviceContext->IASetIndexBuffer(index_buffer->mBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void ADeviceContext::setViewportSize(UINT width, UINT height) {
	D3D11_VIEWPORT viewport = {};
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.f;
	viewport.MaxDepth = 1.f;
	mDeviceContext->RSSetViewports(1, &viewport);
}

void ADeviceContext::setVertexShader(AVertexShader* vertex_shader) {
	mDeviceContext->VSSetShader(vertex_shader->mVertexShader, nullptr, 0);
}

void ADeviceContext::setPixelShader(APixelShader* pixel_shader) {
	mDeviceContext->PSSetShader(pixel_shader->mPixelShader, nullptr, 0);
}

void ADeviceContext::setConstantBuffer(AConstantBuffer* constant_buffer, AVertexShader* vertex_shader) {
	mDeviceContext->VSSetConstantBuffers(0, 1, &constant_buffer->mBuffer);
}

void ADeviceContext::setConstantBuffer(AConstantBuffer* constant_buffer, APixelShader* pixel_shader) {
	mDeviceContext->PSSetConstantBuffers(0, 1, &constant_buffer->mBuffer);
}

void ADeviceContext::setTexture(Texture* texture)
{
	mDeviceContext->PSSetShaderResources(0, 1, &texture->m_shader_res_view);
	mDeviceContext->VSSetShaderResources(0, 1, &texture->m_shader_res_view);
}

void ADeviceContext::setRenderConfig(AVertexShader* vertexShader, APixelShader* pixelShader)
{
	this->mDeviceContext->VSSetShader(vertexShader->getShader(), NULL, 0);
	this->mDeviceContext->PSSetShader(pixelShader->getShader(), NULL, 0);
}


ID3D11DeviceContext* ADeviceContext::getD3DDeviceContext() {
	return mDeviceContext;
}

void ADeviceContext::drawTriangleList(UINT vertex_count, UINT initial_vertex_index) {
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mDeviceContext->Draw(vertex_count, initial_vertex_index);
}

void ADeviceContext::drawIndexedTriangleList(UINT index_count, UINT start_index_location, UINT base_vertex_location) {
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mDeviceContext->DrawIndexed(index_count, start_index_location, base_vertex_location);
}

void ADeviceContext::drawTriangleStrip(UINT vertex_count, UINT initial_vertex_index) {
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	mDeviceContext->Draw(vertex_count, initial_vertex_index);
}

void ADeviceContext::drawShape(D3D_PRIMITIVE_TOPOLOGY topology_type, UINT vertex_count, UINT initial_vertex_index) {
	mDeviceContext->IASetPrimitiveTopology(topology_type);
	mDeviceContext->Draw(vertex_count, initial_vertex_index);
}

bool ADeviceContext::release() {
	mDeviceContext->Release();
	delete this;
	return true;
}