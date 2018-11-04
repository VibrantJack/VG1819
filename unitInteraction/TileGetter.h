/*
@Rock 10.24

TileGetter:
	This is a component of Unit Interaction Manager.
	It trigger highlight event and get response.
	It will send Manager tileGO as required.
*/

#pragma once
#include "unitInteraction/UnitInteractionManager.h"

class TileGetter
{
public:
	TileGetter();
	~TileGetter();

	void requireTile(unit::AbilityDescription* p_ad, unit::Unit* p_source, bool p_needUnit);
private:
	unit::Unit* m_source;
	unit::AbilityDescription* m_ad;

	std::vector<kitten::K_GameObject*> m_tileList;
	std::vector<unit::Unit*> m_unitList;

	bool m_reg;
	bool m_respond;
	bool m_needUnit;
	int m_targetNum;//number of times that player need to click on

	void registerEvent();
	void deregisterEvent();
	void listenEvent(kitten::Event::EventType p_type, kitten::Event* p_data);

	void getTiles(kitten::Event * p_data);
	void getUnit(kitten::K_GameObject* p_tile);

	void triggerHighlightEvent();
	void putRange(kitten::Event* e);
	void putFilter(kitten::Event* e);
	void triggerUnhighlightEvent();

	void send();
	void cancel();

};
