#pragma once
#include<string>
#include"imgui.h"

class UIManager;

class AUIPanel
{

protected:
	AUIPanel(std::string name);
	~AUIPanel() {};

	std::string getName();
	virtual void draw() = 0;

	std::string mPanelName;
	bool mIsEnabled = true;

	friend class UIManager;
};