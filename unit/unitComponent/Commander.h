#pragma once
#include "unit/UnitCommon.h"
#include "kitten/event_system/EventManager.h"

//@Rock

namespace unit
{
	class Commander
	{
	private:
		unit::AbilityDescription* m_adTile;
		unit::AbilityDescription* m_adSpawn;
		Unit* m_unit;
	public:
		std::string m_porPath;

		Commander();
		~Commander();

		void init(Unit* p_u);

		void manipulateTile();
		void spawnUnit(kitten::Event::EventType p_type, kitten::Event * p_data);

		void resetPower(int p_clientID);
	};
}
