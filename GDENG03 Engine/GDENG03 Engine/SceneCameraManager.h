#pragma once
#include"ACamera.h"

class SceneCameraManager
{
public:
	static SceneCameraManager* getInstance();
	static void destroy();

	void setSceneCamera(ACamera* scene_camera);
	void update();

	Matrix4x4 getSceneCameraViewMatrix();
	Matrix4x4 getSceneCameraProjectionMatrix();

private:
	SceneCameraManager();
	~SceneCameraManager();
	SceneCameraManager(SceneCameraManager const&) {};
	SceneCameraManager& operator =(SceneCameraManager const&) {};
	static SceneCameraManager* instance;

	ACamera* mSceneCamera = nullptr;
};