#pragma once
#include"Vector3D.h"
#include"Matrix4x4.h"
#include<string>
#include<vector>
#include"StateSnapshot.h"
#include"AComponent.h"

class AVertexShader;
class APixelShader;

class AGameObject
{
public:
	enum ObjectType {
		NO_TYPE,
		CUBE,
		PLANE,
		TEXTURED_CUBE
	};

	AGameObject(std::string name, ObjectType type);
	~AGameObject();

	virtual void update(float delta_time);
	virtual void draw(int width, int height) = 0;

	std::string getObjectName();
	ObjectType getObjectType();

	bool isActive();
	void setActive(bool is_object_active);
	void select();
	void deselect();

	void setTranslationSpeed(float translation_speed);
	void setRotationSpeed(float rotation_speed);
	void setScaleSpeed(float scale_speed);

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D position);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rotation);
	Vector3D getLocalRotation();

	void updateLocalMatrix();
	void updatePhysicsMatrix(float physics_matrix[16]);
	Matrix4x4 getLocalMatrix();
	Matrix4x4 getPhysicsMatrix();

	void saveInitialState();
	void restoreInitialState();

	void attachComponent(AComponent* new_component);
	void detachComponent(AComponent* component);
	AComponent* findComponentOfType(AComponent::ComponentType component_type);

	__declspec(align(16))
		struct constant {
		Matrix4x4 worldMatrix;
		Matrix4x4 viewMatrix;
		Matrix4x4 projectionMatrix;
		float coefficient;
	};

protected:
	std::string mObjectName;
	ObjectType mObjectType;

	Vector3D mLocalPosition;
	Vector3D mLocalScale;
	Vector3D mLocalRotation;

	Matrix4x4 mLocalMatrix;
	Matrix4x4 mPhysicsMatrix;

	bool mIsActive = true;
	bool mIsSelected = false;

	StateSnapshot* mInitialState = nullptr;

	std::vector<AComponent*> mComponentList;

	AVertexShader* mVertexShader = nullptr;
	APixelShader* mPixelShader = nullptr;

	float mTranslationSpeed = 5.f;
	float mRotationSpeed = 1.f;
	float mScaleSpeed = 1.f;
};