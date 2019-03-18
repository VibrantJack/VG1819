#pragma once
#include "ability/ability/Ability.h"
#include "unit/Unit.h"
#include "networking/ClientGame.h"
#include "kitten/event_system/EventManager.h"

//Rock

namespace ability
{
	int Clone::effect(AbilityInfoPackage* p_info)
	{
		//get card id
		int cardId = p_info->m_source->m_kibbleID;

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

		done(p_info);

		return 0;
	}
}