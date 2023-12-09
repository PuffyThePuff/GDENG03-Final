#pragma once
#include <string>
#include <vector>
#include "Vector3D.h"

class UnityGameObject
{
public:
	UnityGameObject();
	~UnityGameObject();

	void addLine(std::string gameObjectInfo);
	void parseInfo();

	long long getObjectID();
	long long getObjectType();
	std::string getGameObjectName();
	int getGameObjectType();
	bool getActive();

	Vector3D getPosition();
	Vector3D getRotation();
	Vector3D getScale();

	std::vector<long long> getComponentList();
	long long int getOwnerID();

	float getMass();
	bool getGravityActive();
	bool getStatic();

private:
	std::vector<std::string> objectInfo;

	long long objectUnityClass;
	long long objectUnityId;

	std::string objectName;
	int objectType;
	bool isActive;

	Vector3D localPos;
	Vector3D localRot;
	Vector3D localScale;

	std::vector<long long> componentList;
	long long ownerId;

	bool isGravityActive;
	bool isStatic;
	float mass;
};