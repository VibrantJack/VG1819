#include "SpawnUnitOnDrop.h"
#include "unit/Unit.h"
#include "unit/UnitSpawn.h"
#include "kitten/InputManager.h"
#include "board/tile/TileInfo.h"
#include "unit/unitComponent/UnitMove.h"
#include "kitten/K_GameObjectManager.h"
#include "kibble/databank/databank.hpp"
#include "UI/HandFrame.h"
#include "UI/CardUIO.h"
#include "components/PowerTracker.h"
#include "components/clickables/HoverOverCardBehavior.h"
#include "board/BoardManager.h"
#include "kitten\event_system\EventManager.h"
#include <iostream>
#include "UI/UIFrame.h"
#include "_Project/LerpController.h"

// Networking
#include "networking\ClientGame.h"

#define CARD_HOVER_MOVE_TIME 0.2
#define CARD_SHADOW_MOVE_TIME 0.2

void SpawnUnitOnDrop::onClick()
{
	if (networking::ClientGame::isNetworkValid())
	{
		if (unit::InitiativeTracker::getInstance()->getCurrentUnitIndex() >= 0)
		{
			unit::Unit* currentUnit = unit::InitiativeTracker::getInstance()->getCurrentUnit()->getComponent<unit::Unit>();
			unit::Unit* clientCommander = networking::ClientGame::getInstance()->getCommander();
			if (currentUnit != clientCommander) return;
		}
		else
		{
			return;
		}
	}

	DragNDrop::onClick();

	kitten::K_GameObject& shadow = getTransform().getChildren()[0]->getAttachedGameObject();
	auto& shadowTranslation = shadow.getTransform().getTranslation();
	auto shadowLerp = shadow.getComponent<LerpController>();

	if (shadowLerp->isLerping())
	{
		shadowLerp->endLerp(LerpController::TransformBehavior::SetToTarget, false);
	}

	if (m_isDragging == false) 
	{
		m_lerpController->addPositionLerpFinishedCallback(this);
		m_attachedObject->getComponent<userinterface::CardUIO>()->setGAlpha(1);
		m_attachedObject->getComponent<userinterface::CardUIO>()->setTransparency(false);
		
		shadowLerp->positionLerp(
			glm::vec3(
				0,
				0,
				shadowTranslation.z
			), CARD_SHADOW_MOVE_TIME, LerpController::TransformSource::Local
		);

		m_attachedFrame->setBlocksRaycast(true);
	} 
	else 
	{
		m_attachedObject->getComponent<HoverOverCardBehavior>()->setEnabled(false);
		m_attachedObject->getComponent<userinterface::CardUIO>()->setGAlpha(0.5);
		m_attachedObject->getComponent<userinterface::CardUIO>()->setTransparency(true);
		shadow.setEnabled(true);

		shadowLerp->positionLerp(
			glm::vec3(
				- 10 ,
				- 10 ,
				shadowTranslation.z
			), CARD_SHADOW_MOVE_TIME, LerpController::TransformSource::Local
		);

		m_attachedFrame->setBlocksRaycast(false);
	}

	if (!m_isDragging)
		return;

	//check unit cost
	unit::Unit* unit = m_attachedObject->getComponent<unit::Unit>();
	if (BoardManager::getInstance()->getPowerTracker()->getCurrentPower() < unit->m_attributes[UNIT_COST]) // Check if there is enough power to spawn this.
		return;

	//send summon event
	kitten::Event* e = new kitten::Event(kitten::Event::Summon_Unit);
	e->putGameObj(UNIT, m_attachedObject);
	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Summon_Unit, e);
}

void SpawnUnitOnDrop::onDrop()
{
	kitten::K_GameObject* objectBehindCard = input::InputManager::getInstance()->getMouseLastHitObject();
	if (objectBehindCard != nullptr)
	{
		objectBehindCard->getComponent<kitten::ClickableBox>()->onClick();
	}
	else
	{
		kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Cancel_Summon, nullptr);
	}
	resetCard();
}

void SpawnUnitOnDrop::onPause()
{
	resetCard();
}

void SpawnUnitOnDrop::onPositionLerpFinished()
{
	m_attachedObject->getComponent<HoverOverCardBehavior>()->setEnabled(true);
	getTransform().getChildren()[0]->getAttachedGameObject().setEnabled(false);
}

void SpawnUnitOnDrop::removeCard()
{
	// Remove Card from hand
	userinterface::CardUIO* cardUIObject = this->m_attachedObject->getComponent<userinterface::CardUIO>();
	userinterface::HandFrame::getActiveInstance()->removeCard((userinterface::UIObject*)cardUIObject);

	// Delete Card
	kitten::K_GameObjectManager::getInstance()->destroyGameObject(this->m_attachedObject);
}

void SpawnUnitOnDrop::resetCard()
{
	DragNDrop::onDrop();
	m_isDragging = false;
}

SpawnUnitOnDrop::SpawnUnitOnDrop()
	:
	DragNDrop(true)
{

}

SpawnUnitOnDrop::~SpawnUnitOnDrop()
{
}

void SpawnUnitOnDrop::start()
{
	DragNDrop::start();
	setEnabled(!userinterface::HandFrame::getActiveInstance()->isOnDiscardMode());

	kitten::K_GameObject& shadow = getTransform().getChildren()[0]->getAttachedGameObject();
	shadow.getComponent<userinterface::UIFrame>()->setTransparency(true);
	shadow.getComponent<userinterface::UIFrame>()->setGAlpha(0.5);

	shadow.setEnabled(false);
}