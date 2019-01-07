#pragma once
#include "kitten\K_Component.h"
#include "kitten\K_GameObject.h"
#include "unit\Unit.h"
#include "ability\AbilityInfoPackage.h"

#include "_Project\LerpController.h"

#include <unordered_map>
#include <string>

class ProjectileManager : public kitten::K_Component, public LerpController::PositionLerpFinishedCallback
{
private:
	static ProjectileManager* m_instance;

	std::unordered_map<int, std::pair<kitten::K_GameObject*, float>> m_projectiles;

	ability::AbilityInfoPackage* m_lastPackage;
	ability::Ability* m_lastAbility;

	void privateFireProjectile(int p_type, unit::Unit* p_source, unit::Unit* p_target, ability::Ability* p_ability ,ability::AbilityInfoPackage* p_package);

	void onPositionLerpFinished() override;
public:
	ProjectileManager(const std::string& p_projectileList);
	~ProjectileManager();

	static void fireProjectile(int p_type, unit::Unit* p_source, unit::Unit* p_target, ability::Ability* p_ability, ability::AbilityInfoPackage* p_package);
};