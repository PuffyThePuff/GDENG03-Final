#include"AIndexBuffer.h"
#include"AGraphicsEngine.h"

AIndexBuffer::AIndexBuffer() : mBuffer(0) {}

AIndexBuffer::~AIndexBuffer() {}

bool AIndexBuffer::load(void* index_list, UINT index_count) {
	if (mBuffer) mBuffer->Release();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = 4 * index_count;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = index_list;

	mIndexCount = index_count;

	HRESULT result = AGraphicsEngine::getInstance()->mDevice->CreateBuffer(&bufferDesc, &initData, &mBuffer);
	if (FAILED(result)) return false;

	return true;
}

UINT AIndexBuffer::getIndexCount() {
	return mIndexCount;
}

bool AIndexBuffer::release() {
	mBuffer->Release();
	delete this;
	return true;
}