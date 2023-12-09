#pragma once
#include"AGameObject.h"
#include"AVertexBuffer.h"
#include"AIndexBuffer.h"
#include"AConstantBuffer.h"
#include"Matrix4x4.h"
#include "TexturedVertexBuffer.h"

#include "Texture.h"
#include "ObjectRenderer.h"

class TexturedCube : public AGameObject
{
public:
	TexturedCube(std::string name);
	~TexturedCube();

	void update(float delta_time) override;
	void draw(int width, int height) override;

	void attachRenderer(ObjectRenderer* renderer);
	ObjectRenderer* getRenderer() const;

protected:
	//AVertexBuffer* mVertexBuffer;
	AIndexBuffer* mIndexBuffer;
	AConstantBuffer* mConstantBuffer;
	TexturedVertexBuffer* texVertexBuffer;
	AVertexBuffer* mVertexBuffer;

	ObjectRenderer* renderer;

	float mDeltaTime = 0.f;
	float mElapsedTime = 0.f;
};
