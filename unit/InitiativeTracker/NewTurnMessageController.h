/*Rock 1.12
Component of new turn message window. 
This class control how long the window will display.
And camera focus.
*/

#pragma once
#include "kitten/K_Common.h"
#include "puppy/Text/TextBox.h"
namespace unit
{
	class TurnChangeDisplay;
	class NewTurnMessageController : public kitten::K_Component
	{
	public:
		NewTurnMessageController(float p_time);
		virtual ~NewTurnMessageController();

		void setDisplay(TurnChangeDisplay* p_display);

		//void start() override;
		bool hasUpdate() const override;
		void update() override;
		void onEnabled() override;
		void onDisabled() override;

	private:
		float m_time;//time the window will last
		bool m_show;
		double m_currentTime;
		
		TurnChangeDisplay* m_display;
	};
}
