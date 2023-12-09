#include "TextureManager.h"
#include "Texture.h"


#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#if __cplusplus >= 201703L
#include <filesystem>
#endif

TextureManager* TextureManager::sharedInstance = NULL;

void TextureManager::initialize()
{
	sharedInstance = new TextureManager();
}

void TextureManager::destroy()
{
	delete sharedInstance;
}

TextureManager* TextureManager::getInstance()
{
	return sharedInstance;
}

Texture* TextureManager::createTextureFromFile(const wchar_t* filePath)
{
	std::wstring full_path = std::experimental::filesystem::absolute(filePath);

	if (this->resourceMap[full_path] == NULL) {
		std::cout << " null .." << std::endl;
		this->resourceMap[full_path] = this->convertToResource(filePath);
	}

	return (Texture*)this->resourceMap[full_path];
}

TextureManager::TextureManager() :AResourceManager()
{

}

TextureManager::~TextureManager()
{
	AResourceManager::~AResourceManager();
}

Resource* TextureManager::convertToResource(const wchar_t* filePath)
{
	Texture* tex = NULL;
	try
	{
		tex = new Texture(filePath);
	}
	catch (...)
	{

	}

	return (Resource*)tex;
}