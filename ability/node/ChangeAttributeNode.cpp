#pragma once
#include "ability/node/AbilityNode.h"
#include "Unit/Unit.h"
#include "unit\unitComponent\UnitHealthBar.h"
#include "kitten\event_system\EventManager.h"

#include "_Project\CombatText.h"

#include <iostream>
//Rock

#define COMBAT_TEXT_BASE_TIME 1.5f
#define COMBAT_TEXT_TIME_CHANGE_SCALAR 3.33f

#define COMBAT_TEXT_BASE_SCALE glm::vec2(0.02f,0.02f)
#define COMBAT_TEXT_SCALE_CHANGE_SCALAR -0.25f

#define COMBAT_TEXT_INITIAL_OFFSET glm::vec3(1,0.5,0)

namespace ability
{

	ChangeAttributeNode::ChangeAttributeNode()
	{

	}

	int ChangeAttributeNode::effect(unit::Unit* p_target, const std::string & p_name, int p_value)
	{
		std::unordered_map<std::string, int>::iterator it;

		std::cout << p_target->m_name << " : "<<p_name<<" is changed by " << p_value << std::endl;

		it = p_target->m_attributes.find(p_name);
		if (it != p_target->m_attributes.end())
		{
			it->second += p_value;
		}
		else
		{
			//if counter doesn't exist, add it
			p_target->m_attributes[p_name] = p_value;
		}

		if (p_name == UNIT_MV || p_name == UNIT_BASE_MV)
		{
			checkStructureMV(p_target);
		}

		kitten::Event* eventData = new kitten::Event(kitten::Event::Update_Card_Context_Attrib);
		eventData->putGameObj(UNIT_GO_KEY, &p_target->getGameObject());
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Update_Card_Context_Attrib, eventData);

		if (p_name == UNIT_HP || p_name == UNIT_MAX_HP)
		{
			AbilityNodeManager::getInstance()->findNode(CheckHP)->effect(p_target);
			unit::UnitHealthBar* healthBar = p_target->getGameObject().getComponent<unit::UnitHealthBar>();

			healthBar->updateBar();

			if (p_value > 0)
			{
				std::string text = "+" + std::to_string(p_value);
				glm::vec3 color(124, 252, 0); // Lawn green
				float time = (float)p_value / COMBAT_TEXT_TIME_CHANGE_SCALAR;
				glm::vec2 scale = COMBAT_TEXT_BASE_SCALE;// *(COMBAT_TEXT_SCALE_CHANGE_SCALAR * (float)p_value);

				CombatText::floatText(text, p_target->getTransform().getTranslation() + COMBAT_TEXT_INITIAL_OFFSET, time, color, scale);
			}
			else if (p_value == 0)
			{
				std::string text = std::to_string(p_value);
				glm::vec3 color(128,128,128); // Grey

				CombatText::floatText(text, p_target->getTransform().getTranslation(), COMBAT_TEXT_BASE_TIME, color,COMBAT_TEXT_BASE_SCALE);
			}
			else if (p_value < 0)
			{
				std::string text = std::to_string(p_value); //Automatically adds the `-`
				glm::vec3 color(255, 0, 0); // Red
				float time = (float)(-p_value) / COMBAT_TEXT_TIME_CHANGE_SCALAR;
				glm::vec2 scale = COMBAT_TEXT_BASE_SCALE; //*(COMBAT_TEXT_SCALE_CHANGE_SCALAR * (float)(-p_value));

				CombatText::floatText(text, p_target->getTransform().getTranslation() + COMBAT_TEXT_INITIAL_OFFSET, time, color, scale);
			}
		}

		//if (p_target->m_attributes[p_name] < 0)
		//	p_target->m_attributes[p_name] = 0;//no negative value

		return 0;
	}

	void ChangeAttributeNode::checkStructureMV(unit::Unit * p_target)
	{
		//structure can not move	
		if (p_target->checkTag(STRUCTURE))
		{
			p_target->m_attributes[UNIT_BASE_MV] = 0;
			p_target->m_attributes[UNIT_MV] = 0;
		}
	}

}