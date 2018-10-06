#pragma once
#include "unit/UnitCommon.h"
#include "kitten/event_system/EventManager.h"

//Rock
//This class contain infomation about unit's position
//It handles the unit's move function

namespace unit
{
	class UnitMove : public kitten::K_Component
	{
	private:
		const float m_speed = 1.0f;
		const glm::vec3 m_offset = glm::vec3(-0.5f,0.0f,0.0f);

		kitten::K_GameObject* m_lastTile;
		kitten::K_GameObject* m_targetTile;

	public:
		UnitMove();
		~UnitMove();

		void registerListener();
		void deregisterListener();
		void listenEvent(kitten::Event::EventType p_type, kitten::Event* p_data);

		void attempToMove();
		void move(kitten::K_GameObject* p_targetTile);

	};
}