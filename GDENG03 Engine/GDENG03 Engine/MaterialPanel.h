#pragma once
#include "AUIPanel.h"
#include "Texture.h"
//#include "imfilebrowser.h"
#include "imgui/imfilebrowser.h"

class InspectorWindow;
class MaterialPanel : public AUIPanel
{

public:
	MaterialPanel(std::string name);
	~MaterialPanel();

	void setInspectorWindow(InspectorWindow* window);
	void setInspectorData(Texture* texture, std::string materialPath);

private:
	virtual void draw() override;
	friend class UIManager;

	ImGui::FileBrowser* openSceneDialog;
	InspectorWindow* inspectorWindow;

	std::string materialPath;
	Texture* displayTexture;

};