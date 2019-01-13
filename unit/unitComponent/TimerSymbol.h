/*@Rock 1.13
This class is component of timer.
It controls which texture to display.
*/

#pragma once
#include "kitten/K_Common.h"
#include "UI/UIObject.h"

namespace unit
{
	class TimerSymbol : public kitten::K_Component
	{
	public:
		TimerSymbol();
		~TimerSymbol();

		void addTexture(int p_num, const std::string& p_texPath);

		void changeTexture(int p_num);

		void start() override;
	private:
		std::vector<std::string> m_timeTex;
		userinterface::UIObject* m_ui;
	};
}