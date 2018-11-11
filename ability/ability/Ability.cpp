#include "Ability.h"
#include "unit/Unit.h"
#include "board/tile/TileInfo.h"
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

bool ability::Ability::checkTarget(const AbilityInfoPackage * p_info)
{
	if (&(p_info->m_targets) != nullptr)
	{
		if (p_info->m_targets.size() > 0)
		{
			return true;
		}
	}
	return false;
}

void ability::Ability::getTarget(AbilityInfoPackage * p_info)
{
	std::vector<unit::Unit*> unitlist;
	std::vector<kitten::K_GameObject*> tileList = p_info->m_targetTilesGO;

	for (kitten::K_GameObject* t : tileList)
	{
		TileInfo* ti = t->getComponent<TileInfo>();

		if (ti->hasUnit())
		{
			kitten::K_GameObject* u = ti->getUnit();
			unitlist.push_back(u->getComponent<unit::Unit>());
		}
	}

	p_info->m_targets = unitlist;
}

void ability::Ability::triggerTPEvent(ability::TimePointEvent::TPEventType p_tp, unit::Unit * p_target, AbilityInfoPackage * p_info)
{
	unit::StatusContainer* sc = p_target->getStatusContainer();
	ability::TimePointEvent* t = new ability::TimePointEvent(p_tp);
	t->putPackage(INFO_PACKAGE_KEY, p_info);
	sc->triggerTP(p_tp, t);
}
