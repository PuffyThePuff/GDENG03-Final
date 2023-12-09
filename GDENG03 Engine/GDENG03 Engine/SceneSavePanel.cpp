#include "SceneSavePanel.h"

SceneSavePanel::SceneSavePanel(std::string name) : AUIPanel::AUIPanel(name)
{
	browser = new ImGui::FileBrowser(ImGuiFileBrowserFlags_NoModal | ImGuiFileBrowserFlags_EnterNewFilename | ImGuiFileBrowserFlags_CreateNewDir);
	browser->SetTitle("Save as");
	browser->SetTypeFilters({".iet", ".level"});
}

SceneSavePanel::~SceneSavePanel()
{
	delete this->browser;
}

void SceneSavePanel::draw()
{
	browser->Display();
	
	if (browser->HasSelected())
	{
		SceneWriter::WriteToFile(browser->GetSelected().string());
		browser->Close();
	}
}

void SceneSavePanel::openExplorer()
{
	browser->Open();
}

void SceneSavePanel::closeExplorer()
{
	browser->Close();
}

bool SceneSavePanel::isEnabled()
{
	return browser->IsOpened();
}