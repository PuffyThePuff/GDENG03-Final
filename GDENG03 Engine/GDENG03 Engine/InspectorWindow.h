#pragma once
#include"AUIPanel.h"
#include"AGameObject.h"
#include "MaterialPanel.h"
#include"PhysicsComponent.h"
#include "Texture.h"

class InspectorWindow : public AUIPanel
{
public:
	InspectorWindow(std::string name);
	~InspectorWindow();

	void draw() override;

	void setMaterialWindow(MaterialPanel* window);
	void setMaterialWindowData(std::string materialPath);

private:
	AGameObject* selectedObject = nullptr;

	void updatePanelInfo(AGameObject* selected_object);
	void updateObjectInfo(AGameObject* selected_object);

	std::vector<std::string> splitPath(const std::string& s, char delim);

	bool mIsSelectedObjectActive = true;
	float mObjectPosition[3] = {};
	float mObjectRotation[3] = {};
	float mObjectScale[3] = { 1.f, 1.f, 1.f };

	PhysicsComponent* mCurrentPhysicsComponent = nullptr;
	bool mHasPhysicsComponent = false;
	bool mActiveBody = true;
	bool mStaticBody = false;
	bool mGravityBody = true;
	float mBodyMass = 1000.f;
	float mAppliedForce[3] = {};

	// Add other members needed for textures tab here.
	bool mIsPopupEnabled = false;

	//textures
	MaterialPanel* materialScreen;
	std::string materialPath;
	std::string materialName;
	Texture* materialDisplay;
};
