// SpawnUnitOnKeyPress
//
// Used to spawn a unit on a key press to test with networking code
// 
// @Ken

#pragma once
#include "kitten\K_Component.h"
#include "networking\ClientGame.h"
#include "puppy\Text\TextBox.h"
#include "_Project\StringInputDisplay.h"
#include "kitten\InputManager.h"
#include "kitten\event_system\EventManager.h"

class SpawnUnitOnKeyPress : public kitten::K_Component
{
public:
	SpawnUnitOnKeyPress();
	~SpawnUnitOnKeyPress();

	virtual void start() override;

	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	void getTileListener(kitten::Event::EventType p_type, kitten::Event* p_event);
private:
	bool m_bUnitsSpawned, m_bGameStarted;

	bool m_unitIdEntered, m_tileDataReceived;
	bool m_initialUnitsSpawned;
	bool m_bEnteringData;
	int m_summonUnitId, m_summonTileX, m_summonTileY;

	puppy::TextBox* m_textBox;
	StringInputDisplay* m_stringInputDisplay;
	input::InputManager* m_inputMan;

	void summonAllUnits();
};