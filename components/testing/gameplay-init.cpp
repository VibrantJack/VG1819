#include "gameplay-init.h"
#include "unit/UnitTest.h"
#include "UI/HandFrame.h"
#include "kitten/K_ComponentManager.h"

GameplayInit::GameplayInit(bool p_testing)
{ 
	m_testing = p_testing; 
}

void GameplayInit::start() {
	// TODO put this in a separate component or something. 
	unit::InitiativeTracker::createInstance();
	
	if (m_testing)
		unit::UnitTest::getInstanceSafe()->test();

	userinterface::HandFrame::makeAHand();

	kitten::K_ComponentManager::getInstance()->destroyComponent(this);
}