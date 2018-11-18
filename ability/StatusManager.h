#pragma once
#include "AbilityInfoPackage.h"
#include "ability/Ability.h"
#include "status/Status.h"
#include "unit/UnitCommon.h"

#include <vector>
#include <assert.h>

#define STATUS_ENCOURAGE "Status_Encourage"
#define STATUS_LV "Status_LV"
#define STATUS_PRIEST_LV3 "Status_Priest_LV3"
#define STATUS_ARCHER_LV3 "Status_Archer_LV3"
#define STATUS_DUELIST_LV3 "Status_Duelist_LV3"
#define STATUS_DODGE "Status_Dodge"
#define STATUS_TEMP_CHANGE "Status_Temp_Change"
//Rock

namespace ability
{
	class StatusManager
	{
	private:
		static StatusManager * sm_instance;

		std::unordered_map<std::string, Status*> m_statusList;

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