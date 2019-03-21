#pragma once
#include "../GameModeManager.h"

class ItemKeepArea : public GameModeComponent
{
public:
	ItemKeepArea();
	~ItemKeepArea();

	virtual void check() override;
private:
};