#include "SceneWriter.h"

SceneWriter::SceneWriter()
{
}

SceneWriter::~SceneWriter()
{
}

void SceneWriter::WriteToFile(std::string inputFilePath)
{
	std::string filePath = "";
	//if (inputFilePath.find(".iet") != std::string::npos)
	//{
	//	filePath = inputFilePath;
	//}
	//else
	//{
	//	filePath = inputFilePath + ".iet";
	//}

	filePath = inputFilePath + ".level";

	std::ofstream sceneFile;
	sceneFile.open(filePath, std::ios::out);

	std::cout << "FilePath: " << filePath << "\n";

	std::vector<AGameObject*> allObjects = GameObjectManager::getInstance()->getAllGameObjects();

	AGameObject* currentObject;
	AComponent* objectComponent;
	PhysicsComponent* physicsComponent;

	for (int i = 0; i < allObjects.size(); i++)
	{
		currentObject = allObjects[i];

		sceneFile << currentObject->getObjectName() << std::endl;
		Vector3D pos = currentObject->getLocalPosition();
		Vector3D rot = currentObject->getLocalRotation();
		Vector3D scale = currentObject->getLocalScale();

		sceneFile << "Type: " << currentObject->getObjectType() << std::endl;
		sceneFile << "Position: " << pos.x << " " << pos.y << " " << pos.z << std::endl;
		sceneFile << "Rotation: " << rot.x << " " << rot.y << " " << rot.z << std::endl;


		//--------------------------------------------------------------------------------
		//DELETE THIS PART AFTER DONE WITH FINALS TO GET BACK SAVE AND LOAD FUNCTIONALITY
		//--------------------------------------------------------------------------------
		if (currentObject->getObjectType() == AGameObject::PLANE)
		{
			scale.x /= 10;
			scale.z /= 10;
		}

		sceneFile << "Scale: " << scale.x << " " << scale.y << " " << scale.z << std::endl;

		if (currentObject->isActive())
		{
			sceneFile << "Active: 1" << std::endl;
		}
		else
		{
			sceneFile << "Active: 0" << std::endl;
		}

		objectComponent = currentObject->findComponentOfType(AComponent::PHYSICS);

		if (objectComponent)
		{
			physicsComponent = (PhysicsComponent*)objectComponent;

			sceneFile << "PhysicsComponent: 1" << std::endl;
			sceneFile << "Active: " << physicsComponent->isActive() << std::endl;
			sceneFile << "Static: " << physicsComponent->isStatic() << std::endl;
			sceneFile << "Gravity: " << physicsComponent->isGravityEnabled() << std::endl;
			sceneFile << "Mass: " << physicsComponent->getMass() << std::endl;
		}
		else
		{
			sceneFile << "PhysicsComponent: 0" << std::endl;
			sceneFile << "Active: 0" << std::endl;
			sceneFile << "Static: 0" << std::endl;
			sceneFile << "Gravity: 0" << std::endl;
			sceneFile << "Mass: 0" << std::endl;
		}

		objectComponent = nullptr;
		physicsComponent = nullptr;
	}

	sceneFile.close();
}

void SceneWriter::LoadFromFile(std::string inputFilePath)
{
	std::string filePath = "";
	if (inputFilePath.find(".iet") != std::string::npos)
	{
		filePath = inputFilePath;
	}
	else
	{
		filePath = inputFilePath + ".iet";
	}

	std::ifstream sceneFile;
	sceneFile.open(filePath, std::ios::out);
	if (sceneFile.fail())
	{
		std::cout << "ERROR: Failed to open file at path " << filePath << std::endl;
		return;
	}
	
	//delete all object in scene to prepare for loading
	std::vector<AGameObject*> allObjects = GameObjectManager::getInstance()->getAllGameObjects();
	for (int i = 0; i < allObjects.size(); i++)
	{
		std::cout << "Deleting: " << allObjects[i]->getObjectName();
		GameObjectManager::getInstance()->deleteObject(allObjects[i]);
	}

	std::string currentLine;
	int index = 0;

	std::string objectName = "";
	AGameObject::ObjectType objectType;
	Vector3D pos;
	Vector3D rot;
	Vector3D scale;

	bool isActive;
	bool hasPhysics;
	bool isPhysicsActive;
	bool isStatic;
	bool isGravityActive;
	float mass;

	while (std::getline(sceneFile, currentLine))
	{
		switch (index) {
		case 0:
		{
			objectName = currentLine;
			std::cout << objectName << std::endl;
			index++;

			break;
		}

		case 1:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			objectType = (AGameObject::ObjectType)std::stoi(split[1]);
			std::cout << objectType << std::endl;
			index++;

			break;
		}

		case 2:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			pos = Vector3D(std::stof(split[1]), std::stof(split[2]), std::stof(split[3]));
			std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
			index++;

			break;
		}

		case 3:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			rot = Vector3D(std::stof(split[1]), std::stof(split[2]), std::stof(split[3]));
			std::cout << rot.x << " " << rot.y << " " << rot.z << std::endl;
			index++;

			break;
		}

		case 4:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			scale = Vector3D(std::stof(split[1]), std::stof(split[2]), std::stof(split[3]));
			std::cout << scale.x << " " << scale.y << " " << scale.z << std::endl;
			index++;

			break;
		}

		case 5:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			isActive = std::stoi(split[1]);
			std::cout << isActive << std::endl;
			index++;

			break;
		}

		case 6:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			hasPhysics = std::stoi(split[1]);
			std::cout << hasPhysics << std::endl;
			index++;

			break;
		}

		case 7:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			isPhysicsActive = std::stoi(split[1]);
			std::cout << isPhysicsActive << std::endl;
			index++;

			break;
		}

		case 8:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			isStatic = std::stoi(split[1]);
			std::cout << isStatic << std::endl;
			index++;

			break;
		}

		case 9:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			isGravityActive = std::stoi(split[1]);
			std::cout << isGravityActive << std::endl;
			index++;

			break;
		}

		case 10:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			mass = std::stof(split[1]);
			std::cout << mass << std::endl;
			index = 0;

			GameObjectManager::getInstance()->recreateObject(
				objectName,
				objectType,
				pos,
				rot,
				scale,
				hasPhysics,
				isPhysicsActive,
				isStatic,
				isGravityActive,
				mass
			);

			break;
		}

		}
	}
}

void SceneWriter::LoadFromUnityFile(std::string inputFilePath)
{
	std::ifstream sceneFile;
	sceneFile.open(inputFilePath, std::ios::in);
	if (sceneFile.fail())
	{
		std::cout << "ERROR: Failed to open file at path " << inputFilePath << std::endl;
		return;
	}

	//delete all object in scene to prepare for loading
	std::vector<AGameObject*> allObjects = GameObjectManager::getInstance()->getAllGameObjects();
	for (int i = 0; i < allObjects.size(); i++)
	{
		std::cout << "Deleting: " << allObjects[i]->getObjectName();
		GameObjectManager::getInstance()->deleteObject(allObjects[i]);
	}

	std::string readLine;
	std::vector<UnityGameObject*> unityGameObjectList;
	UnityGameObject* currentObject = new UnityGameObject();

	//skip unneeded lines in .unity file
	bool lineSkipped = false;

	while (std::getline(sceneFile, readLine))
	{
		if (readLine.find("--- !u!") != std::string::npos)
		{
			if (lineSkipped)
			{
				unityGameObjectList.push_back(currentObject);
			}
			else
			{
				UnityGameObject* object = currentObject;
				delete object;
				lineSkipped = true;
			}

			currentObject = nullptr;
			currentObject = new UnityGameObject();
		}

		currentObject->addLine(readLine);
	}

	unityGameObjectList.push_back(currentObject);

	sceneFile.close();

	for (int i = 0; i < unityGameObjectList.size(); i++)
	{
		unityGameObjectList[i]->parseInfo();
	}

	std::vector<UnityGameObject*> gameObjectList;
	std::vector<UnityGameObject*> transformList;
	std::vector<UnityGameObject*> meshList;
	std::vector<UnityGameObject*> physicsList;

	for (int i = 0; i < unityGameObjectList.size(); i++)
	{
		int type = unityGameObjectList[i]->getObjectType();
		switch (type)
		{
		//gameObject
		case 1:
			gameObjectList.push_back(unityGameObjectList[i]);
			break;

		//transform
		case 4:
			transformList.push_back(unityGameObjectList[i]);
			break;

		//meshfilter
		case 33:
			meshList.push_back(unityGameObjectList[i]);
			break;

		//rigidbody
		case 54:
			physicsList.push_back(unityGameObjectList[i]);
			break;

		default: {}
		}
	}

	for (int i = 0; i < meshList.size(); i++)
	{
		//skip over this part
		if (meshList[i]->getGameObjectType() == 0)
		{
			continue;
		}

		long long int ownerID = meshList[i]->getOwnerID();

		UnityGameObject* gameObject = nullptr;
		UnityGameObject* transform = nullptr;
		UnityGameObject* physics = nullptr;

		for (int j = 0; j < gameObjectList.size(); j++)
		{
			if (gameObjectList[j]->getObjectID() == ownerID)
			{
				gameObject = gameObjectList[j];
				break;
			}
		}

		if (!gameObject)
		{
			break;
		}

		for (int j = 0; j < transformList.size(); j++) 
		{
			if (transformList[j]->getOwnerID() == ownerID) 
			{
				transform = transformList[j];
				break;
			}
		}

		if (!transform)
		{
			break;
		}

		for (int j = 0; j < physicsList.size(); j++)
		{
			if (physicsList[j]->getOwnerID() == ownerID)
			{
				physics = physicsList[j];
				break;
			}
		}

		Vector3D scale = transform->getScale();

		//adjust to our kinda planes
		if (meshList[i]->getGameObjectType() == 2)
		{
			scale.x *= 10.f;
			scale.z *= 10.f;
		}

		bool hasPhysics = (physics != nullptr);
		bool isStatic = false;
		bool isGravityOn = false; 
		float mass = 0.f; 

		if (hasPhysics)
		{
			isStatic = physics->getStatic();
			isGravityOn = physics->getGravityActive();
			mass = physics->getMass();
		}

		GameObjectManager::getInstance()->recreateObject(
			gameObject->getGameObjectName(),
			(AGameObject::ObjectType)meshList[i]->getGameObjectType(),
			transform->getPosition(),
			transform->getRotation(),
			scale,
			hasPhysics,
			hasPhysics,	//ignored mostly, physics is always active if it has a rigidbody
			isStatic,
			isGravityOn,
			mass
		);
	}

	gameObjectList.clear();
	transformList.clear();
	meshList.clear();
	physicsList.clear();

	while (!unityGameObjectList.empty())
	{
		UnityGameObject* object = unityGameObjectList[0];

		unityGameObjectList.erase(std::remove(unityGameObjectList.begin(), unityGameObjectList.end(), object), unityGameObjectList.end());
		unityGameObjectList.shrink_to_fit();

		delete object;
	}
}