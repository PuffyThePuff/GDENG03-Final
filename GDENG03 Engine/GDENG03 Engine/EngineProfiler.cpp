#include"EngineProfiler.h"
#include"TimeManager.h"
#include"GlobalProperties.h"
#include<string>

EngineProfiler::EngineProfiler(std::string name) : AUIPanel::AUIPanel(name) {}

EngineProfiler::~EngineProfiler() {}

void EngineProfiler::draw() {
	mFramesSinceLastCalc += 1.f;
	mTimeSinceLastCalc += TimeManager::getDeltaTime();
	mElapsedTime += TimeManager::getDeltaTime();
	if (mTimeSinceLastCalc >= 1.f) {
		mAverageDeltaTime = mTimeSinceLastCalc / mFramesSinceLastCalc;
		mFramesPerSecond = 1.f / mAverageDeltaTime;
		mFramesSinceLastCalc = 0.f;
		mTimeSinceLastCalc = 0.f;
	}

	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;
	ImGui::Begin("GDENG03 Engine Profiler", NULL, windowFlags);
	ImGui::SetWindowSize(ImVec2(400, 150));
	ImGui::SetWindowPos(ImVec2(50, GlobalProperties::WINDOW_HEIGHT - 214));
	ImGui::Text("Average time per frame: ");
	ImGui::SameLine();
	ImGui::Text(std::to_string(mAverageDeltaTime * 1000.f).c_str());
	ImGui::SameLine();
	ImGui::Text(" ms");

	ImGui::Text("Frames per second: ");
	ImGui::SameLine();
	ImGui::Text(std::to_string(mFramesPerSecond).c_str());

	ImGui::Text("Seconds since execution: ");
	ImGui::SameLine();
	ImGui::Text(std::to_string(mElapsedTime).c_str());

	ImGui::End();
}