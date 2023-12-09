#pragma once
#include<string>

class PhysicsSystem;

class SystemManager
{
public:
	static SystemManager* getInstance();
	static void initialize();
	static void destroy();

	void update();
	PhysicsSystem* getPhysicsSystem();

private:
	SystemManager();
	~SystemManager();
	SystemManager(SystemManager const&) {};
	SystemManager& operator =(SystemManager const&) {};
	static SystemManager* instance;

	PhysicsSystem* mPhysicsSystem;
};