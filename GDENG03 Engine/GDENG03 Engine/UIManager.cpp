#include"UIManager.h"
#include"AGraphicsEngine.h"
#include"ADeviceContext.h"
#include"MainMenuBar.h"
#include"InspectorWindow.h"
#include"SceneOutliner.h"
#include"EngineProfiler.h"
#include"ScenePlayOptionsWindow.h"
#include "MaterialPanel.h"

UIManager* UIManager::instance = nullptr;

UIManager* UIManager::getInstance() {
    return instance;
}

void UIManager::initialize(HWND window_handle) {
    instance = new UIManager(window_handle);
}

void UIManager::destroy() {
    for (int i = 0; i < instance->mListUI.size(); i++) {
        delete instance->mListUI[i];
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void UIManager::draw() {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (int i = 0; i < mListUI.size(); i++) {
        if (mListUI[i]->mIsEnabled) mListUI[i]->draw();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

AUIPanel* UIManager::getPanel(PanelName panel_name) {
    int index = panel_name;
    if (index >= 0 && index < mListUI.size()) return mListUI[index];
    else return nullptr;
}

void UIManager::setActive(AUIPanel* panel, bool is_enabled) {
    panel->mIsEnabled = is_enabled;
}

UIManager::UIManager(HWND window_handle) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplWin32_Init(window_handle);
    ImGui_ImplDX11_Init(
        AGraphicsEngine::getInstance()->getD3DDevice(),
        AGraphicsEngine::getInstance()->getImmediateDeviceContext()->getD3DDeviceContext()
    );

    MainMenuBar* mainMenuBar = new MainMenuBar("Toolbar");
    mListUI.push_back(mainMenuBar);

    SceneOutliner* sceneOutliner = new SceneOutliner("Scene Outliner");
    mListUI.push_back(sceneOutliner);

    InspectorWindow* inspectorWindow = new InspectorWindow("Inspector Window");
    mListUI.push_back(inspectorWindow);

    EngineProfiler* engineProfiler = new EngineProfiler("Engine Profiler");
    mListUI.push_back(engineProfiler);

    ScenePlayOptionsWindow* scenePlay = new ScenePlayOptionsWindow("Scene Play Options");
    mListUI.push_back(scenePlay);

    // Add material panel constructor here.
    MaterialPanel* materialScreen = new MaterialPanel("Material Screen");
    materialScreen->mIsEnabled = false;
    materialScreen->setInspectorWindow(inspectorWindow);
    mListUI.push_back(materialScreen);

    //Set material screen in inspector window
    inspectorWindow->setMaterialWindow(materialScreen);

    //Scene save and load options
    SceneSavePanel* savePanel = new SceneSavePanel("Save Panel");
    mListUI.push_back(savePanel);
    mainMenuBar->setSceneSavePanel(savePanel);

    SceneLoadPanel* loadPanel = new SceneLoadPanel("Load Panel");
    mListUI.push_back(loadPanel);
    mainMenuBar->setSceneLoadPanel(loadPanel);
}

UIManager::~UIManager() {
    delete instance;
}