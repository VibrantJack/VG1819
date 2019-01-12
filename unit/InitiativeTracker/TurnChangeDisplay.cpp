#include "TurnChangeDisplay.h"
#include "kitten/K_GameObjectManager.h"
#include "NewTurnMessageController.h"
unit::TurnChangeDisplay::TurnChangeDisplay()
	:m_newTurnMsg(nullptr)
{
}

unit::TurnChangeDisplay::~TurnChangeDisplay()
{
}

void unit::TurnChangeDisplay::displayNewGameTurn()
{
	if (m_newTurnMsg == nullptr)
		createMsgGO();
	m_newTurnMsg->setEnabled(true);
}

void unit::TurnChangeDisplay::displayNewUnitTurn(kitten::K_GameObject * p_unit)
{
}

void unit::TurnChangeDisplay::createMsgGO()
{
	assert(m_newTurnMsg == nullptr);
	m_newTurnMsg = kitten::K_GameObjectManager::getInstance()->createNewGameObject("new_turn_message.json");
	m_newTurnMsg->getComponent<NewTurnMessageController>()->setDisplay(this);
}
