#include "DiscardCardOnClick.h"
#include "UI/HandFrame.h"
#include "kitten/K_GameObjectManager.h"
#include "UI\CardContext.h"
#include "UI/CardUIO.h"
#include "components/clickables/HoverOverCardBehavior.h"

#define CARD_DISCARD_ANIM_TIME 2
#define CARD_DISCARD_MOVE_TIME 2

void DiscardCardOnClick::onPositionLerpFinished(kitten::K_GameObject* p_obj)
{
	// Delete Card
	kitten::K_GameObjectManager::getInstance()->destroyGameObject(this->m_attachedObject);
}

DiscardCardOnClick::DiscardCardOnClick(bool p_backToOrigin)
{
}

DiscardCardOnClick::~DiscardCardOnClick()
{
}

void DiscardCardOnClick::start()
{
	ClickableUI::start();
	m_lerpController = m_attachedObject->getComponent<LerpController>();
	setEnabled(userinterface::HandFrame::getActiveInstance()->isOnDiscardMode());
}

void DiscardCardOnClick::onClick()
{
	// Remove Card from hand
	userinterface::CardUIO* cardUIObject = this->m_attachedObject->getComponent<userinterface::CardUIO>();
	userinterface::HandFrame::getActiveInstance()->removeCard((userinterface::UIObject*)cardUIObject);

	// Decrease points by 1, can be customized later for more
	userinterface::HandFrame::getActiveInstance()->decreasePointCountBy(1);

	// disable the Hover so that it doesn't replace animation
	m_attachedObject->getComponent<HoverOverCardBehavior>()->setEnabled(false);

	// Animate Discard
	m_lerpController->positionLerp(glm::vec3(
		getTransform().getTranslation().x,
		getTransform().getTranslation().y + 250,
		getTransform().getTranslation().z
	), CARD_DISCARD_MOVE_TIME);
	//m_lerpController->scaleLerp(glm::vec3(1, 1, 1), CARD_DISCARD_ANIM_TIME); Scale doesn't work
	m_lerpController->addPositionLerpFinishedCallback(this);

}
