#include "gameplay-init.h"
#include "unit/UnitTest.h"
#include "UI/HandFrame.h"
#include "kitten/K_ComponentManager.h"

void GameplayInit::start() {
	// TODO put this in a separate component or something. 
	unit::InitiativeTracker::createInstance();
	
	unit::UnitTest::getInstanceSafe()->test();

	userinterface::HandFrame::makeAHand();

	kitten::K_ComponentManager::getInstance()->destroyComponent(this);
}