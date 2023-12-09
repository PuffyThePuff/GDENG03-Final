#include"AVertexBuffer.h"
#include"AGraphicsEngine.h"

AVertexBuffer::AVertexBuffer() : mBuffer(0), mLayout(0) {}

AVertexBuffer::~AVertexBuffer() {}

bool AVertexBuffer::load(void* vertex_list, UINT vertex_size, UINT vertex_count, void* shader_byte_code, UINT shader_byte_size) {
	if (mBuffer) mBuffer->Release();
	if (mLayout) mLayout->Release();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = vertex_size * vertex_count;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertex_list;

	mVertexSize = vertex_size;
	mVertexCount = vertex_count;
	
	HRESULT result = AGraphicsEngine::getInstance()->mDevice->CreateBuffer(&bufferDesc, &initData, &mBuffer);
	if (FAILED(result)) return false;

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},

		{
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			(sizeof(Vector3D) * 1),
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},

		{
			"COLOR",
			1,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			(sizeof(Vector3D) * 2),
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}
	};
	UINT layoutSize = ARRAYSIZE(layout);
	result = AGraphicsEngine::getInstance()->mDevice->CreateInputLayout(layout, layoutSize, shader_byte_code, shader_byte_size, &mLayout);
	if (FAILED(result)) return false;

	return true;
}

UINT AVertexBuffer::getVertexCount() {
	return mVertexCount;
}

bool AVertexBuffer::release() {
	mLayout->Release();
	mBuffer->Release();
	delete this;
	return true;
}