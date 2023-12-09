#pragma once
#include"AComponent.h"
#include"Vector3D.h"
#include<reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent : public AComponent
{
public:
	PhysicsComponent(std::string name);
	~PhysicsComponent();

	virtual void attachOwner(AGameObject* owner) override;
	void perform(float delta_time) override;
	void reset(Vector3D position, Vector3D rotation);

	RigidBody* getRigidBody();
	
	bool isActive();
	bool isStatic();
	bool isGravityEnabled();
	float getMass();
	
	void setActive(bool is_active);
	void setStatic(bool is_static);
	void enableGravity(bool is_enabled);
	void setMass(float object_mass);
	
	void setPosition(Vector3D new_position);
	void setRotation(Vector3D new_rotation);
	void setScale(Vector3D new_scale);

	void applyForce(float x, float y, float z);

private:
	RigidBody* mRigidBody;

	float mMass = 1.f;
};