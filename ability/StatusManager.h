#pragma once
#include "AbilityInfoPackage.h"
#include "ability/Ability.h"
#include "status/Status.h"
#include "unit/UnitCommon.h"

#include <vector>
#include <assert.h>

//Rock

namespace ability
{
	class StatusManager
	{
	private:
		static StatusManager * sm_instance;

		std::vector<Status*> m_statusList;

		void init();

	public:
		StatusManager();
		~StatusManager();

		static void createInstance();
		static void destroyInstance();
		static StatusManager* getInstance();

		Status * findStatus(const std::string & p_name);
	};
}