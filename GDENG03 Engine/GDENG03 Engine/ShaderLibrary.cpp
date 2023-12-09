#include "ShaderLibrary.h"
#include "AGraphicsEngine.h"
#include "AVertexShader.h"
#include "APixelShader.h"

ShaderLibrary* ShaderLibrary::sharedInstance = NULL;

ShaderLibrary* ShaderLibrary::getInstance()
{
	return sharedInstance;
}

void ShaderLibrary::initialize()
{
	sharedInstance = new ShaderLibrary();
}

void ShaderLibrary::destroy()
{
	delete sharedInstance;
}

void ShaderLibrary::requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{
	AGraphicsEngine* graphEngine = AGraphicsEngine::getInstance();
	graphEngine->compileVertexShader(vertexShaderName.c_str(), "main", shaderByteCode, sizeShader);
}

AVertexShader* ShaderLibrary::getVertexShader(String vertexShaderName)
{
	if (this->activeVertexShaders[vertexShaderName] == NULL) {
		std::cout << "Vertex shader " << vertexShaderName.c_str() << " not found. Have you initialized it? \n";
	}
	return this->activeVertexShaders[vertexShaderName];
}

APixelShader* ShaderLibrary::getPixelShader(String pixelShaderName)
{
	if (this->activePixelShaders[pixelShaderName] == NULL) {
		std::cout << "Pixel shader " << pixelShaderName.c_str() << " not found. Have you initialized it? \n";
	}
	return this->activePixelShaders[pixelShaderName];
}

ShaderLibrary::ShaderLibrary()
{
	//initialize and load all shaders for use
	AGraphicsEngine* graphEngine = AGraphicsEngine::getInstance();

	ShaderNames shaderNames;
	ShaderData shaderData;

	graphEngine->compileVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME] = graphEngine->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);
	//graphEngine->releaseCompiledVertexShader();

	graphEngine->compilePixelShader(shaderNames.BASE_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME] = graphEngine->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);
	//graphEngine->releaseCompiledVertexShader();

	graphEngine->compileVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.TEXTURED_VERTEX_SHADER_NAME] = graphEngine->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);
	//graphEngine->releaseCompiledVertexShader();

	graphEngine->compilePixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.TEXTURED_PIXEL_SHADER_NAME] = graphEngine->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);
	//graphEngine->releaseCompiledVertexShader();

	std::cout << "Shader library initialized. \n";
}

ShaderLibrary::~ShaderLibrary()
{
	ShaderNames shaderNames;
	this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME]->release();
	this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME]->release();

	for (auto& vs : this->activeVertexShaders)
		vs.second->release();

	for (auto& ps : this->activePixelShaders)
		ps.second->release();

	this->activeVertexShaders.clear();
	this->activePixelShaders.clear();
}