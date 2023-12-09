#pragma once
#include"AUIPanel.h"

class EngineProfiler : public AUIPanel
{
public:
	EngineProfiler(std::string name);
	~EngineProfiler();

	void draw() override;

private:
	float mElapsedTime = 0.f;
	float mTimeSinceLastCalc = 0.f;
	float mAverageDeltaTime = 0.f;
	float mFramesPerSecond = 0.f;
	float mFramesSinceLastCalc = 0.f;
};