#include"SystemManager.h"
#include"PhysicsSystem.h"

SystemManager* SystemManager::instance = nullptr;

SystemManager* SystemManager::getInstance() {
	return instance;
}

void SystemManager::initialize() {
	instance = new SystemManager();
}

void SystemManager::destroy() {
	delete instance->mPhysicsSystem;
}

void SystemManager::update() {
	mPhysicsSystem->update();
}

PhysicsSystem* SystemManager::getPhysicsSystem() {
	return mPhysicsSystem;
}

SystemManager::SystemManager() {
	mPhysicsSystem = new PhysicsSystem();
}

SystemManager::~SystemManager() {
	delete instance;
}