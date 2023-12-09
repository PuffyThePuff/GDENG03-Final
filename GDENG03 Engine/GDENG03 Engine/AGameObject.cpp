#include"AGameObject.h"
#include"InputManager.h"
#include"BackendManager.h"
#include"PhysicsComponent.h"
#include"SystemManager.h"
#include"PhysicsSystem.h"
#include"AVertexShader.h"
#include"APixelShader.h"
#include<Windows.h>

AGameObject::AGameObject(std::string name, ObjectType type) {
	mObjectName = name;
	mObjectType = type;

	mLocalPosition = Vector3D(0.f, 0.f, 0.f);
	mLocalRotation = Vector3D(0.f, 0.f, 0.f);
	mLocalScale = Vector3D(1.f, 1.f, 1.f);
	mLocalMatrix.setIdentity();
	mPhysicsMatrix.setIdentity();
}

AGameObject::~AGameObject() {
	for (int i = 0; i < mComponentList.size(); i++) {
		switch (mComponentList[i]->getComponentType()) {
		case AComponent::PHYSICS: {
			SystemManager::getInstance()->getPhysicsSystem()->unregisterComponent((PhysicsComponent*)mComponentList[i]);
		}
		break;
		default: {}
		}
	}

	if (mVertexShader) mVertexShader->release();
	if (mPixelShader) mPixelShader->release();
}

void AGameObject::update(float delta_time) {
	if (BackendManager::getInstance()->getEditorMode() == BackendManager::EDIT && this->mIsSelected) {
		if (InputManager::getInstance()->isKeyDown('R')) {
			if (InputManager::getInstance()->isKeyDown(VK_UP)) {
				float deltaRotation = mRotationSpeed * delta_time;
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(deltaRotation, deltaRotation, deltaRotation);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown(VK_DOWN)) {
				float deltaRotation = -mRotationSpeed * delta_time;
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(deltaRotation, deltaRotation, deltaRotation);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('I')) {
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(mRotationSpeed * delta_time, 0.f, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('K')) {
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(-mRotationSpeed * delta_time, 0.f, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('L')) {
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(0.f, -mRotationSpeed * delta_time, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('J')) {
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(0.f, mRotationSpeed * delta_time, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('O')) {
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(0.f, 0.f, -mRotationSpeed * delta_time);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('U')) {
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(0.f, 0.f, mRotationSpeed * delta_time);
				this->setRotation(newRotation);
			}
		}

		else if (InputManager::getInstance()->isKeyDown('T')) {
			float translationScalar = mTranslationSpeed * delta_time;

			if (InputManager::getInstance()->isKeyDown('I')) {
				Vector3D newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getUpVector() * translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('K')) {
				Vector3D newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getUpVector() * -translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('L')) {
				Vector3D newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getRightVector() * translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('J')) {
				Vector3D newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getRightVector() * -translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('U')) {
				Vector3D newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getForwardVector() * translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('M')) {
				Vector3D newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getForwardVector() * -translationScalar;
				this->setPosition(newPosition);
			}
		}

		else if (InputManager::getInstance()->isKeyDown('Y')) {
			if (InputManager::getInstance()->isKeyDown(VK_UP)) {
				float deltaScale = mScaleSpeed * delta_time;
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(deltaScale, deltaScale, deltaScale);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown(VK_DOWN)) {
				float deltaScale = -mScaleSpeed * delta_time;
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(deltaScale, deltaScale, deltaScale);
				if (newScale.x > 0.f && newScale.y > 0.f && newScale.z > 0.f) this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('I')) {
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(0.f, mScaleSpeed * delta_time, 0.f);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('K')) {
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(0.f, -mScaleSpeed * delta_time, 0.f);
				if (newScale.y > 0.f) this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('L')) {
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(mScaleSpeed * delta_time, 0.f, 0.f);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('J')) {
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(-mScaleSpeed * delta_time, 0.f, 0.f);
				if (newScale.x > 0.f) this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('U')) {
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(0.f, 0.f, mScaleSpeed * delta_time);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('M')) {
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(0.f, 0.f, -mScaleSpeed * delta_time);
				if (newScale.z > 0.f) this->setScale(newScale);
			}
		}
	}
}

std::string AGameObject::getObjectName() {
	return mObjectName;
}

AGameObject::ObjectType AGameObject::getObjectType() {
	return mObjectType;
}

bool AGameObject::isActive() {
	return mIsActive;
}

void AGameObject::setActive(bool is_object_active) {
	mIsActive = is_object_active;
}

void AGameObject::select() {
	mIsSelected = true;
}

void AGameObject::deselect() {
	mIsSelected = false;
}

void AGameObject::setTranslationSpeed(float translation_speed) {
	mTranslationSpeed = translation_speed;
}

void AGameObject::setRotationSpeed(float rotation_speed) {
	mRotationSpeed = rotation_speed;
}

void AGameObject::setScaleSpeed(float scale_speed) {
	mScaleSpeed = scale_speed;
}

void AGameObject::setPosition(float x, float y, float z) {
	mLocalPosition.x = x;
	mLocalPosition.y = y;
	mLocalPosition.z = z;

	updateLocalMatrix();

	AComponent* component = findComponentOfType(AComponent::PHYSICS);
	if (component) {
		PhysicsComponent* physics = (PhysicsComponent*)component;
		physics->setPosition(Vector3D(x, y, z));
	}
}

void AGameObject::setPosition(Vector3D position) {
	mLocalPosition = position;

	updateLocalMatrix();

	AComponent* component = findComponentOfType(AComponent::PHYSICS);
	if (component) {
		PhysicsComponent* physics = (PhysicsComponent*)component;
		physics->setPosition(position);
	}
}

Vector3D AGameObject::getLocalPosition() {
	return mLocalPosition;
}

void AGameObject::setScale(float x, float y, float z) {
	mLocalScale.x = x;
	mLocalScale.y = y;
	mLocalScale.z = z;

	updateLocalMatrix();

	AComponent* component = findComponentOfType(AComponent::PHYSICS);
	if (component) {
		PhysicsComponent* physics = (PhysicsComponent*)component;
		physics->setScale(Vector3D(x, y, z));
	}
}

void AGameObject::setScale(Vector3D scale) {
	mLocalScale = scale;

	updateLocalMatrix();

	AComponent* component = findComponentOfType(AComponent::PHYSICS);
	if (component) {
		PhysicsComponent* physics = (PhysicsComponent*)component;
		physics->setScale(scale);
	}
}

Vector3D AGameObject::getLocalScale() {
	return mLocalScale;
}

void AGameObject::setRotation(float x, float y, float z) {
	mLocalRotation.x = x;
	mLocalRotation.y = y;
	mLocalRotation.z = z;

	updateLocalMatrix();

	AComponent* component = findComponentOfType(AComponent::PHYSICS);
	if (component) {
		PhysicsComponent* physics = (PhysicsComponent*)component;
		physics->setRotation(Vector3D(x, y, z));
	}
}

void AGameObject::setRotation(Vector3D rotation) {
	mLocalRotation = rotation;

	updateLocalMatrix();

	AComponent* component = findComponentOfType(AComponent::PHYSICS);
	if (component) {
		PhysicsComponent* physics = (PhysicsComponent*)component;
		physics->setRotation(rotation);
	}
}

Vector3D AGameObject::getLocalRotation() {
	return mLocalRotation;
}

void AGameObject::updateLocalMatrix() {
	Matrix4x4 newLocalMatrix;
	newLocalMatrix.setIdentity();

	newLocalMatrix.scale(mLocalScale);
	newLocalMatrix.rotate(0, mLocalRotation.x);
	newLocalMatrix.rotate(1, mLocalRotation.y);
	newLocalMatrix.rotate(2, mLocalRotation.z);
	newLocalMatrix.translate(mLocalPosition);

	mLocalMatrix = newLocalMatrix;
}

void AGameObject::updatePhysicsMatrix(float physics_matrix[16]) {
	Matrix4x4 physicsMatrix;

	physicsMatrix.mMatrix[0][0] = physics_matrix[0];
	physicsMatrix.mMatrix[0][1] = physics_matrix[1];
	physicsMatrix.mMatrix[0][2] = physics_matrix[2];
	physicsMatrix.mMatrix[0][3] = physics_matrix[3];

	physicsMatrix.mMatrix[1][0] = physics_matrix[4];
	physicsMatrix.mMatrix[1][1] = physics_matrix[5];
	physicsMatrix.mMatrix[1][2] = physics_matrix[6];
	physicsMatrix.mMatrix[1][3] = physics_matrix[7];

	physicsMatrix.mMatrix[2][0] = physics_matrix[8];
	physicsMatrix.mMatrix[2][1] = physics_matrix[9];
	physicsMatrix.mMatrix[2][2] = physics_matrix[10];
	physicsMatrix.mMatrix[2][3] = physics_matrix[11];

	physicsMatrix.mMatrix[3][0] = physics_matrix[12];
	physicsMatrix.mMatrix[3][1] = physics_matrix[13];
	physicsMatrix.mMatrix[3][2] = physics_matrix[14];
	physicsMatrix.mMatrix[3][3] = physics_matrix[15];

	Matrix4x4 composedMatrix;
	composedMatrix.setIdentity();
	composedMatrix.scale(mLocalScale);
	composedMatrix *= physicsMatrix;

	mPhysicsMatrix = composedMatrix;
}

Matrix4x4 AGameObject::getLocalMatrix() {
	return mLocalMatrix;
}

Matrix4x4 AGameObject::getPhysicsMatrix() {
	return mPhysicsMatrix;
}

void AGameObject::saveInitialState() {
	if (mInitialState) {
		StateSnapshot* state = mInitialState;
		delete state;
	}

	StateSnapshot* newState = new StateSnapshot(this);
	mInitialState = newState;
}

void AGameObject::restoreInitialState() {
	setActive(mInitialState->getEnabledState());
	setScale(mInitialState->getStoredScale());
	setRotation(mInitialState->getStoredRotation());
	setPosition(mInitialState->getStoredPosition());

	AComponent* component = findComponentOfType(AComponent::PHYSICS);
	if (component) {
		PhysicsComponent* physics = (PhysicsComponent*)component;
		physics->reset(mInitialState->getStoredPosition(), mInitialState->getStoredRotation());
	}
}

void AGameObject::attachComponent(AComponent* new_component) {
	mComponentList.push_back(new_component);
	new_component->attachOwner(this);
}

void AGameObject::detachComponent(AComponent* component) {
	mComponentList.erase(std::remove(mComponentList.begin(), mComponentList.end(), component), mComponentList.end());
	mComponentList.shrink_to_fit();
	component->detachOwner();
}

AComponent* AGameObject::findComponentOfType(AComponent::ComponentType component_type) {
	for (int i = 0; i < mComponentList.size(); i++) {
		if (mComponentList[i]->getComponentType() == component_type) return mComponentList[i];
	}

	return NULL;
}