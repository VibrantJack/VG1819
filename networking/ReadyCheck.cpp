// ReadyCheck
//
// Provides a ready check for players and starts the game when all players are ready; after the game 
// has started, this component and attached GO is destroyed
// Displays appropriate messages according to the current state of the ReadyCheck
// 
// Events: receives Ready_Button_Clicked from attached TriggerEventButton to send ready packet to server;
//		receives Player_Joined from ClientGame to update message and enable the Ready button
//		receives Players_Ready from ClientGame to start countdown and then start the game
//
// @Ken

#include "ReadyCheck.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_Time.h"
#include "kitten\K_ComponentManager.h"
#include "networking/ClientGame.h"
#include "unit/InitiativeTracker/InitiativeTracker.h"

#define JOIN_WAITING_MESSAGE_0 "Waiting for players."
#define JOIN_WAITING_MESSAGE_1 "Waiting for players.."
#define JOIN_WAITING_MESSAGE_2 "Waiting for players..."

#define READY_WAITING_ALL_MESSAGE_0 "Waiting for players to ready up."
#define READY_WAITING_ALL_MESSAGE_1 "Waiting for players to ready up.."
#define READY_WAITING_ALL_MESSAGE_2 "Waiting for players to ready up..."

#define READY_WAITING_OTHER_MESSAGE_0 "Waiting for other player to ready up."
#define READY_WAITING_OTHER_MESSAGE_1 "Waiting for other player to ready up.."
#define READY_WAITING_OTHER_MESSAGE_2 "Waiting for other player to ready up..."

#define STARTING_MESSAGE_0 "Starting Game in ... 3"
#define STARTING_MESSAGE_1 "Starting Game in ... 2"
#define STARTING_MESSAGE_2 "Starting Game in ... 1"

#define MESSAGE_CHANGE_DELAY 0.5f

#define READY_BUTTON_SCALE_X 150.0f
#define READY_BUTTON_SCALE_Y 48.0f

ReadyCheck::ReadyCheck(const char* p_pathToTex) : UIElement(p_pathToTex)
{

}

ReadyCheck::ReadyCheck(const char* p_pathToTex, pivotType p_pivot, textureBehaviour p_texBehaviour) : UIElement(p_pathToTex, p_pivot, p_texBehaviour)
{
	
}

ReadyCheck::~ReadyCheck()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::Players_Ready, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::Player_Joined, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::Ready_Button_Clicked, this);
}

void ReadyCheck::start()
{
	UIElement::start();

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Players_Ready,
		this,
		std::bind(&ReadyCheck::playersReadyListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Player_Joined,
		this,
		std::bind(&ReadyCheck::playerJoinedListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Ready_Button_Clicked,
		this,
		std::bind(&ReadyCheck::readyButtonClicked, this, std::placeholders::_1, std::placeholders::_2));

	kitten::K_GameObjectManager* gom = kitten::K_GameObjectManager::getInstance();

	m_textbox = gom->createNewGameObject("UI/ready_check/ready_check_textbox.json")->getComponent<puppy::TextBox>();
	m_textbox->getTransform().setIgnoreParent(false);
	m_textbox->getTransform().setParent(&getTransform());
	m_textbox->setText(JOIN_WAITING_MESSAGE_0);

	glm::vec3 pos = getTransform().getTranslation();
	glm::vec3 scale = getTransform().getScale();
	float textBoxWidth = m_textbox->getBoxWidth();
	float textboxHeight = m_textbox->getBoxHeight();
	m_textbox->getTransform().place(20.0f, (scale.y / 2) + (textboxHeight / 2), 0.01f);

	m_readyButton = gom->createNewGameObject("UI/ready_check/ready_button.json")->getComponent<userinterface::TriggerEventButton>();
	m_readyButton->getTransform().setIgnoreParent(false);
	m_readyButton->getTransform().setParent(&getTransform());
	m_readyButton->setActive(false);
	m_readyButton->getTransform().scale2D(READY_BUTTON_SCALE_X / scale.x, READY_BUTTON_SCALE_Y / scale.y);
	m_readyButton->getTransform().place((scale.x - READY_BUTTON_SCALE_X) - 20.0f, (scale.y / 2) - (READY_BUTTON_SCALE_Y / 2), 0.01f);

	m_messages[0] = JOIN_WAITING_MESSAGE_0;
	m_messages[1] = JOIN_WAITING_MESSAGE_1;
	m_messages[2] = JOIN_WAITING_MESSAGE_2;

	m_lerpController = m_attachedObject->getComponent<LerpController>();
	m_lerpController->addPositionLerpFinishedCallback(this);
}

void ReadyCheck::update()
{
	if (m_update)
	{
		m_timeElapsed += kitten::K_Time::getInstance()->getDeltaTime();

		if (m_timeElapsed > MESSAGE_CHANGE_DELAY)
		{
			m_timeElapsed = 0.0f;
			m_messageIndex = (m_messageIndex + 1) % 3;
			m_textbox->setText(m_messages[m_messageIndex]);
		}
	}

	if (m_startGame)
	{
		m_timeElapsed -= kitten::K_Time::getInstance()->getDeltaTime();

		if (m_timeElapsed < 0.0f)
		{
			glm::vec3 pos = getTransform().getTranslation();
			m_lerpController->positionLerp(glm::vec3(pos.x, pos.y - getTransform().getScale().y, pos.z), 1.0f);
			unit::InitiativeTracker::getInstance()->gameTurnStart();
			m_startGame = false;
		}
		if (m_timeElapsed < 1.0f)
		{
			m_textbox->setText("Starting Game!");
		}
		else if (m_timeElapsed < 2.0f)
		{
			m_textbox->setText(STARTING_MESSAGE_2);
		}
		else if (m_timeElapsed < 3.0f)
		{
			m_textbox->setText(STARTING_MESSAGE_1);
		}
	}
}

void ReadyCheck::playersReadyListener(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	m_update = false;
	m_startGame = true;
	m_timeElapsed = 4.0f;
	m_textbox->setText(STARTING_MESSAGE_0);
}

void ReadyCheck::playerJoinedListener(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	m_messages[0] = READY_WAITING_ALL_MESSAGE_0;
	m_messages[1] = READY_WAITING_ALL_MESSAGE_1;
	m_messages[2] = READY_WAITING_ALL_MESSAGE_2;

	m_readyButton->setActive(true);
}

void ReadyCheck::readyButtonClicked(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	m_readyButton->setActive(false);
	networking::ClientGame::getInstance()->sendBasicPacket(READY_CHECK);

	m_messages[0] = READY_WAITING_OTHER_MESSAGE_0;
	m_messages[1] = READY_WAITING_OTHER_MESSAGE_1;
	m_messages[2] = READY_WAITING_OTHER_MESSAGE_2;
}

void ReadyCheck::onPositionLerpFinished()
{
	kitten::K_GameObjectManager::getInstance()->destroyGameObject(m_attachedObject);
}