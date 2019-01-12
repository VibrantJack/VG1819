#include "TurnChangeDisplay.h"
#include "kitten/K_GameObjectManager.h"
#include "NewTurnMessageController.h"
#include "kitten/event_system/EventManager.h"

unit::TurnChangeDisplay::TurnChangeDisplay()
	:m_newTurnMsg(nullptr)
{
}

unit::TurnChangeDisplay::~TurnChangeDisplay()
{
}

void unit::TurnChangeDisplay::displayNewGameTurn()
{
	resetCamera();

	if (m_newTurnMsg == nullptr)
		createMsgGO();

	m_newTurnMsg->setEnabled(true);
}

void unit::TurnChangeDisplay::displayNewUnitTurn(kitten::K_GameObject * p_unit)
{
	//if new game turn message is showing, don't move camera
	if (m_newTurnMsg->isEnabled())
		return;

	//get transform of unit
	float posX = p_unit->getTransform().getTranslation().x;
	float posZ = p_unit->getTransform().getTranslation().z;

	kitten::Event* e = new kitten::Event(kitten::Event::Move_Camera);
	e->putFloat(CAM_FOV, DEFAULT_CAMERA_FOV);
	e->putFloat(POSITION_X, posX);
	e->putFloat(POSITION_Z, posZ-CAMERA_Z_OFFSET);
	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Move_Camera, e);
}

void unit::TurnChangeDisplay::createMsgGO()
{
	assert(m_newTurnMsg == nullptr);
	m_newTurnMsg = kitten::K_GameObjectManager::getInstance()->createNewGameObject("new_turn_message.json");
	m_newTurnMsg->getComponent<NewTurnMessageController>()->setDisplay(this);
}

void unit::TurnChangeDisplay::resetCamera()
{
	kitten::Event* e = new kitten::Event(kitten::Event::Move_Camera);
	e->putFloat(CAM_FOV, DEFAULT_CAMERA_FOV);
	e->putFloat(POSITION_X, DEFAULT_CAMERA_POS_X);
	e->putFloat(POSITION_Z, DEFAULT_CAMERA_POS_Z);
	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Move_Camera, e);
}
