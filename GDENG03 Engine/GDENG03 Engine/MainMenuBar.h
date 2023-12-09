#pragma once
#include"AUIPanel.h"
#include "SceneSavePanel.h"
#include "SceneLoadPanel.h"

class MainMenuBar : public AUIPanel
{
public:
	MainMenuBar(std::string name);
	~MainMenuBar() {};

	void draw() override;

	void setSceneSavePanel(SceneSavePanel* savePanel);
	void setSceneLoadPanel(SceneLoadPanel* loadPanel);

private:
	SceneSavePanel* mSavePanel = nullptr;
	SceneLoadPanel* mLoadPanel = nullptr;
};