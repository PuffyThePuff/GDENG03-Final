#include"InspectorWindow.h"
#include"GlobalProperties.h"
#include"GameObjectManager.h"
#include"AngleConverter.h"
#include"ActionHistoryManager.h"
#include"BackendManager.h"
#include"SystemManager.h"
#include"PhysicsSystem.h"
#include<iostream>

#include "TexturedCube.h"
#include "TextureManager.h"
#include "UIManager.h"

InspectorWindow::InspectorWindow(std::string name) : AUIPanel::AUIPanel(name) {}

InspectorWindow::~InspectorWindow() {}

void InspectorWindow::draw() {
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("Inspector Window", NULL, windowFlags);
	ImGui::SetWindowSize(ImVec2(300, GlobalProperties::WINDOW_HEIGHT - 64));
	ImGui::SetWindowPos(ImVec2(GlobalProperties::WINDOW_WIDTH - 321, 20));

	if (!GameObjectManager::getInstance()->getSelectedObject()) {
		ImGui::TextWrapped("No object selected. Select an object from the scene.");
	}

	else {
		selectedObject = GameObjectManager::getInstance()->getSelectedObject();
		updatePanelInfo(selectedObject);

		ImGui::Text("Selected Object:");
		ImGui::SameLine();
		ImGui::Text(selectedObject->getObjectName().c_str());
		ImGui::Separator();

		if (BackendManager::getInstance()->getEditorMode() != BackendManager::EDIT) ImGui::BeginDisabled(); 

		if (ImGui::Checkbox("Enabled", &mIsSelectedObjectActive)) {
			updateObjectInfo(selectedObject);
			std::cout << "Action taken: Modified isActive." << std::endl;
		}

		if (ImGui::DragFloat3("Position", mObjectPosition, 0.25f)) {
			updateObjectInfo(selectedObject);
			std::cout << "Action taken: Modified position." << std::endl;
		}

		if (ImGui::DragFloat3("Rotation", mObjectRotation, 1.f, -360.f, 360.f)) {
			updateObjectInfo(selectedObject);
			std::cout << "Action taken: Modified rotation." << std::endl;
		}

		if (ImGui::DragFloat3("Scale", mObjectScale, 0.25f, 0.f, 100.f)) {
			updateObjectInfo(selectedObject);
			std::cout << "Action taken: Modified scale." << std::endl;
		}

		if (BackendManager::getInstance()->getEditorMode() != BackendManager::EDIT) ImGui::EndDisabled(); 

		ImGui::Text("Rigidbody: ");

		if (mHasPhysicsComponent) {
			if (BackendManager::getInstance()->getEditorMode() != BackendManager::EDIT) ImGui::BeginDisabled();

			if (ImGui::Button("Detach"))
				SystemManager::getInstance()->getPhysicsSystem()->unregisterComponent(mCurrentPhysicsComponent);

			if (ImGui::Checkbox("Enabled", &mActiveBody))
				mCurrentPhysicsComponent->setActive(mActiveBody);

			if (ImGui::Checkbox("Is Static", &mStaticBody))
				mCurrentPhysicsComponent->setStatic(mStaticBody);
			
			if (ImGui::Checkbox("Gravity Enabled", &mGravityBody))
				mCurrentPhysicsComponent->enableGravity(mGravityBody);
			
			if (ImGui::InputFloat("Mass", &mBodyMass))
				mCurrentPhysicsComponent->setMass(mBodyMass);

			if (BackendManager::getInstance()->getEditorMode() != BackendManager::EDIT) ImGui::EndDisabled();
			
			ImGui::DragFloat3("Applied Force Vector Components", mAppliedForce);
			
			if (ImGui::Button("Apply Force"))
				mCurrentPhysicsComponent->applyForce(mAppliedForce[0], mAppliedForce[1], mAppliedForce[2]);
		}

		else {
			ImGui::SameLine();
			ImGui::Text("None");

			if (BackendManager::getInstance()->getEditorMode() != BackendManager::EDIT) ImGui::BeginDisabled();

			if (ImGui::Button("Add Physics Component")) {
				PhysicsComponent* component = new PhysicsComponent(selectedObject->getObjectName() + " Physics");
				selectedObject->attachComponent(component);
			}

			if (BackendManager::getInstance()->getEditorMode() != BackendManager::EDIT) ImGui::EndDisabled();
		}

		if (selectedObject->getObjectType() == AGameObject::TEXTURED_CUBE) {
			TexturedCube* texturedCube = static_cast<TexturedCube*>(selectedObject);
			this->materialPath = texturedCube->getRenderer()->getMaterialPath();
			this->materialDisplay = texturedCube->getRenderer()->getTexture();
			ImGui::SetCursorPosX(50);
			ImGui::Image(static_cast<void*>(this->materialDisplay->getShaderResource()), ImVec2(150, 150));

			std::vector<std::string> splitPaths = splitPath(this->materialPath, '\\');
			this->materialName = splitPaths[splitPaths.size() - 1];

			std::string materialNameDisplay = "Material: " + this->materialName;
			ImGui::Text(materialNameDisplay.c_str());

			if (ImGui::Button("Add Material")) {
				//mIsPopupEnabled = !mIsPopupEnabled;
				materialScreen->setInspectorData(materialDisplay, materialPath);
				UIManager::getInstance()->setActive(materialScreen, true);
			}
		
		}

		if (BackendManager::getInstance()->getEditorMode() != BackendManager::EDIT) ImGui::BeginDisabled();

		if (ImGui::Button("Delete Object")) {
			GameObjectManager::getInstance()->deleteObject(selectedObject);
			std::cout << "Permanent action taken: Deleted object." << std::endl;
		}

		if (BackendManager::getInstance()->getEditorMode() != BackendManager::EDIT) ImGui::EndDisabled();
	}

	ImGui::End();
}

void InspectorWindow::setMaterialWindow(MaterialPanel* screen)
{
	materialScreen = screen;
}

void InspectorWindow::setMaterialWindowData(std::string materialPath)
{
	TexturedCube* texturedCube = static_cast<TexturedCube*>(selectedObject);
	texturedCube->getRenderer()->setMaterialPath(materialPath);
}

void InspectorWindow::updatePanelInfo(AGameObject* selected_object) {
	mIsSelectedObjectActive = selected_object->isActive();

	Vector3D position = selected_object->getLocalPosition();
	mObjectPosition[0] = position.x;
	mObjectPosition[1] = position.y;
	mObjectPosition[2] = position.z;

	Vector3D rotation = selected_object->getLocalRotation();
	mObjectRotation[0] = AngleConverter::toDegrees(rotation.x);
	mObjectRotation[1] = AngleConverter::toDegrees(rotation.y);
	mObjectRotation[2] = AngleConverter::toDegrees(rotation.z);

	Vector3D scale = selected_object->getLocalScale();
	mObjectScale[0] = scale.x;
	mObjectScale[1] = scale.y;
	mObjectScale[2] = scale.z;

	AComponent* component = selected_object->findComponentOfType(AComponent::PHYSICS);
	if (component) mHasPhysicsComponent = true;
	else mHasPhysicsComponent = false;

	if (!mHasPhysicsComponent) {
		mCurrentPhysicsComponent = nullptr;
		return;
	}

	PhysicsComponent* physics = (PhysicsComponent*)component;
	mCurrentPhysicsComponent = physics;
	mActiveBody = physics->isActive();
	mStaticBody = physics->isStatic();
	mGravityBody = physics->isGravityEnabled();
	mBodyMass = physics->getMass();
}

void InspectorWindow::updateObjectInfo(AGameObject* selected_object) {
	ActionHistoryManager::getInstance()->startAction(selected_object);

	selected_object->setActive(mIsSelectedObjectActive);
	selected_object->setScale(mObjectScale[0], mObjectScale[1], mObjectScale[2]);
	selected_object->setRotation(AngleConverter::toRadians(mObjectRotation[0]), AngleConverter::toRadians(mObjectRotation[1]), AngleConverter::toRadians(mObjectRotation[2]));
	selected_object->setPosition(mObjectPosition[0], mObjectPosition[1], mObjectPosition[2]);

	ActionHistoryManager::getInstance()->endAction();
}

std::vector<std::string> InspectorWindow::splitPath(const std::string& s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> strings;
	while (std::getline(ss, item, delim)) {
		strings.push_back(std::move(item));
	}
	return strings;
}