#pragma once
#include "unit/UnitCommon.h"
#include "unit/unitComponent/StatusContainer.h"
#include "unit/InitiativeTracker/InitiativeTracker.h"
#include "unit/unitComponent/CooldownRecorder.h"
#include "unit/unitComponent/Commander.h"
#include "unit/unitComponent/CastTimer.h"

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
		CooldownRecorder * m_cdRecorder;
		CastTimer * m_castTimer;
		Commander * m_commander;

		std::vector<kitten::K_GameObject*> m_path;

		bool lateDestroy = false;
		AbilityDescription m_joinAD;
	public:
		std::string m_ID;
		std::vector<std::string> m_tags;
		std::string m_name;
		std::unordered_map<std::string, int> m_attributes;//attributes includes all numerical attribute and counter
		UnitSize m_size;

		std::unordered_map<std::string, unit::AbilityDescription*> m_ADList;
		int m_clientId;

		Unit();
		~Unit();

		//level up
		void setJoinAD();
		void join();
		void levelup();
		
		//commander interface
		void addCommander(Commander* p_c);
		bool isCommander();
		void manipulateTile();
		void summonUnit();
		//status interface
		/*
		void addStatus(ability::Status *p_newStatus);
		bool removeStatus(ability::Status *p_oldStatus);
		ability::Status* getStatus(const std::string& p_name);*/
		StatusContainer* getStatusContainer();
		//trigger event
		void triggerTP(ability::TimePointEvent::TPEventType p_tp, ability::TimePointEvent* p_event = nullptr);
		//turn interface
		void turnStart(UnitTurn* p_t);
		bool canMove();
		bool canAct();
		void moveDone();
		void actDone();
		bool isTurn();
		void turnEnd();
		void playerSkipTurn();
		//position function
		kitten::K_GameObject* getTile();
		//move
		void move();//move action, no restriction, no info needs
		void move(int p_min, int p_max);//move by ability, need range of ability
		void move(kitten::K_GameObject* p_tile);//move to a specific tile by ability
		void move(std::vector<kitten::K_GameObject*> p_path);

		//ability
		int useAbility(const std::string& p_abilityName);
		void cancelAbility(AbilityDescription* p_ad);
		void setCast(AbilityDescription* p_ad, ability::AbilityInfoPackage* p_pack);
		void cancelCast();

		//destroy
		int destroyedByDamage();
		int destroyedByJoin();
		void destroy();
	};
}
