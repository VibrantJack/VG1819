#pragma once
#include "unit/UnitCommon.h"
//Rock
//This class contain infomation about unit's position
//It handles the unit's move function

namespace unit
{
	class UnitMove : public kitten::K_Component
	{
	private:
		kitten::K_GameObject* m_tile;

		void registerListener();
	public:
		UnitMove();
		~UnitMove();

		void attempToMove();
		void move(kitten::K_GameObject* p_targetTile);

	};
}