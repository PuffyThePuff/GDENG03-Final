#include "ObjectRenderer.h"

#include "TextureManager.h"

ObjectRenderer::ObjectRenderer()
{
	setMaterialPath("Assets\\Textures\\default.jpg");
}

ObjectRenderer::~ObjectRenderer()
{
}

void ObjectRenderer::setMaterialPath(String path)
{
	materialPath = path;

	std::wstring widestr = std::wstring(materialPath.begin(), materialPath.end());
	const wchar_t* texturePath = widestr.c_str();

	this->texture = TextureManager::getInstance()->createTextureFromFile(texturePath);
}

ObjectRenderer::String ObjectRenderer::getMaterialPath()
{
	return this->materialPath;
}

Texture* ObjectRenderer::getTexture()
{
	return this->texture;
}
