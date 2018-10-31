#pragma once

#include "kitten\K_Component.h"
#include "puppy\Text\TextBox.h"
#include "kitten\event_system\EventManager.h"
#include "ability\AbilityManager.h"

class SelectAbility : public kitten::K_Component
{
private:
	int m_num;//number of instructions
	std::vector<std::string>* m_instructionList;
	unit::Unit* m_unit;
public:
	enum AbilityType
	{
		Manipulate_Tile,
		Summon_Unit
	};

	SelectAbility();
	~SelectAbility();

	//void useAbility(AbilityType p_ability);

	void set(unit::Unit* p_u, std::vector<std::string>* p_list);
	void select(int p_i);

	//void start() override;
	//virtual bool hasUpdate() const override { return true; };
	//virtual void update() override;
};