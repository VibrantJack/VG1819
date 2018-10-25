// SpawnUnitOnKeyPress
//
// Used to spawn a unit on a key press to test with networking code
// 
// @Ken

#pragma once
#include "kitten\K_Component.h"
#include "ability\AbilityManager.h"

class SpawnUnitOnKeyPress : public kitten::K_Component
{
public:
	SpawnUnitOnKeyPress();
	~SpawnUnitOnKeyPress();

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;
};