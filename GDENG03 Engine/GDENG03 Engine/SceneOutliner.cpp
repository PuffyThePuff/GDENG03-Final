#include"SceneOutliner.h"
#include"GameObjectManager.h"
#include"GlobalProperties.h"

SceneOutliner::SceneOutliner(std::string name) : AUIPanel::AUIPanel(name) {}

SceneOutliner::~SceneOutliner() {}

void SceneOutliner::draw() {
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("Scene Outliner", NULL, windowFlags);
	ImGui::SetWindowSize(ImVec2(300, GlobalProperties::WINDOW_HEIGHT - 64));
	ImGui::SetWindowPos(ImVec2(GlobalProperties::WINDOW_WIDTH - 622, 20));

	std::vector<AGameObject*> objectList = GameObjectManager::getInstance()->getAllGameObjects();
	for (int i = 0; i < objectList.size(); i++) {
		if (objectList[i] == GameObjectManager::getInstance()->getSelectedObject()) {
			if (ImGui::Button(objectList[i]->getObjectName().c_str(), ImVec2(298, 20))) {
				GameObjectManager::getInstance()->deselectObject();
			}
		}

		else {
			if (ImGui::Button(objectList[i]->getObjectName().c_str(), ImVec2(298, 20))) {
				GameObjectManager::getInstance()->setSelectedObject(objectList[i]);
			}
		}
	}

	ImGui::End();
}