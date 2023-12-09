#pragma once
#include <string>

#include "Texture.h"

class ObjectRenderer
{
protected:
	typedef std::string String;

public:
	ObjectRenderer();
	~ObjectRenderer();

	void setMaterialPath(String path);
	String getMaterialPath();
	Texture* getTexture();

private:
	String materialPath;
	Texture* texture = nullptr;
};

