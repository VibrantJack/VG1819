#pragma once

#include "kitten\K_Component.h"
#include "puppy\Text\TextBox.h"
#include "UI\UIObject.h"
#include "kitten\event_system\EventManager.h"

class PowerTracker : public kitten::K_Component
{
public:
	PowerTracker();
	~PowerTracker();

	void start() override;
	void updateTextBox();

	void increaseMaxPower(int p_iAmount = 1);
	void increaseMaxPowerEvent(kitten::Event::EventType p_type, kitten::Event* p_data);
	bool summonUnitCost(int p_iCost);
	void resetCurrent();
	void resetEvent(kitten::Event::EventType p_type, kitten::Event* p_data);
	bool changeCurrentPower(int p_iAmount = 0);

	int getMaxPower();
	int getCurrentPower();	

private:
	int m_iMaxPower;
	int m_iCurrentPower;

	puppy::TextBox* m_textBox;
	userinterface::UIObject* m_powerIcon;
};