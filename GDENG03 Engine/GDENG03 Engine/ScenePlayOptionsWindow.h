#pragma once
#include "AUIPanel.h"

class ScenePlayOptionsWindow : public AUIPanel
{
public:
	ScenePlayOptionsWindow(std::string name);
	~ScenePlayOptionsWindow();

	void draw() override;
};