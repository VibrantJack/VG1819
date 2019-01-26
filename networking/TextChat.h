#pragma once
#include "kitten\K_Component.h"
#include "kitten\event_system\EventManager.h"
#include "_Project\StringInputDisplay.h"
#include "kitten\InputManager.h"
#include "UI\UIObject.h"
#include "UI\TriggerEventButton.h"
#include <deque>

class TextChat : public kitten::K_Component
{
private:
	std::deque<std::pair<int, std::string>> m_messageLog;
	std::deque<puppy::TextBox*> m_messageTextBoxes;

	puppy::TextBox* m_typingTextBox = nullptr;
	StringInputDisplay* m_stringInputDisplay = nullptr;
	userinterface::UIObject* m_background = nullptr;
	userinterface::TriggerEventButton* m_scrollUpButton = nullptr;
	userinterface::TriggerEventButton* m_scrollDownButton = nullptr;
	kitten::K_GameObject* m_newMessageIcon = nullptr;

	int m_messageLogIndex = 0;

	void addMessage(int p_id, const std::string& p_message);
	void setMessageTextBoxes();
	void arrangeMessageTextBoxes();
public:
	TextChat();
	~TextChat();

	virtual void start() override;

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	virtual void onEnabled() override;
	virtual void onDisabled() override;

	void receiveMessageListener(kitten::Event::EventType p_type, kitten::Event* p_data);
	void chatButtonClickedListener(kitten::Event::EventType p_type, kitten::Event* p_data);
	void chatScrollButtonListener(kitten::Event::EventType p_type, kitten::Event* p_data);
};
