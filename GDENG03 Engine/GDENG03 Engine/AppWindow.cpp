#include"AppWindow.h"
#include<Windows.h>
#include"imgui.h"
#include"imgui_impl_dx11.h"
#include"imgui_impl_win32.h"
#include"imgui_stdlib.h"
#include"GlobalProperties.h"
#include<iostream>
#include"PhysicsComponent.h"
#include "ShaderLibrary.h"


#include "TextureManager.h"

AppWindow::AppWindow() {}

AppWindow::~AppWindow() {}

void AppWindow::onCreate() {
	AWindow::onCreate();
	GameObjectManager::initialize();
	AGraphicsEngine::getInstance()->initialize();
	TextureManager::initialize();
	ShaderLibrary::initialize();

	mSwapChain = AGraphicsEngine::getInstance()->createSwapChain();

	RECT windowRect = this->getWindowRect();
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;
	mSwapChain->initialize(this->mWindowHandle, width, height);

	SystemManager::initialize();
	BackendManager::initialize();
	ActionHistoryManager::initialize();

	ACamera* sceneCamera = new ACamera("UnregisteredHyperCam2");
	sceneCamera->setPosition(0.f, 1.f, -2.f);
	sceneCamera->setRotation(0.f, 0.f, 0.f);
	sceneCamera->setPerspectiveProjectionMatrix(1.57f, (float)width / (float)height, 0.1f, 100.f);
	SceneCameraManager::getInstance()->setSceneCamera(sceneCamera);

	UIManager::initialize(this->mWindowHandle);

	
}

void AppWindow::onUpdate() {
	AWindow::onUpdate();

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(
		mSwapChain,
		GlobalProperties::BACKGROUND_COLOR[0],
		GlobalProperties::BACKGROUND_COLOR[1],
		GlobalProperties::BACKGROUND_COLOR[2],
		1.f
	);

	RECT windowRect = this->getWindowRect();
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(width, height);

	InputManager::getInstance()->update();
	SceneCameraManager::getInstance()->update();

	switch (BackendManager::getInstance()->getEditorMode()) {
	case BackendManager::EDIT: {
		GameObjectManager::getInstance()->update();
	}
	break;

	case BackendManager::PLAY: {
		GameObjectManager::getInstance()->update();
		SystemManager::getInstance()->update();
	}
	break;

	case BackendManager::PAUSED: {
		if (BackendManager::getInstance()->isInFrameStep()) {
			GameObjectManager::getInstance()->update();
			SystemManager::getInstance()->update();
			BackendManager::getInstance()->endFrame();
		}
	}
	break;

	}

	GameObjectManager::getInstance()->draw(width, height);
	UIManager::getInstance()->draw();
	mSwapChain->present(false);
}

void AppWindow::onDestroy() {
	AWindow::onDestroy();
	mSwapChain->release();
	SystemManager::destroy();
	BackendManager::destroy();
	ActionHistoryManager::destroy();
	InputManager::destroy();
	SceneCameraManager::destroy();
	GameObjectManager::destroy();
	UIManager::destroy();
	AGraphicsEngine::getInstance()->release();
}