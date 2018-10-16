#pragma once
#include "kitten/K_Component.h"

class PlaySoundOnStart : public kitten::K_Component
{
public:
	PlaySoundOnStart();
	~PlaySoundOnStart();

	void start() override;
};