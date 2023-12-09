#pragma once
#include<unordered_map>
#include<vector>
#include"SystemManager.h"
#include<reactphysics3d/reactphysics3d.h>

class PhysicsComponent;

using namespace reactphysics3d;

class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void registerComponent(PhysicsComponent* physics_component);
	void unregisterComponent(PhysicsComponent* physics_component);
	void unregisterComponentByName(std::string name);
	PhysicsComponent* findComponentByName(std::string name);
	std::vector<PhysicsComponent*> getAllComponents();

	void update();
	PhysicsWorld* getPhysicsWorld();
	PhysicsCommon* getPhysicsCommon();

private:
	std::unordered_map<std::string, PhysicsComponent*> mComponentTable;
	std::vector<PhysicsComponent*> mComponentList;

	PhysicsCommon* mPhysicsCommon;
	PhysicsWorld* mPhysicsWorld;
};