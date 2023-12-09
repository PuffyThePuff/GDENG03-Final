#pragma once
#include<string>

class AGameObject;

class AComponent
{
public:
	enum ComponentType {
		NOT_SET = -1,
		SCRIPT = 0,
		RENDERER = 1,
		INPUT = 2,
		PHYSICS = 3
	};

	AComponent(std::string component_name, ComponentType component_type);
	~AComponent();

	virtual void attachOwner(AGameObject* owner);
	void detachOwner();
	AGameObject* getOwner();
	ComponentType getComponentType();
	std::string getComponentName();

	virtual void perform(float delta_time) = 0;

protected:
	AGameObject* mOwner;
	ComponentType mType;
	std::string mComponentName;
};