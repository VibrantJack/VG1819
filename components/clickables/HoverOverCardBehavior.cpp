#include "HoverOverCardBehavior.h"
#include "UI/HandFrame.h"
#include "kibble/databank/databank.hpp"

#define CARD_HOVER_MOVE_TIME 0.2

HoverOverCardBehavior::HoverOverCardBehavior()
{
}

HoverOverCardBehavior::~HoverOverCardBehavior()
{
}

void HoverOverCardBehavior::start()
{
	ClickableUI::start();
	m_lerpController = m_attachedObject->getComponent<LerpController>();
	m_unit = m_attachedObject->getComponent<unit::Unit>();
	m_cardContext = userinterface::HandFrame::getActiveInstance()->getGameObject().getComponent<CardContext>();
}

void HoverOverCardBehavior::onHoverStart()
{
	m_lerpController->positionLerp(glm::vec3(m_origin.x, m_origin.y + 50, m_origin.z), CARD_HOVER_MOVE_TIME);
	m_isHovered = true;
	if(m_unit == nullptr)
		m_cardContext->setUnit(kibble::getUnitFromId(1));
	else
		m_cardContext->setUnit(m_unit);
	m_cardContext->setEnabled(true);
}

void HoverOverCardBehavior::onHoverEnd()
{
	m_lerpController->positionLerp(m_origin, CARD_HOVER_MOVE_TIME);
	m_isHovered = false;
	m_cardContext->setEnabled(false);
}
