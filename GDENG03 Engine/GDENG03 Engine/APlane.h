#pragma once
#include"AGameObject.h"
#include"AVertexBuffer.h"
#include"AConstantBuffer.h"

class APlane : public AGameObject
{
public:
	APlane(std::string name);
	~APlane();

	void update(float delta_time) override;
	void draw(int width, int height) override;

private:
	AVertexBuffer* mVertexBuffer;
	AConstantBuffer* mConstantBuffer;
};