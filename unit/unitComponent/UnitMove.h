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

		bool notRegistered = true;

		bool set = false;//for test
		int m_tileX;
		int m_tileZ;

		float distanceX;
		float distanceZ;

		kitten::K_GameObject* m_currentTile;
		kitten::K_GameObject* m_lastTile;
		unit::AbilityDescription* m_ad;

		void triggerNewTileEvent();

	public:
		UnitMove();
		~UnitMove();

		void attempToMove(int p_min = 1, int p_max = -1);

		/*
		//move to unit interaction manager 
		void registerListener();
		void deregisterListener();
		void listenEvent(kitten::Event::EventType p_type, kitten::Event* p_data);

		void triggerHighLightEvent(int p_min = 1, int p_max = -1);
		void triggerUnhighLightEvent();*/

		void move(kitten::K_GameObject* p_targetTile);

		void setTile(kitten::K_GameObject* p_tile);
		void setTile(int p_x, int p_z);

		kitten::K_GameObject* getTile();
		void reset();

		bool hasUpdate() const override;
		void update() override;

	};
}