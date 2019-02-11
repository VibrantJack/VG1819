#include "DeckCountTextureBind.h"
#include "kitten/event_system/EventManager.h"
#include "UI/UIFrame.h"

void DeckCountTextureBind::deckEventReceiver(kitten::Event::EventType p_type, kitten::Event * p_data)
{
	int deckCount = p_data->getInt(DECK_CARD_COUNT_LEFT);
	if (m_deckCount > deckCount)
	{
		if (m_currentTexPair->first > deckCount)
		{
			while (m_currentTexPair->first > deckCount)
			{
				m_currentTexPair++;
			}
			m_attachedObject->getComponent<userinterface::UIFrame>()->setTexture(m_currentTexPair->second.c_str());
		}
	}

	m_deckCount = deckCount;
}

void DeckCountTextureBind::start()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Card_Drawn,
		this,
		std::bind(&DeckCountTextureBind::deckEventReceiver, this, std::placeholders::_1, std::placeholders::_2));
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Card_Discarded,
		this,
		std::bind(&DeckCountTextureBind::deckEventReceiver, this, std::placeholders::_1, std::placeholders::_2));

	m_currentTexPair = m_texPairs.rbegin();
	m_attachedObject->getComponent<userinterface::UIFrame>()->setTexture(m_currentTexPair->second.c_str());
}

void DeckCountTextureBind::addTexPair(int p_atCount, const std::string& p_tex)
{
	m_texPairs[p_atCount] = p_tex;
}

DeckCountTextureBind::DeckCountTextureBind()
{
}

DeckCountTextureBind::~DeckCountTextureBind()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Card_Drawn, this);
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Card_Discarded, this);
}
