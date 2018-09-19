#pragma once
#include "ability/AbilityInfoPackage.h"
#include "ability/node/AbilityNodeManager.h"

#include <string>
#include <map>
#include <vector>

//Rock

namespace ability
{
	class Ability
	{
	public:
		Ability() {};
		~Ability() {};

		std::string m_name;
		std::string m_description;//the text that will be showed to player

		virtual int effect(const AbilityInfoPackage* p_info) = 0;
	};
}


