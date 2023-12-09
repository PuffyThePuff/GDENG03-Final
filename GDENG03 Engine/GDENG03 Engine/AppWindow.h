#pragma once
#include"AWindow.h"
#include"AGraphicsEngine.h"
#include"GameObjectManager.h"
#include"InputManager.h"
#include"SceneCameraManager.h"
#include"UIManager.h"
#include"SystemManager.h"
#include"BackendManager.h"
#include"ActionHistoryManager.h"

#include"ASwapChain.h"
#include"ADeviceContext.h"
#include"AVertexBuffer.h"
#include"AIndexBuffer.h"
#include"AConstantBuffer.h"
#include"AVertexShader.h"
#include"APixelShader.h"
#include"AGameObject.h"
#include"ACube.h"
#include"APlane.h"
#include"ACamera.h"
#include"Vertex.h"
#include"Matrix4x4.h"
#include"Randomizer.h"
#include<vector>

class AppWindow : public AWindow
{
public:
	AppWindow();
	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

private:
	ASwapChain* mSwapChain;
};