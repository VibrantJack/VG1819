#include "DeckDiscardedCardHandler.h"
#include "UI/CardUIO.h"
#include "kitten/K_GameObjectManager.h"
#include "_Project/LerpController.h"

#define TIME_TO_MOVE_CARD 1.25

void DeckDiscardedCardHandler::onEnabled()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Card_Discarded,
		this,
		std::bind(&DeckDiscardedCardHandler::receiveDiscardedCard, this, std::placeholders::_1, std::placeholders::_2));
}

void DeckDiscardedCardHandler::onDisabled()
{
	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Card_Discarded, this);
}

DeckDiscardedCardHandler::DeckDiscardedCardHandler()
{
}

DeckDiscardedCardHandler::~DeckDiscardedCardHandler()
{
}

void DeckDiscardedCardHandler::receiveDiscardedCard(kitten::Event::EventType p_type, kitten::Event * p_event)
{
	// check which player is discarding
	if (0 != p_event->getInt(PLAYER_ID)) {
		// This means this clients discard
		// Find the number of cards discarded
		int count = p_event->getInt(CARD_COUNT);

		if (card != nullptr) return; // only one will be displayed at a time.

		// Generate Cards to discard
		kitten::K_GameObject* card = kitten::K_GameObjectManager::getInstance()->createNewGameObject("handcard.json");
		userinterface::CardUIO* cardCasted = card->getComponent<userinterface::CardUIO>();
		cardCasted->scaleAsCard();

		LerpController* lerpC = card->getComponent<LerpController>();
		if (lerpC == nullptr)
		{
			card->getTransform().place2D(getTransform().getTranslation().x, getTransform().getTranslation().y + 250);
		}
		else
		{
			lerpC->positionLerp(
				glm::vec3(getTransform().getTranslation().x, getTransform().getTranslation().y + 250, 0),
				TIME_TO_MOVE_CARD);
			lerpC->addPositionLerpFinishedCallback(this);
		}
	}
	else
	{

	}
}

void DeckDiscardedCardHandler::start()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Card_Discarded,
		this,
		std::bind(&DeckDiscardedCardHandler::receiveDiscardedCard, this, std::placeholders::_1, std::placeholders::_2));
}

void DeckDiscardedCardHandler::onPositionLerpFinished(kitten::K_GameObject* p_obj)
{
	// Delete Card
	kitten::K_GameObjectManager::getInstance()->destroyGameObject(this->m_attachedObject);
}
