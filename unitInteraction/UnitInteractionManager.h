/*
@Rock 10.20

UnitInteractionManager:
	This class handles the flow of all interaction between units and board.
	It will receive request from unit.
	It will assemble ability info package by highlight elements on board and ask player to make choice.
	It will then send the package to ability manager to make ability take effect.
*/

#pragma once
#include "ability/AbilityManager.h"
#include "board/BoardManager.h"
#include "unit/Unit.h"

class UnitInteractionManager
{
public:
	static void createInstance() { assert(sm_instance == nullptr); sm_instance = new UnitInteractionManager(); };
	static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
	static UnitInteractionManager * getInstance() { return sm_instance; };

	void request(unit::Unit* p_unit, unit::AbilityDescription * p_ad);

private:
	static UnitInteractionManager* sm_instance;
	UnitInteractionManager();
	~UnitInteractionManager();

	unit::AbilityDescription* m_ad;
	ability::AbilityInfoPackage* m_package;
	std::string m_abilityName;
	int m_target;
	bool m_gotTarget;

	void getTile();
	void cancel();
	void send();

	void registerEvent();
	void deregisterEvent();
	void listenEvent(kitten::Event::EventType p_type, kitten::Event* p_data);

};
