#pragma once
#include"AUIPanel.h"

class SimpleWindowPanel : public AUIPanel
{
public:
	SimpleWindowPanel(std::string name);
	~SimpleWindowPanel() {};

	void draw() override;

private:
	bool mIsDemoWindowOpen = false;
	float mBackgroundColor[3];
};