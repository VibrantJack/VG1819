#include "ProjectileManager.h"

#include "kitten\K_GameObjectManager.h"
#include "util\MathUtil.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

ProjectileManager* ProjectileManager::m_instance = nullptr;

ProjectileManager::ProjectileManager(const std::string& p_projectileList) : m_time(nullptr), m_lastSource(nullptr), m_lastFiredObj(nullptr)
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
			//Should rotate?
		    std::string rotate;
			std::getline(stream, rotate, ',');
			bool shouldRotate = (rotate == " true" || rotate == "true");
			// How many projectiles to fire : only applies to multi-target non-AOE abilities
			std::string projs;
			std::getline(stream, projs, ',');
			float numProjs = std::stof(projs);


			// Make the GameObject
			if (numProjs < 2)
			{
				auto gameObj = gameObjMan->createNewGameObject(jsonName);
				gameObj->setEnabled(false);

				// Insert into the map
				ProjectileMapEntry entry;
				entry.gameObject = gameObj;
				entry.speed = convertedTime;
				entry.arcHeight = convertedHeight;
				entry.shouldRotate = shouldRotate;

				m_projectiles.insert(std::make_pair(name, entry));
			}
			else
			{
				std::string delay;
				std::getline(stream, delay, ',');
				float delayBetweenProjectiles = std::stof(delay);

				for (int i = 0; i < numProjs; ++i)
				{
					auto gameObj = gameObjMan->createNewGameObject(jsonName);
					gameObj->setEnabled(false);

					ProjectileMapEntry entry;
					entry.gameObject = gameObj;
					entry.speed = convertedTime;
					entry.arcHeight = convertedHeight;
					entry.shouldRotate = shouldRotate;
					entry.delayBetweenAttacks = delayBetweenProjectiles;


					m_projectiles.insert(std::make_pair(name + std::to_string(i), entry));
				}
			}
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
	m_instance->m_lastPackage = p_package;
	m_instance->m_lastAbility = p_ability;
	m_instance->m_lastUnitSel = p_source->getGameObject().getComponent<unit::UnitSelect>();
	m_instance->m_lastUnitSel->disableInteraction(true);
	m_instance->m_firingMultipleProjectiles = false;
	m_instance->m_firedForMultiDamage = false;

	m_instance->privateFireProjectile(p_type, p_source->getTransform(), p_target->getTransform());
}


void ProjectileManager::multiDamageFireProjectile(const keyType& p_type, unit::Unit* p_source, ability::Ability* p_ability, ability::AbilityInfoPackage* p_package)
{
	m_instance->m_lastPackage = p_package;
	m_instance->m_lastAbility = p_ability;
	m_instance->m_lastUnitSel = p_source->getGameObject().getComponent<unit::UnitSelect>();
	m_instance->m_lastUnitSel->disableInteraction(true);

	m_instance->m_firedForMultiDamage = true;

	kitten::K_GameObject* clickedObj = p_package->m_clickedObject;
	
	if (clickedObj != nullptr)
	{
		m_instance->m_firingMultipleProjectiles = false;
		m_instance->privateFireProjectile(p_type, p_source->getTransform(), p_package->m_clickedObject->getTransform());
	}
	else
	{
		// We are firing multiple projectiles over some time

		m_instance->m_firingMultipleProjectiles = true;
		m_instance->m_lastSource = &(p_source->getTransform());
		m_instance->m_delayBetweenFires = m_instance->m_projectiles[p_type + std::to_string(0)].delayBetweenAttacks;
		m_instance->m_lastFiredObj = nullptr;
		m_instance->m_lastProjName = p_type;
		m_instance->m_targetIndex = 0;

		m_instance->setEnabled(true);
	}
}

void ProjectileManager::privateFireProjectile(const keyType& p_type, const kitten::Transform& p_source, const kitten::Transform& p_target)
{
	auto entry = m_projectiles[p_type];

	kitten::K_GameObject* proj = entry.gameObject;
	m_lastGO = proj;

	// Move the projectile 
	LerpController* lerpCon = proj->getComponent<LerpController>();
	assert(lerpCon != nullptr);

	const glm::vec3& startPos = p_source.getTranslation();
	proj->getTransform().place(startPos.x, startPos.y+1, startPos.z);

	const glm::vec3& endPos = p_target.getTranslation();

	glm::vec3 direction = startPos - endPos;
	direction = glm::normalize(direction);

	// Get the angle between the source and the destination to rotate the projectile
	float xDist = p_source.getTranslation().x - p_target.getTranslation().x;
	float zDist = p_source.getTranslation().z - p_target.getTranslation().z;
	float hypotenuseDistance = sqrt((xDist*xDist + zDist*zDist));

	float degAngle;
	Direction projDirection = other;

	if (zDist == 0.0f) // left/right
	{
		if (xDist > 0)
		{
			degAngle = -90;
			projDirection = right;
		}
		else
		{
			degAngle = 90;
			projDirection = left;
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
				degAngle = -180; // down
				projDirection = down;
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
				projDirection = other;
			}
		}
		else
		{
			if (xDist == 0)
			{
				//up
				projDirection = up;
			}
		}
	}

	proj->getTransform().rotateAbsolute(glm::vec3(0, 0, -degAngle));

	lerpCon->addPositionLerpFinishedCallback(this);

	float time = entry.speed * hypotenuseDistance;
	float projArcHeight = entry.arcHeight;

	if (projArcHeight != 0.0f)
	{
		lerpCon->arcLerp(endPos, time, projArcHeight);

		if (entry.shouldRotate)
		{
			// Calculate starting Z angle
			// opposite / adjacent
			float oa = projArcHeight / (hypotenuseDistance / 2);
			float radZAngle = atan(oa);
			float degZAngle = radZAngle / DEG_TO_RAD_FACTOR;

			glm::quat maxRot, endRot;

			maxRot = proj->getTransform().getRotation();

			SWAP(direction.x, direction.z);

			std::cout << "direction: " << direction.x << ", " << direction.y << ", " << direction.z << std::endl;

			proj->getTransform().rotateRelative(-direction * degZAngle);
			proj->getTransform().rotateRelative(glm::vec3(45, 0, 0));

			endRot = glm::quat(radZAngle * direction) * maxRot;

			lerpCon->arcRotate(maxRot, endRot, time);
		}
		else
		{
			proj->getTransform().rotateRelative(glm::vec3(45, 0, 0));
		}
	}
	else
	{
		proj->getTransform().rotateRelative(glm::vec3(45, 0, 0));
		lerpCon->positionLerp(endPos, time);
	}

	proj->setEnabled(true);
}

void ProjectileManager::onPositionLerpFinished(kitten::K_GameObject* p_obj)
{
	if (!m_firingMultipleProjectiles || m_lastFiredObj == p_obj)
	{
		m_lastUnitSel->disableInteraction(false);

		if (m_firedForMultiDamage)
		{
			m_lastAbility->multiTargetProjectileFinished(m_lastPackage);
		}
		else
		{
			m_lastAbility->singleTargetProjectileFinished(m_lastPackage);
		}

		m_lastAbility = nullptr;
		m_lastPackage = nullptr;
		m_lastUnitSel = nullptr;
	}

	p_obj->setEnabled(false);
}

void ProjectileManager::start()
{
	m_time = kitten::K_Time::getInstance();
	assert(m_time != nullptr);

	setEnabled(false);
}

void ProjectileManager::update()
{
	assert(m_firingMultipleProjectiles, "Enabling / disabling broke again");

	m_timeElapsed += m_time->getDeltaTime();

	if (m_timeElapsed >= m_delayBetweenFires)
	{
		auto target = m_lastPackage->m_targets[m_targetIndex];
		m_instance->privateFireProjectile(m_lastProjName + std::to_string(m_targetIndex), *m_lastSource, target->getTransform());

		++m_targetIndex;
		if (m_targetIndex == m_lastPackage->m_targets.size())
		{
			m_lastFiredObj = m_projectiles[m_lastProjName + std::to_string(m_targetIndex-1)].gameObject;
			setEnabled(false);
		}

		m_timeElapsed = 0.0f;
	}
}