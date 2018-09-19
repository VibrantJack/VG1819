#pragma once
#include "Ability.h"

class Heal : public Ability
{
public:
	Heal();

	int effect(const AbilityInfoPackage* p_info);
};