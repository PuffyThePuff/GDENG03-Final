#include"AComponent.h"

AComponent::AComponent(std::string component_name, ComponentType component_type) {
	mComponentName = component_name;
	mType = component_type;
	mOwner = NULL;
}

AComponent::~AComponent() {
	mOwner = NULL;
	mType = NOT_SET;
}

void AComponent::attachOwner(AGameObject* owner) {
	mOwner = owner;
}

void AComponent::detachOwner() {
	delete this;
}

AGameObject* AComponent::getOwner() {
	return mOwner;
}

AComponent::ComponentType AComponent::getComponentType() {
	return mType;
}

std::string AComponent::getComponentName() {
	return mComponentName;
}