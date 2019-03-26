#pragma once
#include "../GameModeManager.h"

class DefendArea : public GameModeComponent
{
public:
	DefendArea();
	~DefendArea();

	virtual void check() override;
	virtual void setProperty(nlohmann::json* p_jsonfile) override;
private:
	//point gain for each unit per turn, -1 means equal to level
	int m_pointPerUnit;

	//point gain for each turn
	//max point / point per turn = number of turns defender have to hold
	int m_pointPerTurn;
};