/*
@Rock 11.22

This class handles a game object of display.
The game object has 4 text box which displays min limit, max limit, current, and counter name.
It also has a quad renderable for background.
This class will listen to input and change value.
*/
#pragma once
#include "kitten/K_Common.h"
#include "puppy\Text\TextBox.h"
#include "kitten\InputManager.h"

class CounterGetter;
class CounterGetterDisplay : public kitten::K_Component
{
private:
	int m_min;
	int m_max;
	int m_current;
	std::string m_counter;
	puppy::TextBox* m_textBox;

	kitten::K_GameObject* m_maxGO;//game object handles "max limit" text box
	kitten::K_GameObject* m_minGO;//game object handles "min limit" text box
	kitten::K_GameObject* m_counterGO;//game object handles "counter name" text box

	CounterGetter* m_getter;
public:
	CounterGetterDisplay();
	~CounterGetterDisplay();

	void setGetter(CounterGetter* p_g);
	void set(int p_min, int p_max, const std::string& p_counter);
	virtual void start() override;
	virtual bool hasUpdate() const override;
	virtual void update() override;
};
