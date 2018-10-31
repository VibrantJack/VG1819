#pragma once
#include "unit/Unit.h"

//@Rock

namespace unit
{
	class Commander : public unit::Unit
	{
	public:
		Commander();
		~Commander();

		void init();

		std::string m_porPath;
		unit::AbilityDescription* m_adTile;
		unit::AbilityDescription* m_adSpawn;

		void manipulateTile();
		void spawnUnit();
	};
}
