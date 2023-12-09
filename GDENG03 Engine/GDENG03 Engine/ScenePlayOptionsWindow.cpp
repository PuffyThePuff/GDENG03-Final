#include"ScenePlayOptionsWindow.h"
#include"BackendManager.h"
#include"ActionHistoryManager.h"
#include"GameObjectManager.h"

ScenePlayOptionsWindow::ScenePlayOptionsWindow(std::string name) : AUIPanel::AUIPanel(name) {}

ScenePlayOptionsWindow::~ScenePlayOptionsWindow() {}

void ScenePlayOptionsWindow::draw() {
	ImGui::Begin("Scene Play Options");

	switch (BackendManager::getInstance()->getEditorMode()) {
	case BackendManager::EDIT: {
		if (ImGui::Button("Play")) {
			GameObjectManager::getInstance()->saveInitialStates();
			BackendManager::getInstance()->setEditorMode(BackendManager::PLAY);
		}
	}
	break;

	case BackendManager::PLAY: {
		if (ImGui::Button("Stop")) {
			BackendManager::getInstance()->setEditorMode(BackendManager::EDIT);
			GameObjectManager::getInstance()->restoreInitialStates();
		}
		ImGui::SameLine();
		if (ImGui::Button("Pause")) BackendManager::getInstance()->setEditorMode(BackendManager::PAUSED);
		ImGui::SameLine();
		ImGui::BeginDisabled();
		ImGui::Button("Next Frame");
		ImGui::EndDisabled();
	}
	break;

	case BackendManager::PAUSED: {
		if (ImGui::Button("Stop")) {
			BackendManager::getInstance()->setEditorMode(BackendManager::EDIT);
			GameObjectManager::getInstance()->restoreInitialStates();
		}
		ImGui::SameLine();
		if (ImGui::Button("Resume")) BackendManager::getInstance()->setEditorMode(BackendManager::PLAY);
		ImGui::SameLine();
		if (ImGui::Button("Next Frame")) BackendManager::getInstance()->startFrame();
	}
	break;

	}

	ImGui::Separator();
	if (ImGui::Button("Undo")) {
		ActionHistoryManager* history = ActionHistoryManager::getInstance();
		if (history->canUndo()) history->undoAction();
	}
	ImGui::SameLine();
	if (ImGui::Button("Redo")) {
		ActionHistoryManager* history = ActionHistoryManager::getInstance();
		if (history->canRedo()) history->redoAction();
	}

	ImGui::End();
}