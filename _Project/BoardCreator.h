#pragma once
#include "kitten\K_Component.h"
#include "kitten\K_GameObject.h"
#include "kitten\event_system\EventManager.h"
#include "_Project/Range.h"
#include <vector>
#include <array>

class BoardCreator : public kitten::K_Component
{
public:
	BoardCreator();
	~BoardCreator();

	virtual bool hasUpdate() const;

	virtual void start() override;
	virtual void update() override;

	void highlightTile(kitten::Event::EventType p_type, kitten::Event* p_data);
	void unhighlightTiles(kitten::Event::EventType p_type, kitten::Event* p_data);
	void unhighlightCurrent(kitten::Event::EventType p_type, kitten::Event* p_data);

	static kitten::K_GameObject* getTile(int x, int z);
private:
	static kitten::K_GameObject* m_pTileList[15][15];
	
	kitten::Event::TileList m_toBeHighlighted;
	kitten::Event::TileList m_lastHighlighted;
	kitten::Event::TileList m_toBeUnhighlighted;

	std::string m_sHighlightedBy;
};