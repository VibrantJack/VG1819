#pragma once
#include "kitten\K_Component.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_Time.h"

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
		float delayBetweenAttacks;
	};

	std::unordered_map<keyType, ProjectileMapEntry> m_projectiles;

	ability::AbilityInfoPackage* m_lastPackage;
	ability::Ability* m_lastAbility;
	kitten::K_GameObject* m_lastGO;
	unit::UnitSelect* m_lastUnitSel;

	bool m_firedForMultiDamage = false;

	// Used for firing multiple projectiles for the same ability
	bool m_firingMultipleProjectiles = false;
	keyType m_lastProjName;

	int m_targetIndex = 0;

	float m_delayBetweenFires = 0.0f, m_timeElapsed =0.0f;
	
	kitten::K_Time* m_time = nullptr;
	kitten::Transform* m_lastSource;
	kitten::K_GameObject* m_lastFiredObj = nullptr;

	// Methods

	void privateFireProjectile(const keyType& p_type, const kitten::Transform& p_source, const kitten::Transform& p_target);
	
	void onPositionLerpFinished(kitten::K_GameObject* p_obj) override;


	virtual bool hasUpdate() const override { return true; }
	virtual void start() override;
	virtual void update() override;

public:
	ProjectileManager(const std::string& p_projectileList);
	~ProjectileManager();

	static void fireProjectile(const keyType& p_type, unit::Unit* p_source, unit::Unit* p_target, ability::Ability* p_ability, ability::AbilityInfoPackage* p_package);
	static void multiDamageFireProjectile(const keyType& p_type, unit::Unit* p_source, ability::Ability* p_ability, ability::AbilityInfoPackage* p_package);
};