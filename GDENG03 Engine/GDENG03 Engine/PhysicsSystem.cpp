#include"PhysicsSystem.h"
#include"PhysicsComponent.h"
#include"TimeManager.h"
#include<iostream>
#include"AGameObject.h"

PhysicsSystem::PhysicsSystem() {
	mPhysicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -9.8, 0);
	mPhysicsWorld = mPhysicsCommon->createPhysicsWorld(settings);

	std::cout << "Physics System initialized!" << std::endl;
}

PhysicsSystem::~PhysicsSystem() {
	while (!mComponentList.empty()) {
		unregisterComponent(mComponentList[0]);
	}

	delete mPhysicsCommon;
	std::cout << "Physics System destroyed!" << std::endl;
}

void PhysicsSystem::registerComponent(PhysicsComponent* physics_component) {
	mComponentList.push_back(physics_component);
	mComponentTable[physics_component->getComponentName()] = physics_component;
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* physics_component) {
	std::string key = physics_component->getComponentName();
	mComponentTable.erase(key);
	mComponentList.erase(std::remove(mComponentList.begin(), mComponentList.end(), physics_component), mComponentList.end());
	mComponentList.shrink_to_fit();

	physics_component->getOwner()->detachComponent(physics_component);
}

void PhysicsSystem::unregisterComponentByName(std::string name) {
	PhysicsComponent* component = mComponentTable[name];
	if (component) unregisterComponent(component);
}

PhysicsComponent* PhysicsSystem::findComponentByName(std::string name) {
	return mComponentTable[name];
}

std::vector<PhysicsComponent*> PhysicsSystem::getAllComponents() {
	return mComponentList;
}

void PhysicsSystem::update() {
	if (TimeManager::getDeltaTime() > 0.f) {
		mPhysicsWorld->update(TimeManager::getDeltaTime());
		for (int i = 0; i < mComponentList.size(); i++) {
			mComponentList[i]->perform(TimeManager::getDeltaTime());
		}
	}
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld() {
	return mPhysicsWorld;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon() {
	return mPhysicsCommon;
}