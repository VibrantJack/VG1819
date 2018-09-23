#pragma once
#include "unit/UnitCommon.h"
#include "unit/unitComponent/AbilityDescription.h"
#include "unit/unitComponent/StatusContainer.h"

//@Rock

namespace unit
{
	enum UnitSize;
	class Unit : public kitten::K_Component
	{
	private:
		StatusContainer * m_statusContainer;
	public:
		std::string m_ID;
		std::vector<std::string> m_tags;
		std::string m_name;
		std::map<std::string, int> m_attributes;//attributes includes all numerical attribute and counter
		UnitSize m_size;

		std::vector<unit::AbilityDescription*> m_abilityDescription;

		Unit();
		~Unit();

		void addStatus(ability::Status *p_newStatus);
		bool removeStatus(ability::Status *p_oldStatus);

		StatusContainer* getStatus();

		int useAbility(int p_abilityIndex);

		int callStatus(int p_StatusIndex, int p_event);
		//event is the one of the events that this status registered
		//should be enum, I didn't define it yet, so use int as place holder

		int destroyedByDamage();
	};
}


