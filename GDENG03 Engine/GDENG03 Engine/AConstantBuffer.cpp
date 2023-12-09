#include"AConstantBuffer.h"
#include"AGraphicsEngine.h"
#include"ADeviceContext.h"

AConstantBuffer::AConstantBuffer() {}

AConstantBuffer::~AConstantBuffer() {}

bool AConstantBuffer::load(void* buffer, UINT buffer_size) {
	if (mBuffer) mBuffer->Release();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = buffer_size;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = buffer;

	HRESULT result = AGraphicsEngine::getInstance()->mDevice->CreateBuffer(&bufferDesc, &initData, &mBuffer);
	if (FAILED(result)) return false;

	return true;
}

void AConstantBuffer::update(ADeviceContext* device_context, void* buffer) {
	device_context->mDeviceContext->UpdateSubresource(mBuffer, NULL, NULL, buffer, NULL, NULL);
}

bool AConstantBuffer::release() {
	if (mBuffer) mBuffer->Release();
	delete this;
	return true;
}