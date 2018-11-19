#pragma once
#include "kitten\K_Component.h"
#include "puppy\Text\TextBox.h"
#include "kitten\InputManager.h"

class StringInputDisplay : public kitten::K_Component, public input::StringListener
{
private:
	puppy::TextBox* m_textBox;
	std::string m_strString;
public:
	StringInputDisplay();
	~StringInputDisplay();

	virtual void start() override;

	virtual void onStringFinished(const std::string& p_string) override;
	virtual void onStringChanged(const std::string& p_string) override;

	const std::string& getString() { return m_strString; }
};