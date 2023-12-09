#include "UnityGameObject.h"
#include "StringUtilities.h"

UnityGameObject::UnityGameObject()
{
	objectUnityClass = 0;
	objectUnityId = 0;

	objectName = " ";
	objectType = 0;
	isActive = false;

	localScale.x = 1.f;
	localScale.y = 1.f;
	localScale.z = 1.f;

	ownerId = 0;

	mass = 0.f;
	isGravityActive = false;
	isStatic = false;
}

UnityGameObject::~UnityGameObject()
{

}

void UnityGameObject::addLine(std::string gameObjectInfo)
{
	objectInfo.push_back(gameObjectInfo);
}

void UnityGameObject::parseInfo()
{
	std::string idLine = objectInfo[0];
	idLine.erase(std::remove(idLine.begin(), idLine.end(), ' '), idLine.end());

	std::vector<std::string> temp1 = StringUtilities::split(idLine, '!');
	std::vector<std::string> temp2 = StringUtilities::split(temp1[2], '&');

	objectUnityClass = std::stoll(temp2[0]);
	objectUnityId = std::stoll(temp2[1]);

	switch (objectUnityClass)
	{
		//gameObject
		case 1:
		{
			//need to skip the first few lines
			for (int i = 2; i < objectInfo.size(); i++)
			{
				std::string line = objectInfo[i];

				//alexa what is continue?
				//stops the current loop and iterates
				if (objectInfo[i].find("component") != std::string::npos)
				{
					line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
					line.erase(std::remove(line.begin(), line.end(), '{'), line.end());
					line.erase(std::remove(line.begin(), line.end(), '}'), line.end());

					std::vector<std::string> component = StringUtilities::split(line, ':');

					componentList.push_back(std::stoll(component[2]));

					continue;
				}

				if (objectInfo[i].find("m_Name") != std::string::npos)
				{
					std::vector<std::string> name = StringUtilities::split(line, ':');

					objectName = name[1];

					objectName.erase(objectName.begin());

					continue;
				}

				if (objectInfo[i].find("m_IsActive") != std::string::npos)
				{
					line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

					std::vector<std::string> active = StringUtilities::split(line, ':');

					isActive = std::stoi(active[1]);

					continue;
				}
			}
		} break;

		//transform
		case 4:
		{
			for (int i = 2; i < objectInfo.size(); i++)
			{
				std::string line = objectInfo[i];

				line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
				line.erase(std::remove(line.begin(), line.end(), '{'), line.end());
				line.erase(std::remove(line.begin(), line.end(), '}'), line.end());

				std::vector<std::string> parsedInfo = StringUtilities::split(line, ':');

				if (objectInfo[i].find("m_LocalPosition") != std::string::npos)
				{
					localPos.x = std::stof(parsedInfo[2].substr(0, parsedInfo[2].find(",")));
					localPos.y = std::stof(parsedInfo[3].substr(0, parsedInfo[3].find(",")));
					localPos.z = std::stof(parsedInfo[4]);

					continue;
				}

				if (objectInfo[i].find("m_LocalScale") != std::string::npos)
				{
					localScale.x = std::stof(parsedInfo[2].substr(0, parsedInfo[2].find(",")));
					localScale.y = std::stof(parsedInfo[3].substr(0, parsedInfo[3].find(",")));
					localScale.z = std::stof(parsedInfo[4]);

					continue;
				}

				if (objectInfo[i].find("m_LocalEulerAnglesHint") != std::string::npos)
				{
					localRot.x = std::stof(parsedInfo[2].substr(0, parsedInfo[2].find(",")));
					localRot.y = std::stof(parsedInfo[3].substr(0, parsedInfo[3].find(",")));
					localRot.z = std::stof(parsedInfo[4]);

					//convert angles to radians
					localRot.x *= acos(0.f) / 90.f;
					localRot.y *= acos(0.f) / 90.f;
					localRot.z *= acos(0.f) / 90.f;

					continue;
				}

				if (objectInfo[i].find("m_GameObject") != std::string::npos) 
				{
					ownerId = std::stoll(parsedInfo[2]);

					continue;
				}
			}
		} break;

		//mesh filter; checks if cube or plane
		case 33:
		{
			for (int i = 2; i < objectInfo.size(); i++)
			{
				std::string line = objectInfo[i];

				line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
				line.erase(std::remove(line.begin(), line.end(), '{'), line.end());
				line.erase(std::remove(line.begin(), line.end(), '}'), line.end());

				std::vector<std::string> parsedInfo = StringUtilities::split(line, ':');

				if (objectInfo[i].find("m_Mesh") != std::string::npos)
				{
					long long meshID = std::stoll(parsedInfo[2].substr(0, parsedInfo[2].find(",")));

					if (meshID == 10202)
					{
						objectType = 1;
					}
					else if (meshID == 10209)
					{
						objectType = 2;
					}

					continue;
				}

				if (objectInfo[i].find("m_GameObject") != std::string::npos)
				{
					ownerId = std::stoll(parsedInfo[2]);

					continue;
				}
			}
		} break;

		//rigidbody
		case 54:
		{
			for (int i = 2; i < objectInfo.size(); i++)
			{
				std::string line = objectInfo[i];

				if (objectInfo[i].find("m_Mass") != std::string::npos)
				{
					line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

					std::vector<std::string> mass = StringUtilities::split(line, ':');

					this->mass = std::stof(mass[1]);

					continue;
				}

				if (objectInfo[i].find("m_UseGravity") != std::string::npos)
				{
					line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

					std::vector<std::string> gravity = StringUtilities::split(line, ':');

					isGravityActive = std::stoi(gravity[1]);

					continue;
				}

				if (objectInfo[i].find("m_IsKinematic") != std::string::npos)
				{
					line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

					std::vector<std::string> kinematic = StringUtilities::split(line, ':');
					isStatic = std::stoi(kinematic[1]);

					continue;
				}

				if (objectInfo[i].find("m_GameObject") != std::string::npos) 
				{
					line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
					line.erase(std::remove(line.begin(), line.end(), '{'), line.end());
					line.erase(std::remove(line.begin(), line.end(), '}'), line.end());

					std::vector<std::string> owner = StringUtilities::split(line, ':');
					ownerId = std::stoll(owner[2]);

					continue;
				}
			}
		} break;

		default: {}
	}
}

long long int UnityGameObject::getObjectID()
{
	return objectUnityId;
}

long long int UnityGameObject::getObjectType()
{
	return objectUnityClass;
}

std::string UnityGameObject::getGameObjectName()
{
	return objectName;
}

int UnityGameObject::getGameObjectType()
{
	return objectType;
}

bool UnityGameObject::getActive()
{
	return this->isActive;
}

Vector3D UnityGameObject::getPosition()
{
	return this->localPos;
}

Vector3D UnityGameObject::getRotation()
{
	return this->localRot;
}

Vector3D UnityGameObject::getScale()
{
	return this->localScale;
}

std::vector<long long int> UnityGameObject::getComponentList()
{
	return this->componentList;
}

long long int UnityGameObject::getOwnerID()
{
	return this->ownerId;
}

float UnityGameObject::getMass()
{
	return this->mass;
}

bool UnityGameObject::getGravityActive()
{
	return this->isGravityActive;
}

bool UnityGameObject::getStatic()
{
	return this->isStatic;
}