#include "TexturedVertexBuffer.h"
#include "AGraphicsEngine.h"
#include <iostream>

TexturedVertexBuffer::TexturedVertexBuffer() : AVertexBuffer()
{
}

TexturedVertexBuffer::~TexturedVertexBuffer()
{
	TexturedVertexBuffer::~TexturedVertexBuffer();
}

bool TexturedVertexBuffer::load(void* vertex_list, UINT vertex_size, UINT vertex_count, void* shader_byte_code, UINT shader_byte_size)
{
	//release if previous buffer and input layout are used from previous frame update.
	if (this->mBuffer != NULL) {
		this->mBuffer->Release();
	}

	if (this->mLayout != NULL) {
		this->mLayout->Release();
	}

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = vertex_size * vertex_count;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertex_list;

	this->mVertexSize = vertex_size;
	this->mVertexCount = vertex_count;

	ID3D11Device* directXDevice = AGraphicsEngine::getInstance()->getD3DDevice();
	HRESULT bufferResult = directXDevice->CreateBuffer(&bufferDesc, &initData, &this->mBuffer);
	if (SUCCEEDED(bufferResult)) {
		std::cout << "Creation of textured buffer succeeded. \n";
	}
	else {
		std::cout << "An error occurred in creating a textured buffer. \n";
	}

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		//semantic name - index, format, input slot, aligned byte offset, input slot class, instance data step rate
		//2 bytes each entry
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	UINT layoutSize = ARRAYSIZE(layout);
	HRESULT layoutResult = directXDevice->CreateInputLayout(layout, layoutSize, shader_byte_code, shader_byte_size, &this->mLayout);
	if (SUCCEEDED(layoutResult)) {
		std::cout << "Creation of input layout succeeded. \n";
	}
	else {
		std::cout << "An error occurred in creating an input layout. \n";
		return false;
	}

	return true;
}