#include"ASwapChain.h"
#include"AGraphicsEngine.h"

ASwapChain::ASwapChain() {}

ASwapChain::~ASwapChain() {}

bool ASwapChain::initialize(HWND window_handle, UINT window_width, UINT window_height) {
	ID3D11Device* device = AGraphicsEngine::getInstance()->mDevice;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = window_width;
	desc.BufferDesc.Height = window_height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = window_handle;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT result = AGraphicsEngine::getInstance()->mdxgiFactory->CreateSwapChain(device, &desc, &mSwapChain);
	if (FAILED(result)) return false;

	ID3D11Texture2D* buffer = NULL;
	result = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	if (FAILED(result)) return false;

	result = device->CreateRenderTargetView(buffer, NULL, &mRenderTargetView);
	buffer->Release();
	if (FAILED(result)) return false;

	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = window_width;
	texDesc.Height = window_height;
	texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texDesc.MipLevels = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.MiscFlags = 0;
	texDesc.ArraySize = 1;
	texDesc.CPUAccessFlags = 0;

	buffer = nullptr;
	result = device->CreateTexture2D(&texDesc, NULL, &buffer);
	if (FAILED(result)) return false;

	result = device->CreateDepthStencilView(buffer, NULL, &this->mDepthStencilView);
	buffer->Release();
	if (FAILED(result)) return false;

	return true;
}

bool ASwapChain::release() {
	mSwapChain->Release();
	delete this;
	return true;
}

bool ASwapChain::present(bool vsync) {
	mSwapChain->Present(vsync, NULL);
	return true;
}

ID3D11RenderTargetView* ASwapChain::getRenderTargetView() {
	return mRenderTargetView;
}

ID3D11DepthStencilView* ASwapChain::getDepthStencilView() {
	return mDepthStencilView;
}