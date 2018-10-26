#include "Ability.h"
#include "unit/Unit.h"
#include <iostream>

int ability::Ability::damage(unit::Unit* p_target, int power)
{
	AbilityNode* node1 = AbilityNodeManager::getInstance()->findNode("ChangeAttributeNode");
	AbilityNode* node2 = AbilityNodeManager::getInstance()->findNode("CheckHPNode");

	std::cout <<p_target->m_name<<" is damaged by "<< power <<std::endl;

	//change hp
	node1->effect(p_target, "hp", power);
	//then check hp
	node2->effect(p_target);

	return 0;
}

void ability::Ability::done(const AbilityInfoPackage* p_info)
{
	p_info->m_source->actDone();

	delete p_info;
}
