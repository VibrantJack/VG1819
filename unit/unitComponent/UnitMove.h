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
		const float m_speed = 0.25f;
		const glm::vec3 m_offset = glm::vec3(-0.5f,0.0f,0.0f);

		float distanceX;
		float distanceZ;

		kitten::K_GameObject* m_currentTile;
		kitten::K_GameObject* m_lastTile;

	public:
		UnitMove();
		~UnitMove();

		void registerListener();
		void deregisterListener();
		void listenEvent(kitten::Event::EventType p_type, kitten::Event* p_data);

		void attempToMove();
		void triggerHighLightEvent();
		void triggerUnhighLightEvent();
		void move(kitten::K_GameObject* p_targetTile);

		void setTile(kitten::K_GameObject* p_targetTile);
		void reset();
		bool hasUpdate() const override;
		void update() override;

	};
}