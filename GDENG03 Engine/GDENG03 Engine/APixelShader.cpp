#include"APixelShader.h"
#include"AGraphicsEngine.h"

APixelShader::APixelShader() {}

APixelShader::~APixelShader() {}

void APixelShader::release() {
	mPixelShader->Release();
	delete this;
}

ID3D11PixelShader* APixelShader::getShader()
{
	return mPixelShader;
}

bool APixelShader::initialize(const void* shader_byte_code, size_t byte_code_size) {
	HRESULT result = AGraphicsEngine::getInstance()->mDevice->CreatePixelShader(
		shader_byte_code,
		byte_code_size,
		nullptr,
		&mPixelShader
	);
	if (FAILED(result)) return false;

	return true;
}
