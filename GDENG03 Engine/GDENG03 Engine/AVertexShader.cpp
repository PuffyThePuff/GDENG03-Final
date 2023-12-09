#include"AVertexShader.h"
#include"AGraphicsEngine.h"

AVertexShader::AVertexShader() {}

AVertexShader::~AVertexShader() {}

void AVertexShader::release() {
	mVertexShader->Release();
	delete this;
}

ID3D11VertexShader* AVertexShader::getShader()
{
	return mVertexShader;
}

bool AVertexShader::initialize(const void* shader_byte_code, size_t byte_code_size) {
	HRESULT result = AGraphicsEngine::getInstance()->mDevice->CreateVertexShader(
		shader_byte_code,
		byte_code_size,
		nullptr,
		&mVertexShader
	);
	if (FAILED(result)) return false;

	return true;
}
