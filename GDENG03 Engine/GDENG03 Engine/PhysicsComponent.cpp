#include"PhysicsComponent.h"
#include"SystemManager.h"
#include"PhysicsSystem.h"
#include"AGameObject.h"
#include"Vector3D.h"
#include<iostream>

PhysicsComponent::PhysicsComponent(std::string name) : AComponent::AComponent(name, PHYSICS) {
	PhysicsSystem* physicsSystem = SystemManager::getInstance()->getPhysicsSystem();
	physicsSystem->registerComponent(this);
	std::cout << this->getComponentName() << " registered." << std::endl;

	mRigidBody = nullptr;
}

PhysicsComponent::~PhysicsComponent() {
	SystemManager::getInstance()->getPhysicsSystem()->unregisterComponent(this);
	AComponent::~AComponent();
}

void PhysicsComponent::attachOwner(AGameObject* owner) {
	AComponent::attachOwner(owner);

	PhysicsSystem* physicsSystem = SystemManager::getInstance()->getPhysicsSystem();

	reactphysics3d::PhysicsCommon* physicsCommon = physicsSystem->getPhysicsCommon();
	reactphysics3d::PhysicsWorld* physicsWorld = physicsSystem->getPhysicsWorld();

	Vector3D position = this->getOwner()->getLocalPosition();
	Vector3D rotation = this->getOwner()->getLocalRotation();
	Vector3D scale = this->getOwner()->getLocalScale();

	reactphysics3d::Transform transform;
	transform.setPosition(Vector3(position.x, position.y, position.z));
	transform.setOrientation(Quaternion::fromEulerAngles(rotation.x, rotation.y, rotation.z));
	mRigidBody = physicsWorld->createRigidBody(transform);

	reactphysics3d::BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.x / 2.f, scale.y / 2.f, scale.z / 2.f));
	mRigidBody->addCollider(boxShape, Transform::identity());

	mRigidBody->updateMassPropertiesFromColliders();
	mRigidBody->setMass(mMass);
	mRigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
	mRigidBody->setLinearDamping(0.01);
	mRigidBody->setAngularDamping(0.01);

	transform = mRigidBody->getTransform();

	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->updatePhysicsMatrix(matrix);
}

void PhysicsComponent::perform(float delta_time) {
	const Transform transform = mRigidBody->getTransform();
	float physicsMatrix[16];
	transform.getOpenGLMatrix(physicsMatrix);

	this->getOwner()->updatePhysicsMatrix(physicsMatrix);
}

void PhysicsComponent::reset(Vector3D position, Vector3D rotation) {
	mRigidBody->setLinearVelocity(Vector3::zero());
	mRigidBody->setAngularVelocity(Vector3::zero());

	Transform transform;
	transform.setPosition(Vector3(position.x, position.y, position.z));
	transform.setOrientation(Quaternion::fromEulerAngles(rotation.x, rotation.y, rotation.z));
	mRigidBody->setTransform(transform);

	transform = mRigidBody->getTransform();
	float physicsMatrix[16];
	transform.getOpenGLMatrix(physicsMatrix);
	this->getOwner()->updatePhysicsMatrix(physicsMatrix);
}

RigidBody* PhysicsComponent::getRigidBody() {
	return mRigidBody;
}

bool PhysicsComponent::isActive() {
	return mRigidBody->isActive();
}

bool PhysicsComponent::isStatic() {
	if (mRigidBody->getType() == BodyType::DYNAMIC) return false;
	else return true;
}

bool PhysicsComponent::isGravityEnabled() {
	return mRigidBody->isGravityEnabled();
}

float PhysicsComponent::getMass() {
	return mRigidBody->getMass();
}

void PhysicsComponent::setActive(bool is_active) {
	mRigidBody->setIsActive(is_active);
}

void PhysicsComponent::setStatic(bool is_static) {
	if (is_static) mRigidBody->setType(BodyType::STATIC);
	else mRigidBody->setType(BodyType::DYNAMIC);
}

void PhysicsComponent::enableGravity(bool is_enabled) {
	mRigidBody->enableGravity(is_enabled);
}

void PhysicsComponent::setMass(float object_mass) {
	mMass = object_mass;
	mRigidBody->setMass(mMass);
}

void PhysicsComponent::setPosition(Vector3D new_position) {
	Transform transform = mRigidBody->getTransform();
	transform.setPosition(Vector3(new_position.x, new_position.y, new_position.z));
	mRigidBody->setTransform(transform);

	transform = mRigidBody->getTransform();
	float physicsMatrix[16];
	transform.getOpenGLMatrix(physicsMatrix);
	this->getOwner()->updatePhysicsMatrix(physicsMatrix);
}

void PhysicsComponent::setRotation(Vector3D new_rotation) {
	Transform transform = mRigidBody->getTransform();
	transform.setOrientation(Quaternion::fromEulerAngles(new_rotation.x, new_rotation.y, new_rotation.z));
	mRigidBody->setTransform(transform);

	transform = mRigidBody->getTransform();
	float physicsMatrix[16];
	transform.getOpenGLMatrix(physicsMatrix);
	this->getOwner()->updatePhysicsMatrix(physicsMatrix);
}

void PhysicsComponent::setScale(Vector3D new_scale) {
	mRigidBody->removeCollider(mRigidBody->getCollider(0));

	BoxShape* boxShape = SystemManager::getInstance()->getPhysicsSystem()->getPhysicsCommon()->createBoxShape(Vector3(new_scale.x / 2.f, new_scale.y / 2.f, new_scale.z / 2.f));
	mRigidBody->addCollider(boxShape, Transform::identity());
}

void PhysicsComponent::applyForce(float x, float y, float z) {
	mRigidBody->applyWorldForceAtCenterOfMass(Vector3(x, y, z));
}