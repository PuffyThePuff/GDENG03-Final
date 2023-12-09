#include"APlane.h"
#include"AGraphicsEngine.h"
#include"InputManager.h"
#include"SceneCameraManager.h"
#include"ADeviceContext.h"
#include<iostream>

APlane::APlane(std::string name) : AGameObject::AGameObject(name, PLANE) {
	void* shaderByteCode = nullptr;
	size_t shaderSize;
	AGraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);

	Vertex* currentVertexList = new Vertex[4];

	currentVertexList[0] = Vertex(
		Vector3D(-0.5f, 0.f, 0.5f),
		Vector3D(1.f, 0.f, 0.f),
		Vector3D(0.2f, 0.f, 0.f)
	);
	currentVertexList[1] = Vertex(
		Vector3D(0.5f, 0.f, 0.5f),
		Vector3D(0.f, 1.f, 0.f),
		Vector3D(0.f, 0.2f, 0.f)
	);
	currentVertexList[2] = Vertex(
		Vector3D(-0.5f, 0.f, -0.5f),
		Vector3D(0.f, 0.f, 1.f),
		Vector3D(0.f, 0.f, 0.2f)
	);
	currentVertexList[3] = Vertex(
		Vector3D(0.5f, 0.f, -0.5f),
		Vector3D(1.f, 1.f, 0.f),
		Vector3D(0.2f, 0.2f, 0.f)
	);

	mVertexBuffer = AGraphicsEngine::getInstance()->createVertexBuffer();
	mVertexBuffer->load(currentVertexList, sizeof(Vertex), 4, shaderByteCode, shaderSize);

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

APlane::~APlane() {
	mVertexBuffer->release();
	mConstantBuffer->release();
}

void APlane::update(float delta_time) {
	AGameObject::update(delta_time);
}

void APlane::draw(int width, int height) {
	constant shaderNumbers;

	if (this->findComponentOfType(AComponent::PHYSICS)) {
		shaderNumbers.worldMatrix = this->getPhysicsMatrix();
	}
		
	else shaderNumbers.worldMatrix = this->getLocalMatrix();

	shaderNumbers.viewMatrix = SceneCameraManager::getInstance()->getSceneCameraViewMatrix();
	shaderNumbers.projectionMatrix = SceneCameraManager::getInstance()->getSceneCameraProjectionMatrix();
	shaderNumbers.coefficient = 0.f;

	mConstantBuffer->update(AGraphicsEngine::getInstance()->getImmediateDeviceContext(), &shaderNumbers);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, this->mVertexShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, this->mPixelShader);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(this->mVertexShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(this->mPixelShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(mVertexBuffer->getVertexCount(), 0);
}