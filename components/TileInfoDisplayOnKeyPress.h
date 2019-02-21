#pragma once
#include "kitten\K_Component.h"
#include "kitten\InputManager.h"
#include "puppy\Text\TextBox.h"

class TileInfoDisplayOnKeyPress : public kitten::K_Component
{
private:
	char m_key;
	input::InputManager* m_inputMan;
	puppy::TextBox* m_tileInfoDisplay;

public:
	TileInfoDisplayOnKeyPress(char p_key);
	TileInfoDisplayOnKeyPress(nlohmann::json & p_json);
	~TileInfoDisplayOnKeyPress();

	bool hasUpdate() const override { return true; };

	void start() override;
	void update() override;

};