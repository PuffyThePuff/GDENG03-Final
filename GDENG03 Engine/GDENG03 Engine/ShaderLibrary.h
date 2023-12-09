#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

class AVertexShader;
class APixelShader;

class ShaderNames {
public:
	typedef std::wstring String;
	//vertex shader names
	const String BASE_VERTEX_SHADER_NAME = L"VertexShader.hlsl";
	const String TEXTURED_VERTEX_SHADER_NAME = L"TextureVertexShader.hlsl";

	//pixel shader names
	const String BASE_PIXEL_SHADER_NAME = L"PixelShader.hlsl";
	const String TEXTURED_PIXEL_SHADER_NAME = L"TexturePixelShader.hlsl";
};

class ShaderLibrary
{
public:
	class ShaderData {
	public:
		void* shaderByteCode = NULL;
		size_t sizeShader = 0;
	};

	typedef std::wstring String;
	typedef std::unordered_map<String, AVertexShader*> VertexShaderTable;
	typedef std::unordered_map<String, APixelShader*> PixelShaderTable;

	static ShaderLibrary* getInstance();
	static void initialize();
	static void destroy();

	void requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader); //since shader byte code gets dereferenced for some reason if stored in a hash table. request manually.
	AVertexShader* getVertexShader(String vertexShaderName);
	APixelShader* getPixelShader(String pixelShaderName);

private:
	ShaderLibrary();
	~ShaderLibrary();
	ShaderLibrary(ShaderLibrary const&) {};             // copy constructor is private
	ShaderLibrary& operator=(ShaderLibrary const&) {};  // assignment operator is private*/
	static ShaderLibrary* sharedInstance;

	VertexShaderTable activeVertexShaders;
	PixelShaderTable activePixelShaders;
};