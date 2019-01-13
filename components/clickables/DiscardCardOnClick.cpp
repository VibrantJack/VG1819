#include "DiscardCardOnClick.h"
#include "UI/HandFrame.h"
#include "kitten/K_GameObjectManager.h"
#include "UI\CardContext.h"
#include "UI/CardUIO.h"

#define CARD_DISCARD_ANIM_TIME 4
#define CARD_DISCARD_MOVE_TIME 4

void DiscardCardOnClick::onPositionLerpFinished()
{
	// Delete Card
	kitten::K_GameObjectManager::getInstance()->destroyGameObjectWithChild(this->m_attachedObject);
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
	setEnabled(!userinterface::HandFrame::getActiveInstance()->isOnDiscardMode());
}

void DiscardCardOnClick::onClick()
{
	// Remove Card from hand
	userinterface::CardUIO* cardUIObject = this->m_attachedObject->getComponent<userinterface::CardUIO>();
	userinterface::HandFrame::getActiveInstance()->removeCard((userinterface::UIObject*)cardUIObject);

	// Decrease points by 1, can be customized later for more
	userinterface::HandFrame::getActiveInstance()->decreasePointCountBy(1);

	// Reset the controller
	m_lerpController->cancelLerp(false);

	// Animate Discard
	m_lerpController->positionLerp(glm::vec3(
		getTransform().getTranslation().x,
		getTransform().getTranslation().y +150,
		getTransform().getTranslation().z
	), CARD_DISCARD_MOVE_TIME);
	m_lerpController->scaleLerp(glm::vec3(
		0, 0, 0
	), CARD_DISCARD_ANIM_TIME);
	m_lerpController->addPositionLerpFinishedCallback(this);
}
