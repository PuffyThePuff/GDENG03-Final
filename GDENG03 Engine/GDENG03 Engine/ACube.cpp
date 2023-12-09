#include"ACube.h"
#include"AGraphicsEngine.h"
#include"SceneCameraManager.h"
#include"ADeviceContext.h"
#include<iostream>
#include"GlobalProperties.h"

ACube::ACube(std::string name) : AGameObject::AGameObject(name, CUBE) {
	void* shaderByteCode = nullptr;
	size_t shaderSize;
	AGraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);

	Vertex* currentVertexList = new Vertex[8];

	currentVertexList[0] = Vertex(
		Vector3D(-0.5f, -0.5f, -0.5f),
		Vector3D(1.f, 0.f, 0.f),
		Vector3D(0.2f, 0.f, 0.f)
	);
	currentVertexList[1] = Vertex(
		Vector3D(-0.5f, 0.5f, -0.5f),
		Vector3D(0.f, 1.f, 0.f),
		Vector3D(0.f, 0.2f, 0.f)
	);
	currentVertexList[2] = Vertex(
		Vector3D(0.5f, 0.5f, -0.5f),
		Vector3D(0.f, 1.f, 0.f),
		Vector3D(0.f, 0.2f, 0.f)
	);
	currentVertexList[3] = Vertex(
		Vector3D(0.5f, -0.5f, -0.5f),
		Vector3D(1.f, 0.f, 0.f),
		Vector3D(0.2f, 0.f, 0.f)
	);
	currentVertexList[4] = Vertex(
		Vector3D(0.5f, -0.5f, 0.5f),
		Vector3D(0.f, 0.f, 1.f),
		Vector3D(0.f, 0.f, 0.2f)
	);
	currentVertexList[5] = Vertex(
		Vector3D(0.5f, 0.5f, 0.5f),
		Vector3D(1.f, 1.f, 0.f),
		Vector3D(0.2f, 0.2f, 0.f)
	);
	currentVertexList[6] = Vertex(
		Vector3D(-0.5f, 0.5f, 0.5f),
		Vector3D(1.f, 1.f, 0.f),
		Vector3D(0.2f, 0.2f, 0.f)
	);
	currentVertexList[7] = Vertex(
		Vector3D(-0.5f, -0.5f, 0.5f),
		Vector3D(0.f, 0.f, 1.f),
		Vector3D(0.f, 0.f, 0.2f)
	);

	mVertexBuffer = AGraphicsEngine::getInstance()->createVertexBuffer();
	mVertexBuffer->load(currentVertexList, sizeof(Vertex), 8, shaderByteCode, shaderSize);

	unsigned int indexList[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		1, 6, 5,
		5, 2, 1,
		7, 0, 3,
		3, 4, 7,
		3, 2, 5,
		5, 4, 3,
		7, 6, 1,
		1, 0, 7
	};

	mIndexBuffer = AGraphicsEngine::getInstance()->createIndexBuffer();
	mIndexBuffer->load(indexList, ARRAYSIZE(indexList));

	constant datablock;
	datablock.coefficient = 0.f; 

	mConstantBuffer = AGraphicsEngine::getInstance()->createConstantBuffer();
	mConstantBuffer->load(&datablock, sizeof(constant));

	this->mVertexShader = AGraphicsEngine::getInstance()->createVertexShader(shaderByteCode, shaderSize);
	AGraphicsEngine::getInstance()->releaseCompiledVertexShader();

	AGraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &shaderSize);
	this->mPixelShader = AGraphicsEngine::getInstance()->createPixelShader(shaderByteCode, shaderSize);
	AGraphicsEngine::getInstance()->releaseCompiledPixelShader();

	delete[] currentVertexList;
}

ACube::~ACube() {
	mVertexBuffer->release();
	mIndexBuffer->release();
	mConstantBuffer->release();
}

void ACube::update(float delta_time) {
	AGameObject::update(delta_time);
}

void ACube::draw(int width, int height) {
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
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(mIndexBuffer);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(mIndexBuffer->getIndexCount(), 0, 0);
}