// TextChat
//
// A component that enables text chat communication between players
// Displays up to 10 messages in the window and enables scrolling through 
// a log of the 100 most recent messages
// Host messages appear yellowish and the connecting player appears as cyan
// Typing is only possible when the window is open but there is an icon that
// appears when a new message is received while the window is closed
//
// @Ken

#include "TextChat.h"

#include "kitten\K_GameObjectManager.h"
#include "networking\ClientGame.h"

#define MESSAGE_LOG_LIMIT 100
#define MESSAGE_DISPLAY_LIMIT 10
#define FONT_HEIGHT 14
#define MESSAGES_MARGIN_X 5.0f
#define MESSAGES_PADDING_Y 5.0f

#define P0_COLOR_R 255.0f / 255.0f
#define P0_COLOR_G 216.0f / 255.0f
#define P0_COLOR_B 0.0f / 255.0f
#define P1_COLOR_R 0.0f / 255.0f
#define P1_COLOR_G 230.0f / 255.0f
#define P1_COLOR_B 255.0f / 255.0f

TextChat::TextChat()
{

}

TextChat::~TextChat()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::Chat_Button_Clicked, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::TextChat_Receive_Message, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::TextChat_Scroll_Up, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::TextChat_Scroll_Down, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::Pause_Menu_Open, this);
}

void TextChat::start()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Chat_Button_Clicked,
		this,
		std::bind(&TextChat::chatButtonClickedListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::TextChat_Receive_Message,
		this,
		std::bind(&TextChat::receiveMessageListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::TextChat_Scroll_Up,
		this,
		std::bind(&TextChat::chatScrollButtonListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::TextChat_Scroll_Down,
		this,
		std::bind(&TextChat::chatScrollButtonListener, this, std::placeholders::_1, std::placeholders::_2));

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Pause_Menu_Open,
		this,
		std::bind(&TextChat::pauseMenuOpenedListener, this, std::placeholders::_1, std::placeholders::_2));

	glm::vec3 origin = getTransform().getTranslation();
	glm::vec2 scale2D = getTransform().getScale2D();

	kitten::K_GameObject* messageInput = kitten::K_GameObjectManager::getInstance()->createNewGameObject("text_chat/text_chat_input.json");
	messageInput->getTransform().setIgnoreParent(false);
	messageInput->getTransform().setParent(&getTransform());
	messageInput->getTransform().place(MESSAGES_MARGIN_X, MESSAGES_PADDING_Y + FONT_HEIGHT, 0.1f);
	m_typingTextBox = messageInput->getComponent<puppy::TextBox>();
	m_stringInputDisplay = messageInput->getComponent<StringInputDisplay>();

	m_background = kitten::K_GameObjectManager::getInstance()->createNewGameObject("text_chat/text_chat_background.json")->getComponent<userinterface::UIObject>();
	m_background->getTransform().setIgnoreParent(false);
	m_background->getTransform().setParent(&getTransform());

	kitten::K_GameObject* chatButton = kitten::K_GameObjectManager::getInstance()->createNewGameObject("text_chat/chat_button.json");
	glm::vec2 buttonScale2D = chatButton->getTransform().getScale2D();
	chatButton->getTransform().place(origin.x, origin.y - buttonScale2D.y, origin.z);

	m_newMessageIcon = kitten::K_GameObjectManager::getInstance()->createNewGameObject("text_chat/text_chat_new_message_icon.json");
	glm::vec2 iconScale = m_newMessageIcon->getTransform().getScale2D();
	m_newMessageIcon->getTransform().place(origin.x + buttonScale2D.x + 10.0f, origin.y - iconScale.y, origin.z);
	m_newMessageIcon->setEnabled(false);

	m_scrollUpButton = kitten::K_GameObjectManager::getInstance()->createNewGameObject("text_chat/text_chat_scroll_button_up.json")->getComponent<userinterface::TriggerEventButton>();
	glm::vec2 scrollButtonScale = m_scrollUpButton->getTransform().getScale2D();
	m_scrollUpButton->getTransform().scale2D(scrollButtonScale.x, scrollButtonScale.y);
	m_scrollUpButton->getTransform().place(origin.x + scale2D.x - scrollButtonScale.x, origin.y + scale2D.y - scrollButtonScale.y, origin.z + 0.1f);
	m_scrollUpButton->getGameObject().setEnabled(false);
	m_scrollUpButton->setActive(false);

	// TODO: Set as child when the ClickableFrame as child issue is fixed
	/*scrollUpButton->getTransform().scale2D(scrollButtonScale.x / scale2D.x, scrollButtonScale.y / scale2D.y);
	scrollUpButton->getTransform().place(scale2D.x - scrollButtonScale.x, scale2D.y - scrollButtonScale.y, 1.0f);
	scrollUpButton->getTransform().setIgnoreParent(false);
	scrollUpButton->getTransform().setParent(&getTransform());*/

	m_scrollDownButton = kitten::K_GameObjectManager::getInstance()->createNewGameObject("text_chat/text_chat_scroll_button_down.json")->getComponent<userinterface::TriggerEventButton>();
	m_scrollDownButton->getTransform().scale2D(scrollButtonScale.x, scrollButtonScale.y);
	m_scrollDownButton->getTransform().place(origin.x + scale2D.x - scrollButtonScale.x, origin.y + (2 * MESSAGES_PADDING_Y) + FONT_HEIGHT, origin.z + 0.1f);
	m_scrollDownButton->getGameObject().setEnabled(false);
	m_scrollDownButton->setActive(false);

	for (int i = 0; i < MESSAGE_DISPLAY_LIMIT; ++i)
	{
		puppy::TextBox* textBox = kitten::K_GameObjectManager::getInstance()->createNewGameObject("text_chat/text_chat_message_textbox.json")->getComponent<puppy::TextBox>();
		textBox->getTransform().setIgnoreParent(false);
		textBox->getTransform().setParent(&getTransform());
		textBox->setText("");
		m_messageTextBoxes.push_back(textBox);
	}
	m_messageTextBoxes.shrink_to_fit();

	arrangeMessageTextBoxes();
	m_attachedObject->setEnabled(false);
}

void TextChat::update()
{
	input::InputManager* input = input::InputManager::getInstance();
	if (input->keyDown(GLFW_KEY_ENTER) && !input->keyDownLast(GLFW_KEY_ENTER) && !m_gamePaused)
	{
		const std::string& message = m_stringInputDisplay->getString();
		addMessage(networking::ClientGame::getClientId(), message);
		networking::ClientGame::getInstance()->sendTextChatMessagePacket(message);

		// InputManager sets poll mode to true when enter is hit, set back to false to continue typing
		input->setPollMode(false);
	}

}

// Newest messages added to the back of the deque, oldest messages at the front
void TextChat::addMessage(int p_id, const std::string& p_message)
{
	std::string message = p_message;
	if (p_message.length() > MAX_TEXTCHAT_MSG_SIZE)
	{
		message = p_message.substr(0, MAX_TEXTCHAT_MSG_SIZE);
	}
	// Add message to log
	// If size > max messages, start tracking the index as size - max messages
	// The index will be the point at which to start taking messages, so the index would be oldest message
	// and incrementing by one would be a newer message
	m_messageLog.push_back(std::make_pair(p_id, message.c_str()));

	// Check if the log is full, if so, remove the oldest message
	if (m_messageLog.size() > MESSAGE_LOG_LIMIT)
	{
		m_messageLog.pop_front();
	}

	// When adding a message, if the log is bigger than the display limit, then update the index to start from
	// the most recent messages
	// This will allow the chat to automatically "scroll" down whenever a new message is typed/received and the user
	// was "scrolled" up, viewing old messages
	if (m_messageLog.size() > MESSAGE_DISPLAY_LIMIT)
	{
		m_messageLogIndex = m_messageLog.size() - MESSAGE_DISPLAY_LIMIT;
		m_scrollUpButton->setActive(true);
		m_scrollDownButton->setActive(false);
	}

	/*printf("Message Log:\n");
	for (int i = 0; i < m_messageLog.size(); ++i)
	{
		printf("\t%s\n", m_messageLog[i].second.c_str());
	}*/

	// Only update the text boxes if the chat is open
	if (m_attachedObject->isEnabled())
	{
		setMessageTextBoxes();
	}
}

void TextChat::setMessageTextBoxes()
{
	int startingIndex = m_messageLogIndex;

	if (m_messageLog.size() < MESSAGE_DISPLAY_LIMIT)
	{
		for (int i = m_messageTextBoxes.size() - m_messageLog.size(); i < m_messageTextBoxes.size(); ++i)
		{
			m_messageTextBoxes[i]->setText(m_messageLog[m_messageLogIndex].second);
			if (m_messageLog[m_messageLogIndex].first == 0)
			{
				m_messageTextBoxes[i]->setColor(P0_COLOR_R, P0_COLOR_G, P0_COLOR_B);
			}
			else if (m_messageLog[m_messageLogIndex].first == 1)
			{
				m_messageTextBoxes[i]->setColor(P1_COLOR_R, P1_COLOR_G, P1_COLOR_B);
			}
			else
			{
				m_messageTextBoxes[i]->setColor(1, 1, 1);
			}
			m_messageLogIndex++;
		}
	}
	else
	{
		for (int i = 0; i < m_messageTextBoxes.size(); ++i)
		{
			m_messageTextBoxes[i]->setText(m_messageLog[m_messageLogIndex].second);
			if (m_messageLog[m_messageLogIndex].first == 0)
			{
				m_messageTextBoxes[i]->setColor(P0_COLOR_R, P0_COLOR_G, P0_COLOR_B);
			} 
			else if (m_messageLog[m_messageLogIndex].first == 1)
			{
				m_messageTextBoxes[i]->setColor(P1_COLOR_R, P1_COLOR_G, P1_COLOR_B);
			} 
			else
			{
				m_messageTextBoxes[i]->setColor(1, 1, 1);
			}
			m_messageLogIndex++;
		}
	}

	m_messageLogIndex = startingIndex;
}

void TextChat::arrangeMessageTextBoxes()
{
	float x = getTransform().getTranslation().x;
	float y = getTransform().getScale().y - MESSAGES_PADDING_Y;
	auto end = m_messageTextBoxes.end();
	for (auto it = m_messageTextBoxes.begin(); it != end; ++it)
	{
		(*it)->getTransform().place(MESSAGES_MARGIN_X, y, 0.1f);
		y -= (FONT_HEIGHT + MESSAGES_PADDING_Y);
	}
}

void TextChat::onEnabled()
{
	m_scrollUpButton->getGameObject().setEnabled(true);
	m_scrollDownButton->getGameObject().setEnabled(true);
	m_newMessageIcon->setEnabled(false);
	setMessageTextBoxes();
}

void TextChat::onDisabled()
{
	m_typingTextBox->setText("");
	m_scrollUpButton->getGameObject().setEnabled(false);
	m_scrollDownButton->getGameObject().setEnabled(false);
}

void TextChat::receiveMessageListener(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	std::string message = p_data->getString(TEXTCHAT_MESSAGE_KEY);
	int id = p_data->getInt(PLAYER_ID);
	addMessage(id, message);

	if (!m_attachedObject->isEnabled())
	{
		m_newMessageIcon->setEnabled(true);
	}
}

void TextChat::chatButtonClickedListener(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	m_attachedObject->setEnabled(!m_attachedObject->isEnabled());
	input::InputManager::getInstance()->setPollMode(!m_attachedObject->isEnabled());
}

void TextChat::chatScrollButtonListener(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	if (p_type == kitten::Event::TextChat_Scroll_Up)
	{
		if (m_messageLogIndex - 1 >= 0)
		{
			--m_messageLogIndex;
		}
		else
		{
			m_messageLogIndex = 0;
		}
		setMessageTextBoxes();

		if (m_messageLogIndex == 0)
		{
			m_scrollUpButton->setActive(false);
		}

		printf("Scrollin up Index: %d\n", m_messageLogIndex);
	}
	else if (p_type == kitten::Event::TextChat_Scroll_Down)
	{
		if (m_messageLogIndex + 1 <= m_messageLog.size() - MESSAGE_DISPLAY_LIMIT)
		{
			++m_messageLogIndex;
		} 
		else
		{
			m_messageLogIndex = m_messageLog.size() - MESSAGE_DISPLAY_LIMIT;
		}
		setMessageTextBoxes();

		if (m_messageLogIndex == m_messageLog.size() - MESSAGE_DISPLAY_LIMIT)
		{
			m_scrollDownButton->setActive(false);
		}

		printf("Scrollin down Index: %d\n", m_messageLogIndex);
	}

	if (m_messageLogIndex < m_messageLog.size() - MESSAGE_DISPLAY_LIMIT && m_messageLogIndex >= 0)
	{
		m_scrollDownButton->setActive(true);
	}

	if (m_messageLogIndex == m_messageLog.size() - MESSAGE_DISPLAY_LIMIT && m_messageLog.size() > MESSAGE_DISPLAY_LIMIT)
	{
		m_scrollUpButton->setActive(true);
	}
}

void TextChat::pauseMenuOpenedListener(kitten::Event::EventType p_type, kitten::Event* p_data)
{
	m_gamePaused = p_data->getInt(PAUSE_MENU_OPEN);

	if (m_gamePaused && m_attachedObject->isEnabled()) // If menu opened and chat is open, disable typing
	{
		input::InputManager::getInstance()->setPollMode(true);
	}
	else if (!m_gamePaused && m_attachedObject->isEnabled()) // If menu closed and chat is open, enable typing
	{
		input::InputManager::getInstance()->setPollMode(false);
	}
}