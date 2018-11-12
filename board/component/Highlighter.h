/*Rock 10.18

This class can highlight or unHighlight tiles on the board.

Done by Ken.
Move it from BoardCreator

*/

#pragma once
#include "kitten/K_GameObject.h"
#include "kitten/K_Component.h"
#include "kitten/event_system/EventManager.h"
#include "board/tile/TileInfo.h"

class Highlighter : public kitten::K_Component
{
public:
	Highlighter();
	~Highlighter();

	virtual bool hasUpdate() const;

	virtual void start() override;
	virtual void update() override;

	void highlightTile(TileInfo::HighlightType p_type, kitten::Event::TileList p_list);
	void unhighlightAll(TileInfo::HighlightType p_type);
	//void unHighlightCurrent();

private:
	std::unordered_map<TileInfo::HighlightType, std::string> m_texMap;
	std::vector<kitten::K_GameObject*> m_toBeChanged;
	std::unordered_map<TileInfo::HighlightType, std::vector<kitten::K_GameObject*>> m_listForType;

	/*
	kitten::Event::TileList m_toBeHighlighted;
	kitten::Event::TileList m_lastHighlighted;
	kitten::Event::TileList m_toBeUnhighlighted;
	*/

	std::string m_sHighlightedBy;
};