#pragma once
#include "Ability.h"

//Rock

namespace ability
{
	class Heal : public Ability
	{
	public:
		Heal();

		int effect(const AbilityInfoPackage* p_info);
	};
}
