#pragma once
#include "../GameModeManager.h"

class DefendArea : public GameModeComponent
{
public:
	DefendArea();
	~DefendArea();

	virtual void check() override;
private:
};