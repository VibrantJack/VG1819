#pragma once
#include "../GameModeManager.h"

class ControlArea : public GameModeComponent
{
public:
	ControlArea();
	~ControlArea();

	virtual void check() override;

private:
};
