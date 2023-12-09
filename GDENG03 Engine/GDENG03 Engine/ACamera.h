#pragma once
#include"AGameObject.h"
#include"AInputListener.h"
#include"Matrix4x4.h"

class ACamera : public AGameObject, public AInputListener
{
public:
	ACamera(std::string name);
	~ACamera();

	void update(float delta_time) override;
	Matrix4x4 getViewMatrix();

	void setOrthographicProjectionMatrix(float width, float height, float near_plane, float far_plane);
	void setPerspectiveProjectionMatrix(float field_of_view, float aspect, float near_plane, float far_plane);
	Matrix4x4 getProjectionMatrix();

	void onPress(int key) override;
	void onRelease(int key) override;
	void onMouseMove(const Point delta_position) override;
	void onLMBPress(const Point mouse_position) override;
	void onLMBRelease(const Point mouse_position) override;
	void onRMBPress(const Point mouse_position) override;
	void onRMBRelease(const Point mouse_position) override;

	void draw(int width, int height) override;

private:
	Matrix4x4 mProjectionMatrix;
};