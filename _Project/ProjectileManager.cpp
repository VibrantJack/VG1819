#include "ProjectileManager.h"

#include "kitten\K_GameObjectManager.h"
#include "util\MathUtil.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

ProjectileManager* ProjectileManager::m_instance = nullptr;

ProjectileManager::ProjectileManager(const std::string& p_projectileList)
{
	assert(m_instance == nullptr);
	m_instance = this;
	
	// load in the effects
	std::ifstream file(p_projectileList);
	assert(file.is_open()); // assertation failed? path is wrong or file missing

	auto gameObjMan = kitten::K_GameObjectManager::getInstance();

	std::string line;
	while (std::getline(file, line))
	{
		if (line[0] != '/' && line[1] != '/') //skip comment
		{
			std::stringstream stream(line);
			// get the name
			std::string name;
			std::getline(stream, name, ',');
			// get the json (gameobject file) name
			std::string jsonName;
			std::getline(stream, jsonName, ',');
			// get the time
			std::string time;
			std::getline(stream, time, ',');
			float convertedTime = 1.0f/std::stof(time);
			//get the arc height
			std::string height;
			std::getline(stream, height, ',');
			float convertedHeight = std::stof(height);

			// Make the GameObject
			auto gameObj = gameObjMan->createNewGameObject(jsonName);
			gameObj->setEnabled(false);

			// Insert into the map
			ProjectileMapEntry entry;
			entry.gameObject = gameObj;
			entry.speed = convertedTime;
			entry.arcHeight = convertedHeight;

			m_projectiles.insert(std::make_pair(name, entry));
		}
	}

	file.close();
}

ProjectileManager::~ProjectileManager()
{
	assert(m_instance == this);
	m_instance = nullptr;
}

void ProjectileManager::fireProjectile(const keyType& p_type, unit::Unit* p_source, unit::Unit* p_target, ability::Ability* p_ability, ability::AbilityInfoPackage* p_package)
{
	m_instance->privateFireProjectile(p_type, p_source, p_target, p_ability, p_package);
}

void ProjectileManager::privateFireProjectile(const keyType& p_type, unit::Unit* p_source, unit::Unit* p_target, ability::Ability* p_ability, ability::AbilityInfoPackage* p_package)
{
	auto entry = m_projectiles[p_type];

	kitten::K_GameObject* proj = entry.gameObject;
	m_lastGO = proj;
	
	m_lastPackage = p_package;
	m_lastAbility = p_ability;

	// Move the projectile 
	LerpController* lerpCon = proj->getComponent<LerpController>();
	assert(lerpCon != nullptr);

	const glm::vec3& startPos = p_source->getTransform().getTranslation();
	proj->getTransform().place(startPos.x, startPos.y+2, startPos.z);

	// Get the angle between the source and the destination to rotate the projectile
	float xDist = p_source->getTransform().getTranslation().x - p_target->getTransform().getTranslation().x;
	float zDist = p_source->getTransform().getTranslation().z - p_target->getTransform().getTranslation().z;
	float hypotenuseDistance = sqrt((xDist*xDist + zDist*zDist));

	float degAngle;
	if (zDist == 0.0f)
	{
		if (xDist > 0)
		{
			degAngle = -90;
		}
		else
		{
			degAngle = 90;
		}
	}
	else
	{
		float radAngle = atan(xDist / zDist);
		degAngle = radAngle / DEG_TO_RAD_FACTOR;

		if (zDist > 0)
		{
			if (degAngle == 0)
			{
				degAngle = -180; //Straight up/down
			}
			else
			{
				if (degAngle > 0)
				{
					degAngle += 180;
				}
				else
				{
					degAngle -= 180;
				}
			}
		}
	}

	proj->getTransform().rotateAbsolute(glm::vec3(0, 0, -degAngle));
	proj->getTransform().rotateRelative(glm::vec3(45, 0, 0)); //rotate to the camera
	

	lerpCon->addPositionLerpFinishedCallback(this);

	float time = entry.speed * hypotenuseDistance;
	float projArcHeight = entry.arcHeight;

	if (projArcHeight != 0.0f)
	{
		lerpCon->arcLerp(p_target->getTransform().getTranslation(), time, projArcHeight);
	}
	else
	{
		lerpCon->positionLerp(p_target->getTransform().getTranslation(), time);
	}
	
	m_lastUnitSel = p_source->getGameObject().getComponent<unit::UnitSelect>();
	m_lastUnitSel->disableInteraction(true);

	proj->setEnabled(true);
}

void ProjectileManager::onPositionLerpFinished()
{
	m_lastUnitSel->disableInteraction(false);

	m_lastAbility->singleTargetProjectileFinished(m_lastPackage);
	
	m_lastAbility = nullptr;
	m_lastPackage = nullptr;
	m_lastUnitSel = nullptr;

	m_lastGO->setEnabled(false);
}
