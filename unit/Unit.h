#pragma once
#include "unit/UnitCommon.h"
#include "unit/unitComponent/StatusContainer.h"
#include "unit/InitiativeTracker/InitiativeTracker.h"

//@Rock
//although unit is just a component of game object
//it acts like central system which pass commands to other components

namespace unit
{
	class UnitTurn;
	class Unit : public kitten::K_Component
	{
	private:
		UnitTurn* m_turn;
		StatusContainer * m_statusContainer;
	public:
		std::string m_ID;
		std::vector<std::string> m_tags;
		std::string m_name;
		std::unordered_map<std::string, int> m_attributes;//attributes includes all numerical attribute and counter
		UnitSize m_size;

		std::unordered_map<std::string, unit::AbilityDescription*> m_ADList;

		Unit();
		~Unit();

		//status interface
		void addStatus(ability::Status *p_newStatus);
		bool removeStatus(ability::Status *p_oldStatus);
		ability::Status* getStatus(const std::string& p_name);
		StatusContainer* getStatusContainer();

		//turn interface
		void turnStart(UnitTurn* p_t);
		bool canMove();
		bool canAct();
		void moveDone();
		void actDone();
		bool isTurn();
		void turnEnd();

		//position function
		kitten::K_GameObject* getTile();

		int useAbility(const std::string& p_abilityName);
		//int callStatus(int p_StatusIndex, int p_event);
		//event is the one of the events that this status registered
		//should be enum, I didn't define it yet, so use int as place holder

		int destroyedByDamage();
	};
}


