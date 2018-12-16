/*
@Rock 12.15
This class will be a component of cursor object.
It disable windows cursor and handles cursor movement.
*/

#pragma once
#include "kitten/K_Common.h"
#include "kitten\InputManager.h"

class CustomCursor : public kitten::K_Component
{
private:
	std::pair<int, int> m_offset;

	int m_lastX;
	int m_lastY;

	input::InputManager* m_inputMan;
public:
	CustomCursor(int p_x=0, int p_y=0);
	~CustomCursor();

	void start() override;
	bool hasUpdate() const override;
	void update() override;

	void onEnabled() override;
	void onDisabled() override;
};