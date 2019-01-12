/*Rock 1.11
This class will display message to show that turn is changed
*/

#pragma once
#include "unit/InitiativeTracker/UnitTurn.h"
#include "kitten/K_GameObject.h"
#include "unit/InitiativeTracker/UnitAura.h"

namespace unit
{
	class TurnChangeDisplay
	{
	public:
		TurnChangeDisplay();
		virtual ~TurnChangeDisplay();

		void displayNewGameTurn();
		void displayNewUnitTurn();
	private:
	};
}
