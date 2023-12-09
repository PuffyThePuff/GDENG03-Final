#include "SceneLoadPanel.h"

SceneLoadPanel::SceneLoadPanel(std::string name) : AUIPanel::AUIPanel(name)
{
	browser = new ImGui::FileBrowser(ImGuiFileBrowserFlags_NoModal | ImGuiFileBrowserFlags_EnterNewFilename | ImGuiFileBrowserFlags_CreateNewDir);
	browser->SetTitle("Open");
	browser->SetTypeFilters({".iet", ".unity"});
}

SceneLoadPanel::~SceneLoadPanel()
{
	delete this->browser;
}

void SceneLoadPanel::draw()
{
	browser->Display();

	if (browser->HasSelected())
	{
		if (browser->GetSelected().string().find(".iet") != std::string::npos)
		{
			SceneWriter::LoadFromFile(browser->GetSelected().string());
		}
		else if (browser->GetSelected().string().find(".unity") != std::string::npos)
		{
			SceneWriter::LoadFromUnityFile(browser->GetSelected().string());
		}
		browser->Close();
	}
}

void SceneLoadPanel::openExplorer()
{
	browser->Open();
}

void SceneLoadPanel::closeExplorer()
{
	browser->Close();
}

bool SceneLoadPanel::isEnabled()
{
	return browser->IsOpened();
}