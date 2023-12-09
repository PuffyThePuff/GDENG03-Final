#include"TexturedCube.h"
#include"AGraphicsEngine.h"
#include"SceneCameraManager.h"
#include"ADeviceContext.h"
#include<iostream>
#include"GlobalProperties.h"
#include "ShaderLibrary.h"
#include "Vector2D.h"
#include "TextureManager.h"

struct TextureVertex
{
	Vector3D position;
	Vector2D texcoord;
};


TexturedCube::TexturedCube(std::string name) : AGameObject::AGameObject(name, TEXTURED_CUBE) {
	

	renderer = new ObjectRenderer();
	

	ShaderNames shaderNames;
	void* shaderByteCode = nullptr;
	size_t shaderSize;

	AGraphicsEngine::getInstance()->compileVertexShader(L"TextureVertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);
	//ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.TEXTURED_VERTEX_SHADER_NAME, &shaderByteCode, &shaderSize);

	Vector3D position_list[] =
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};

	TextureVertex quadList[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] },


		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },


		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }

	};

	this->texVertexBuffer = AGraphicsEngine::getInstance()->createTexturedVertexBuffer();
	this->texVertexBuffer->load(quadList, sizeof(TextureVertex), ARRAYSIZE(quadList), shaderByteCode, shaderSize);


	unsigned int indexList[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	this->mIndexBuffer = AGraphicsEngine::getInstance()->createIndexBuffer();
	this->mIndexBuffer->load(indexList, ARRAYSIZE(indexList));

	constant datablock;
	datablock.coefficient = 0.f;
	mConstantBuffer = AGraphicsEngine::getInstance()->createConstantBuffer();
	mConstantBuffer->load(&datablock, sizeof(constant));


	//ADeviceContext* deviceContext = AGraphicsEngine::getInstance()->getImmediateDeviceContext();
	//deviceContext->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME),ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));

	///*
	this->mVertexShader = AGraphicsEngine::getInstance()->createVertexShader(shaderByteCode, shaderSize);
	AGraphicsEngine::getInstance()->releaseCompiledVertexShader();

	AGraphicsEngine::getInstance()->compilePixelShader(L"TexturePixelShader.hlsl", "psmain", &shaderByteCode, &shaderSize);
	this->mPixelShader = AGraphicsEngine::getInstance()->createPixelShader(shaderByteCode, shaderSize);
	AGraphicsEngine::getInstance()->releaseCompiledPixelShader();
	//*/
}

TexturedCube::~TexturedCube() {
	mVertexBuffer->release();
	mIndexBuffer->release();
	mConstantBuffer->release();
}

void TexturedCube::update(float delta_time) {
	AGameObject::update(delta_time);
}

void TexturedCube::draw(int width, int height) {

	
	

	constant shaderNumbers;

	if (this->findComponentOfType(AComponent::PHYSICS)) {
		shaderNumbers.worldMatrix = this->getPhysicsMatrix();
	}

	else shaderNumbers.worldMatrix = this->getLocalMatrix();

	shaderNumbers.viewMatrix = SceneCameraManager::getInstance()->getSceneCameraViewMatrix();
	shaderNumbers.projectionMatrix = SceneCameraManager::getInstance()->getSceneCameraProjectionMatrix();
	shaderNumbers.coefficient = 0.5f * (sin(mElapsedTime) + 1.f);

	mConstantBuffer->update(AGraphicsEngine::getInstance()->getImmediateDeviceContext(), &shaderNumbers);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, this->mVertexShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, this->mPixelShader);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(this->mVertexShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(this->mPixelShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setTexture(renderer->getTexture());

	/*
	ShaderNames shaderNames;
	ADeviceContext* deviceContext = AGraphicsEngine::getInstance()->getImmediateDeviceContext();
	deviceContext->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME), ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));
	*/

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(texVertexBuffer);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(mIndexBuffer);


	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(mIndexBuffer->getIndexCount(), 0, 0);

}

ObjectRenderer* TexturedCube::getRenderer() const
{
	return this->renderer;
}
