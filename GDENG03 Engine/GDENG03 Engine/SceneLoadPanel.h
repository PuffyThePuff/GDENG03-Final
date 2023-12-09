#pragma once
#include "AUIPanel.h"
#include "SceneWriter.h"
#include <imgui.h>
//#include <imfilebrowser.h>
#include "imgui/imfilebrowser.h"

class SceneLoadPanel : public AUIPanel
{
public:
	SceneLoadPanel(std::string name);
	~SceneLoadPanel();

	void draw() override;
	void openExplorer();
	void closeExplorer();

	bool isEnabled();

private:
	ImGui::FileBrowser* browser;
};
