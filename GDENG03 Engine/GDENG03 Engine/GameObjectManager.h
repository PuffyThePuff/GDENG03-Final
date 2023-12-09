#pragma once
#include"AGameObject.h"
#include<string>
#include<vector>
#include<unordered_map>
#include"AVertexShader.h"
#include"APixelShader.h"

class GameObjectManager
{
public:
	enum PrimitiveType {
		CUBE,
		PLANE,
		PHYSICS_CUBE,
		PHYSICS_PLANE,
		TEXTURED_CUBE
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(std::string name);
	std::vector<AGameObject*> getAllGameObjects();
	int getObjectCount();
	int getActiveObjectCount();
	void update();
	void draw(int viewport_width, int viewport_height);

	void addObject(AGameObject* game_object);
	void createObject(PrimitiveType spawn_type);
	void recreateObject(
		std::string object_name,
		AGameObject::ObjectType object_type,
		Vector3D object_position,
		Vector3D object_rotation,
		Vector3D object_scale,
		bool has_physics_component,
		bool is_physics_active,
		bool is_static,
		bool is_gravity_enabled,
		float mass
	);
	void deleteObject(AGameObject* game_object);
	void deleteObjectByName(std::string name);

	void setSelectedObject(std::string name);
	void setSelectedObject(AGameObject* game_object);
	AGameObject* getSelectedObject();
	void deselectObject();

	void saveInitialStates();
	void restoreInitialStates();

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator =(GameObjectManager const&) {};
	static GameObjectManager* instance;

	std::vector<AGameObject*> mGameObjectList;
	std::unordered_map<std::string, AGameObject*> mGameObjectTable;

	AGameObject* mCurrentSelectedObject = nullptr;
};