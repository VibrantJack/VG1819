#pragma once
#include "unit/Unit.h"

//Rock
//this component works with initiative tracker
//handles turn information
//only current unit takes turn

namespace unit
{
	class TurnChangeDisplay;
	class UnitTurn
	{
	private:
		unit::Unit* m_currentUnit;
		bool m_isEnd;
		TurnChangeDisplay* m_display;
	public:
		UnitTurn();
		~UnitTurn();

		bool move;
		bool act;

		void turnStart(kitten::K_GameObject* p_unitObj);
		void checkTurn();
		void turnEnd();
		void turnReset();

		bool isCurrent(kitten::K_GameObject* p_unitObj);
		void unitDestroyed();
		void setEnd();

		void setNewTurnDisplay(TurnChangeDisplay* p_display);
	};
}