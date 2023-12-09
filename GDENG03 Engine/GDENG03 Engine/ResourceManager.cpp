#include "ResourceManager.h"
#include <filesystem>
#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#if __cplusplus >= 201703L
#include <filesystem>
#endif

AResourceManager::AResourceManager()
{
}

AResourceManager::~AResourceManager()
{
    if (this->resourceMap.size() != 0) {
        this->resourceMap.clear();
    }
}