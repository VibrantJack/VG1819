#include "ProjectileManager.h"

#include "kitten\K_GameObjectManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

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
			float convertedTime = std::stof(time);

			// Make the GameObject
			auto gameObj = gameObjMan->createNewGameObject(jsonName);

			// Insert into the map
			m_projectiles.insert(std::make_pair(name, std::make_pair(gameObj, convertedTime)));
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
	auto pair = m_projectiles[p_type];

	kitten::K_GameObject* proj = pair.first;
	float time = pair.second;

	m_lastPackage = p_package;
	m_lastAbility = p_ability;

	// Move the projectile 
	LerpController* lerpCon = proj->getComponent<LerpController>();
	assert(lerpCon != nullptr);

	const glm::vec3& startPos = p_source->getTransform().getTranslation();
	proj->getTransform().place(startPos.x, startPos.y+1, startPos.z);

	lerpCon->addPositionLerpFinishedCallback(this);
	
	proj->setEnabled(true);
	lerpCon->positionLerp(p_target->getTransform().getTranslation(), time);	
}

void ProjectileManager::onPositionLerpFinished()
{
	m_lastAbility->singleTargetProjectileFinished(m_lastPackage);
	m_lastAbility = nullptr;
	m_lastPackage = nullptr;
}