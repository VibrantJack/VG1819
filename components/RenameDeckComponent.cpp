#include "RenameDeckComponent.h"
#include "DeckAlterationComponent.h"

RenameDeckComponent::RenameDeckComponent()
{
}

RenameDeckComponent::RenameDeckComponent(nlohmann::json & p_json) : kitten::K_Component(p_json)
{
}

RenameDeckComponent::~RenameDeckComponent()
{
	input::InputManager::getInstance()->removeStringListener(this);
}

void RenameDeckComponent::start()
{
	input::InputManager::getInstance()->addStringListener(this);
}

void RenameDeckComponent::onStringFinished(const std::string & p_string)
{
	DeckAlterationComponent::getActiveInstance()->getDeckData()->name = p_string;
}

void RenameDeckComponent::onStringChanged(const std::string & p_string)
{
	DeckAlterationComponent::getActiveInstance()->getDeckData()->name = p_string;
}
