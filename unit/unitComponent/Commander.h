#pragma once
#include "unit/UnitCommon.h"
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
		Commander();
		~Commander();

		void init(Unit* p_u);

		std::string m_porPath;

		void manipulateTile();
		void spawnUnit();
	};
}
