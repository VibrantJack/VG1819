#pragma once

#include "kitten\K_Component.h"
#include "puppy\Text\TextBox.h"
#include "kitten\event_system\EventManager.h"
#include "ability\AbilityManager.h"

class SelectAbility : public kitten::K_Component
{
public:
	enum AbilityType
	{
		Manipulate_Tile,
		Summon_Unit
	};

	SelectAbility();
	~SelectAbility();

	void useAbility(AbilityType p_ability);

	//void start() override;
	//virtual bool hasUpdate() const override { return true; };
	//virtual void update() override;
};