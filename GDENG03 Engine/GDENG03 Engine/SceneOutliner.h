#pragma once
#include"AUIPanel.h"
#include"AGameObject.h"

class SceneOutliner : public AUIPanel
{
public:
	SceneOutliner(std::string name);
	~SceneOutliner();

	void draw() override;
};