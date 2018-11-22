#include "Ability.h"
#include "unit/Unit.h"
#include "board/tile/TileInfo.h"
#include <iostream>

void ability::Ability::singleTargetDamage(AbilityInfoPackage * p_info)
{
	//damage target by power
	if (checkTarget(p_info))
	{
		//trigger deal damage event
		triggerTPEvent(ability::TimePointEvent::Deal_Damage, p_info->m_source, p_info);

		//trigger receive damage event
		unit::Unit* target = p_info->m_targets[0];
		triggerTPEvent(ability::TimePointEvent::Receive_Damage, target, p_info);

		//so power will change to negative
		int power = -(p_info->m_intValue.find(UNIT_POWER)->second);

		damage(target, power);
	}

	//delete package
	done(p_info);
}

void ability::Ability::multiTargetDamage(AbilityInfoPackage * p_info)
{
	if (checkTarget(p_info))
	{
		//deal damaga to all units

		//trigger deal damage event
		triggerTPEvent(ability::TimePointEvent::Deal_Damage, p_info->m_source, p_info);

		for (unit::Unit* u : p_info->m_targets)
		{
			//get copy of package
			AbilityInfoPackage* clonePackage = new AbilityInfoPackage(*p_info);

			//trigger receive damage
			triggerTPEvent(ability::TimePointEvent::Receive_Damage, u, clonePackage);

			int power = -(clonePackage->m_intValue.find(UNIT_POWER)->second);

			damage(u, power);

			//delete clone
			delete clonePackage;
		}
	}

	//delete package
	done(p_info);
}

int ability::Ability::damage(unit::Unit* p_target, int power)
{
	AbilityNode* node1 = AbilityNodeManager::getInstance()->findNode(ChangeAttribute);

	//change hp
	node1->effect(p_target, UNIT_HP, power);

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

bool ability::Ability::checkAlly(unit::Unit* p_source, unit::Unit* p_target)
{
	return p_source->m_clientId == p_target->m_clientId;
}

bool ability::Ability::checkTag(unit::Unit* p_u, const std::string& p_tag)
{
	for (std::string it : p_u->m_tags)
	{
		if (it == p_tag)
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