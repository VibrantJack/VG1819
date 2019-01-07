#include "ProjectileManager.h"

ProjectileManager* ProjectileManager::m_instance = nullptr;

ProjectileManager::ProjectileManager(const std::string& p_projectileList)
{
	assert(m_instance == nullptr);
	m_instance = this;
	
	// load in the effects
}

ProjectileManager::~ProjectileManager()
{
	assert(m_instance == this);
	m_instance = nullptr;
}

void ProjectileManager::fireProjectile(int p_type, unit::Unit* p_source, unit::Unit* p_target, ability::Ability* p_ability, ability::AbilityInfoPackage* p_package)
{
	m_instance->privateFireProjectile(p_type, p_source, p_target, p_ability, p_package);
}

void ProjectileManager::privateFireProjectile(int p_type, unit::Unit* p_source, unit::Unit* p_target, ability::Ability* p_ability, ability::AbilityInfoPackage* p_package)
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
	proj->getTransform().place(startPos.x, startPos.y, startPos.z);

	lerpCon->addPositionLerpFinishedCallback(this);
	
	proj->setEnabled(true);
	lerpCon->positionLerp(p_target->getTransform().getTranslation(), time); // @todo data drive time
	
}

void ProjectileManager::onPositionLerpFinished()
{
	m_lastAbility->singleTargetProjectileFinished(m_lastPackage);
	m_lastAbility = nullptr;
	m_lastPackage = nullptr;
}