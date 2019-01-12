/*Rock 1.11
This class will display message to show that turn is changed
*/

#pragma once
#include "kitten/K_Common.h"

namespace unit
{
	class TurnChangeDisplay
	{
	public:
		TurnChangeDisplay();
		virtual ~TurnChangeDisplay();

		void displayNewGameTurn();
		void displayNewUnitTurn(kitten::K_GameObject* p_unit);
	private:
		kitten::K_GameObject* m_newTurnMsg;

		void createMsgGO();
	};
}
