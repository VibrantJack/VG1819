/*Rock 1.11
This class will display message to show that turn is changed
*/

#pragma once
#include "kitten/K_Common.h"

#define DEFAULT_CAMERA_FOV 45
#define DEFAULT_CAMERA_POS_X 7
#define DEFAULT_CAMERA_POS_Z 0

//Trigonometry
//camera angle is 20 degree
//the y value is 13
//so z should be 4.73
#define CAMERA_Z_OFFSET 4.73

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

		void resetCamera();

	};
}
