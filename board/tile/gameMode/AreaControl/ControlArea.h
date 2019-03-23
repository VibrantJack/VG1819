#pragma once
#include "../GameModeManager.h"

class ControlArea : public GameModeComponent
{
public:
	ControlArea();
	~ControlArea();

	virtual void check() override;
	virtual void setProperty(nlohmann::json* p_jsonfile) override;
private:
	//point gain for each unit per turn, -1 means equal to level
	int m_pointPerUnit;
	
};
