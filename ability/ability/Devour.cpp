#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"

//Rock

namespace ability
{
	int Devour::effect(AbilityInfoPackage* p_info)
	{
		//deal damage to target

		//single target damage
		//trigger deal damage event
		triggerTPEvent(ability::TimePointEvent::Deal_Damage, p_info->m_source, p_info);

		//trigger receive damage event
		unit::Unit* target = p_info->m_targets[0];
		triggerTPEvent(ability::TimePointEvent::Receive_Damage, target, p_info);

		//so power will change to negative
		int power = -(p_info->m_intValue.find(UNIT_POWER)->second);

		changeHP(target, power);


		//check if target dies
		if (target->m_attributes[UNIT_HP] <= 0)
		{//add slime to hand
			//get card id
			int cardId = p_info->m_intValue[KIBBLE_ID];

			//get num
			int num = p_info->m_intValue[CARD_DRAWN];

			//create event
			kitten::Event* eventData = new kitten::Event(kitten::Event::EventType::Card_Drawn);

			std::unordered_map<int, int> cards;
			cards.insert(std::make_pair(cardId, num));
			putCardToHand(eventData, cards);

			//queue event
			kitten::EventManager::getInstance()->triggerEvent(
				kitten::Event::EventType::Put_Card_To_Hand,
				eventData
			);
		}

		UniversalSounds::playSound("devour");

		done(p_info);

		return 0;

		return 0;
	}
}