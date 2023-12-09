#include"MainMenuBar.h"
#include"GameObjectManager.h"

MainMenuBar::MainMenuBar(std::string name) : AUIPanel::AUIPanel(name) {}

void MainMenuBar::draw() {
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("New")) {}
		if (ImGui::MenuItem("Save"))
		{
			if (!mSavePanel->isEnabled())
			{
				mSavePanel->openExplorer();
			}
		}
		if (ImGui::MenuItem("Open"))
		{
			if (!mLoadPanel->isEnabled())
			{
				mLoadPanel->openExplorer();
			}
		}
		if (ImGui::MenuItem("Exit")) {}
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Game Object")) {
		if (ImGui::MenuItem("Create Cube")) {
			GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE);
		}

		if (ImGui::MenuItem("Create Sphere")) {}

		if (ImGui::MenuItem("Create Plane")) {
			GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE);
		}

		if (ImGui::BeginMenu("Light")) {
			if (ImGui::MenuItem("Point Light")) {}
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Create Several Dynamic Physics Cubes")) {
			for (int i = 0; i < 30; i++) {
				GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_CUBE);
			}
		}

		if (ImGui::MenuItem("Create Dynamic Physics Cube")) {
			GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_CUBE);
		}

		if (ImGui::MenuItem("Create Static Physics Plane")) {
			GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_PLANE);
		}

		if (ImGui::MenuItem("Create Textured Cube")) {
			GameObjectManager::getInstance()->createObject(GameObjectManager::TEXTURED_CUBE);
		}

		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
}

void MainMenuBar::setSceneSavePanel(SceneSavePanel* savePanel)
{
	mSavePanel = savePanel;
}

void MainMenuBar::setSceneLoadPanel(SceneLoadPanel* loadPanel)
{
	mLoadPanel = loadPanel;
}