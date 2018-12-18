#pragma once

#include "kitten\K_Component.h"

class MainMenuBoard : public kitten::K_Component
{
private:

public:
	MainMenuBoard();
	~MainMenuBoard();

	virtual void start() override;
};