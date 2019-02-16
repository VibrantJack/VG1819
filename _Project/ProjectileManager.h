#pragma once
#include "kitten\K_Component.h"
#include "kitten\K_GameObject.h"

#include "unit\Unit.h"
#include "ability\AbilityInfoPackage.h"
#include "unit\unitComponent\UnitSelect.h"
#include "_Project\LerpController.h"

#include <unordered_map>
#include <string>

class ProjectileManager : public kitten::K_Component, public LerpController::PositionLerpFinishedCallback
{
private:
	static ProjectileManager* m_instance;
	typedef std::string keyType;

	enum Direction
	{
		up, left, right, down, other
	};

	struct ProjectileMapEntry
	{
		kitten::K_GameObject* gameObject;
		float speed;
		float arcHeight;
		bool shouldRotate;
	};

	std::unordered_map<keyType, ProjectileMapEntry> m_projectiles;

	ability::AbilityInfoPackage* m_lastPackage;
	ability::Ability* m_lastAbility;
	kitten::K_GameObject* m_lastGO;
	unit::UnitSelect* m_lastUnitSel;

	void privateFireProjectile(const keyType& p_type, unit::Unit* p_source, unit::Unit* p_target, ability::Ability* p_ability ,ability::AbilityInfoPackage* p_package);

	void onPositionLerpFinished() override;
public:
	ProjectileManager(const std::string& p_projectileList);
	~ProjectileManager();

	static void fireProjectile(const keyType& p_type, unit::Unit* p_source, unit::Unit* p_target, ability::Ability* p_ability, ability::AbilityInfoPackage* p_package);
};