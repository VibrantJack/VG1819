#pragma once

#include "kitten\K_Component.h"
#include "puppy\Text\TextBox.h"

class PowerTracker : public kitten::K_Component
{
public:
	PowerTracker();
	~PowerTracker();

	void start() override;

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	void increaseMaxPower(int p_iAmount = 1);
	bool summonUnitCost(int p_iCost);
	void resetCurrent();

	int getMaxPower();
	int getCurrentPower();	

private:
	int m_iMaxPower;
	int m_iCurrentPower;

	puppy::TextBox* m_textBox;
};