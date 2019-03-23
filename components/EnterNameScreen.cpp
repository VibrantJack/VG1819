#include "EnterNameScreen.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\event_system\EventManager.h"
#include "networking\ClientGame.h"
#include "kitten\InputManager.h"
#include "kitten\K_Instance.h"

EnterNameScreen::EnterNameScreen(int p_nameMinLimit, int p_nameMaxLimit) 
	: 
	m_nameMinLimit(p_nameMinLimit),
	m_nameMaxLimit(p_nameMaxLimit)
{

}

EnterNameScreen::~EnterNameScreen()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Scene_Change, this);
	input::InputManager::getInstance()->setPollMode(true);
}

void EnterNameScreen::start()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Scene_Change,
		this,
		std::bind(&EnterNameScreen::sceneChangeListener, this, std::placeholders::_1, std::placeholders::_2));

	m_stringInputDisplay = m_attachedObject->getComponent<StringInputDisplay>();
	m_stringInputDisplay->setCharLimit(m_nameMaxLimit);

	m_inputTextbox = m_attachedObject->getComponent<puppy::TextBox>();

	kitten::K_GameObject* nameStatus = kitten::K_GameObjectManager::getInstance()->createNewGameObject("enter_name_status_textbox.json");
	m_nameStatusTextBox = nameStatus->getComponent<puppy::TextBox>();
	m_nameStatusTextBox->getGameObject().getTransform().setParent(&m_attachedObject->getTransform());

	kitten::K_GameObject* confirmButtonGO = kitten::K_GameObjectManager::getInstance()->createNewGameObject("UI/name_confirm_button.json");
	m_confirmButton = confirmButtonGO->getComponent<userinterface::ClickableButton>();
	m_confirmButtonFrame = confirmButtonGO->getComponent<kitten::ClickableFrame>();

	input::InputManager::getInstance()->setPollMode(false);
}

void EnterNameScreen::update()
{
	int nameLength = m_inputTextbox->getText().length();
	if (nameLength < m_nameMinLimit || nameLength > m_nameMaxLimit)
	{
		setConfirmButtonEnabled(false);
		m_nameStatusTextBox->setText("Name should be between " + std::to_string(m_nameMinLimit) 
			+ " and " + std::to_string(m_nameMaxLimit) + " characters.");
	}
	else
	{
		setConfirmButtonEnabled(true);
		m_nameStatusTextBox->setText("");
	}

	// Resets poll mode if the user hits enter
	input::InputManager* inputMan = input::InputManager::getInstance();
	if (inputMan->keyDown(GLFW_KEY_ENTER) && !inputMan->keyDownLast(GLFW_KEY_ENTER))
	{
		std::string name = m_stringInputDisplay->getString();
		if (name.length() >= m_nameMinLimit && name.length() <= m_nameMaxLimit)
		{
			kitten::K_Instance::changeScene(DECK_MENU_SCENE);
		}
		else
		{
			inputMan->setPollMode(false);
		}
	}
}

void EnterNameScreen::sceneChangeListener(kitten::Event::EventType p_type, kitten::Event* p_event)
{
	std::string scene = p_event->getString(NEXT_SCENE_PATH_KEY);

	if (scene == DECK_MENU_SCENE)
	{
		networking::ClientGame::setPlayerName(m_stringInputDisplay->getString());
	}
}

void EnterNameScreen::setConfirmButtonEnabled(bool p_enabled)
{
	m_confirmButton->setActive(p_enabled);
	m_confirmButtonFrame->setEnabled(p_enabled);
}