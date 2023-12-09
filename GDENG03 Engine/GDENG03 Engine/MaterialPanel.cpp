#include "MaterialPanel.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "TextureManager.h"
#include "Texture.h"
#include "InspectorWindow.h"

void MaterialPanel::setInspectorData(Texture* texture, std::string materialPath)
{
	this->materialPath = materialPath;
	displayTexture = texture;
	
}

MaterialPanel::MaterialPanel(std::string name) : AUIPanel(name)
{
	this->openSceneDialog = new ImGui::FileBrowser();
	this->openSceneDialog->SetTitle("Open Material");
	this->openSceneDialog->SetTypeFilters({ ".jpg", ".png" });

}

MaterialPanel::~MaterialPanel()
{

}

void MaterialPanel::setInspectorWindow(InspectorWindow* window)
{
	this->inspectorWindow = window;
}

void MaterialPanel::draw()
{
	if (this->mIsEnabled)
	{
		int WINDOW_WIDTH = 400;
		int WINDOW_HEIGHT = 400;

		ImGui::Begin("Materials Editor", 0, ImGuiWindowFlags_NoResize);
		ImGui::SetWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));

		ImGui::SetCursorPosX(50);
		ImGui::Image(static_cast<void*>(this->displayTexture->getShaderResource()), ImVec2(300, 300));

		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		if (ImGui::Button("Load Texture", ImVec2(WINDOW_WIDTH - 20, 20)))
		{
			this->openSceneDialog->Open();
		}

		if (ImGui::Button("Apply", ImVec2(WINDOW_WIDTH - 20, 20)))
		{
			this->mIsEnabled = false;
			inspectorWindow->setMaterialWindowData(this->materialPath);
		}

		this->openSceneDialog->Display();
		if (this->openSceneDialog->HasSelected())
		{

			std::string textureString = this->openSceneDialog->GetSelected().string();
			std::wstring widestr = std::wstring(textureString.begin(), textureString.end());
			const wchar_t* texturePath = widestr.c_str();

			this->displayTexture = static_cast<Texture*>(TextureManager::getInstance()->createTextureFromFile(texturePath));
			this->materialPath = textureString;
			this->openSceneDialog->ClearSelected();
			this->openSceneDialog->Close();
		}
		ImGui::End();
	}

}
