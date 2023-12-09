#include"SceneCameraManager.h"
#include"TimeManager.h"

SceneCameraManager* SceneCameraManager::instance = nullptr;

SceneCameraManager* SceneCameraManager::getInstance() {
	if (!instance) instance = new SceneCameraManager();
	return instance;
}

void SceneCameraManager::destroy() {
	delete instance->mSceneCamera;
}

void SceneCameraManager::setSceneCamera(ACamera* scene_camera) {
	mSceneCamera = scene_camera;
}

void SceneCameraManager::update() {
	mSceneCamera->update(TimeManager::getDeltaTime());
}

Matrix4x4 SceneCameraManager::getSceneCameraViewMatrix() {
	return mSceneCamera->getViewMatrix();
}

Matrix4x4 SceneCameraManager::getSceneCameraProjectionMatrix() {
	return mSceneCamera->getProjectionMatrix();
}

SceneCameraManager::SceneCameraManager() {}

SceneCameraManager::~SceneCameraManager() {
	delete instance;
}