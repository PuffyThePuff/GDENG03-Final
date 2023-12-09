#pragma once
#include"Vector3D.h"
#include<string>

class AGameObject;

class StateSnapshot
{
public:
	StateSnapshot(AGameObject* affected_object);
	~StateSnapshot();

	AGameObject* getObject();
	std::string getObjectName();
	bool getEnabledState();
	Vector3D getStoredPosition();
	Vector3D getStoredRotation();
	Vector3D getStoredScale();

private:
	AGameObject* mObject;
	std::string mObjectName;
	bool mIsEnabled;
	Vector3D mLocalPosition;
	Vector3D mLocalRotation;
	Vector3D mLocalScale;
};