#include "TrackerBlockClickable.h"
#include "kitten/K_Common.h"
#include "board/tile/TileInfo.h"
#include <iostream>
namespace unit
{
	TrackerBlockClickable::TrackerBlockClickable() : m_unit(nullptr)
	{
	}

	TrackerBlockClickable::TrackerBlockClickable(nlohmann::json & p_json) : kitten::ClickableUI(p_json),
		m_unit(nullptr)
	{
	}

	TrackerBlockClickable::~TrackerBlockClickable()
	{
	}

	void TrackerBlockClickable::onClick()
	{
		//std::cout << "Block CLICKED..........." << std::endl;
	}

	void TrackerBlockClickable::onHoverStart()
	{
		if (m_unit != nullptr)
		{
			kitten::Event* updateContextEvent = new kitten::Event(kitten::Event::Update_Card_Context_By_GO);
			updateContextEvent->putGameObj(UPDATE_CARD_CONTEXT_KEY, m_unit);
			kitten::EventManager::getInstance()->queueEvent(kitten::Event::Update_Card_Context_By_GO, updateContextEvent);

			// Enable Card Context
			kitten::Event* enableContextEvent = new kitten::Event(kitten::Event::Card_Context_Set_Enabled);
			enableContextEvent->putInt(CARD_CONTEXT_SET_ENABLED_KEY, TRUE);
			kitten::EventManager::getInstance()->queueEvent(kitten::Event::Card_Context_Set_Enabled, enableContextEvent);
		}

		//highlight unit
		kitten::K_GameObject* tile = m_unit->getComponent<unit::Unit>()->getTile();
		kitten::Event::TileList* list = new kitten::Event::TileList();
		list->push_back(tile->getComponent<TileInfo>()->getPos());

		kitten::Event* highlightUnitEvent = new kitten::Event(kitten::Event::Highlight_Tile_With_List);
		highlightUnitEvent->putTileList(list);
		kitten::EventManager::getInstance()->queueEvent(kitten::Event::Highlight_Tile_With_List, highlightUnitEvent);
	}

	void TrackerBlockClickable::onHoverEnd()
	{
		kitten::Event* enableContextEvent = new kitten::Event(kitten::Event::Card_Context_Set_Enabled);
		enableContextEvent->putInt(CARD_CONTEXT_SET_ENABLED_KEY, FALSE);
		kitten::EventManager::getInstance()->queueEvent(kitten::Event::Card_Context_Set_Enabled, enableContextEvent);

		//unhighlight
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Unhighlight_Tile, nullptr);
	}

	void TrackerBlockClickable::onPause()
	{
		kitten::Event* enableContextEvent = new kitten::Event(kitten::Event::Card_Context_Set_Enabled);
		enableContextEvent->putInt(CARD_CONTEXT_SET_ENABLED_KEY, FALSE);
		kitten::EventManager::getInstance()->queueEvent(kitten::Event::Card_Context_Set_Enabled, enableContextEvent);

		//unhighlight
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Unhighlight_Tile, nullptr);
	}

	//DEPRECATED METHOD
	void TrackerBlockClickable::setTextBox(kitten::K_GameObject * p_txt)
	{
		//m_txtGO = p_txt;
		//m_txtGO->setEnabled(false);
	}
	
	void TrackerBlockClickable::setUnit(kitten::K_GameObject* p_unit)
	{
		m_unit = p_unit;
	}
}
