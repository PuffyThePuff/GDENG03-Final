#pragma once
#include"AUIPanel.h"
#include<vector>
#include<unordered_map>
#include<Windows.h>
#include"imgui.h"
#include"imgui_impl_dx11.h"
#include"imgui_impl_win32.h"
#include"imgui_stdlib.h"
#include "SceneLoadPanel.h"
#include "SceneSavePanel.h"

class UIManager
{
public:
	enum PanelName {
		MAIN_MENU_TOOLBAR,
		SCENE_OUTLINER,
		INSPECTOR,
		ENGINE_PROFILER,
		SCENE_PLAY_PANEL,
		MATERIAL_PANEL
	};

	static UIManager* getInstance();
	static void initialize(HWND window_handle);
	static void destroy();

	void draw();
	AUIPanel* getPanel(PanelName panel_name);
	void setActive(AUIPanel* panel, bool is_enabled);

private:
	UIManager(HWND window_handle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator =(UIManager const&) {};
	static UIManager* instance;

	std::vector<AUIPanel*> mListUI;
};