#pragma once
#include "kitten\mouse picking\Clickable.h"

class UseAbilityWhenClicked : public kitten::Clickable
{
public:
	UseAbilityWhenClicked();
	virtual ~UseAbilityWhenClicked();

	virtual void onClick() override;
};