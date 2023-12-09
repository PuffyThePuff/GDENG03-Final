#include"StateSnapshot.h"
#include"AGameObject.h"

StateSnapshot::StateSnapshot(AGameObject* affected_object) {
	mObject = affected_object;
	mObjectName = affected_object->getObjectName();
	mIsEnabled = affected_object->isActive();
	mLocalPosition = affected_object->getLocalPosition();
	mLocalRotation = affected_object->getLocalRotation();
	mLocalScale = affected_object->getLocalScale();
}

StateSnapshot::~StateSnapshot() {}

AGameObject* StateSnapshot::getObject() {
	return mObject;
}

std::string StateSnapshot::getObjectName() {
	return mObjectName;
}

bool StateSnapshot::getEnabledState() {
	return mIsEnabled;
}

Vector3D StateSnapshot::getStoredPosition() {
	return mLocalPosition;
}

Vector3D StateSnapshot::getStoredRotation() {
	return mLocalRotation;
}

Vector3D StateSnapshot::getStoredScale() {
	return mLocalScale;
}