#include "UnitMove.h"
#include "unit/Unit.h"
#include "board/tile/TileInfo.h"
#include "board/BoardManager.h"
#include "unitInteraction/UnitInteractionManager.h"
#include <iostream>
#include <cmath>

void unit::UnitMove::triggerNewTileEvent()
{
	//trigger new tile event
	Unit* u = m_attachedObject->getComponent<Unit>();

	ability::TimePointEvent* t = new ability::TimePointEvent(ability::TimePointEvent::New_Tile);
	t->putGameObject("tile", m_currentTile);
	u->triggerTP(ability::TimePointEvent::New_Tile, t);
}

unit::UnitMove::UnitMove()
{
	m_currentTile = nullptr;
	m_ad = nullptr;
}

unit::UnitMove::~UnitMove()
{
	if (m_ad != nullptr)
		delete m_ad;
}
/*
void unit::UnitMove::registerListener()
{
	notRegistered = false;

	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Tile_Clicked,
		this,
		std::bind(&UnitMove::listenEvent, this, std::placeholders::_1, std::placeholders::_2));
}

void unit::UnitMove::deregisterListener()
{
	notRegistered = true;

	kitten::EventManager::getInstance()->queueRemoveListener(kitten::Event::Tile_Clicked, this);
}

void unit::UnitMove::listenEvent(kitten::Event::EventType p_type, kitten::Event * p_data)
{
	if (p_type == kitten::Event::Tile_Clicked)
	{
		
		bool highlighted = p_data->getInt("highlighted");
		if (highlighted)//move
		{
			move(p_data->getGameObj("tile0"));
		}
		else//cancel move
		{
			std::cout << "Cancel Move" << std::endl;
			triggerUnhighLightEvent();
		}
		deregisterListener();
	}
}
*/
void unit::UnitMove::attempToMove(int p_min, int p_max)
{
	unit::Unit* u = m_attachedObject->getComponent<unit::Unit>();

	if (m_ad != nullptr)
		delete m_ad;

	m_ad = new unit::AbilityDescription();

	m_ad->m_stringValue["name"] = "Move";
	m_ad->m_intValue["target"] = 1;
	m_ad->m_intValue["min_range"] = p_min;
	if (p_max < 0)
		m_ad->m_intValue["max_range"] = m_attachedObject->getComponent<Unit>()->m_attributes["mv"];//the range is between 1 and mv attributes
	else
		m_ad->m_intValue["max_range"] = p_max;
	//filter
	m_ad->m_intValue["filter"] = 1;
	m_ad->m_stringValue["filter0"] = "unit";

	UnitInteractionManager::getInstance()->request(u, m_ad);
}
/*
void unit::UnitMove::triggerHighLightEvent(int p_min, int p_max)
{
	//trigger the highlight event shows what are possible move
	kitten::Event* e = new kitten::Event(kitten::Event::Highlight_Tile);
	e->putString(TILE_OWNER_KEY, m_attachedObject->getComponent<Unit>()->m_name + " Move.");//highlight because of this unit move
	e->putInt("min_range", p_min);

	if (p_max < 0)
		e->putInt("max_range", m_attachedObject->getComponent<Unit>()->m_attributes["mv"]);//the range is between 1 and mv attributes
	else
		e->putInt("max_range", p_max);
	e->putGameObj("tileAtOrigin", m_currentTile);
	e->putString("mode", "range");
	e->putString("use", "move");
	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Highlight_Tile, e);
}

void unit::UnitMove::triggerUnhighLightEvent()
{
	kitten::Event* e = new kitten::Event(kitten::Event::Unhighlight_Tile);
	kitten::EventManager::getInstance()->triggerEvent(kitten::Event::Unhighlight_Tile, e);
}*/

void unit::UnitMove::move(kitten::K_GameObject * p_targetTile)
{
	//remove unit from current tile
	m_currentTile->getComponent<TileInfo>()->removeUnit();
	//add this to target tile
	p_targetTile->getComponent<TileInfo>()->setUnit(m_attachedObject);

	m_lastTile = m_currentTile;//set current to last
	m_currentTile = p_targetTile;//set target to current

	//set distance
	distanceX = m_currentTile->getTransform().getTranslation().x - m_lastTile->getTransform().getTranslation().x;
	distanceZ = m_currentTile->getTransform().getTranslation().z - m_lastTile->getTransform().getTranslation().z;

	//tell unit object move is done
	m_attachedObject->getComponent<unit::Unit>()->moveDone();

	//send unhighlight event
	//triggerUnhighLightEvent();

	triggerNewTileEvent();
}

void unit::UnitMove::setTile(kitten::K_GameObject * p_tile)
{
	if (m_currentTile != nullptr)
	{
		//remove unit from current tile
		m_currentTile->getComponent<TileInfo>()->removeUnit();
	}
	//std::string name = m_attachedObject->getComponent<Unit>()->m_name;
	//add this to target tile
	p_tile->getComponent<TileInfo>()->setUnit(m_attachedObject);

	m_currentTile = p_tile;
	m_lastTile = p_tile;
	reset();
}

void unit::UnitMove::setTile(int p_x, int p_z)
{
	set = true;
	m_tileX = p_x;
	m_tileZ = p_z;
}

kitten::K_GameObject * unit::UnitMove::getTile()
{
	return m_currentTile;
}

void unit::UnitMove::reset()
{
	//set the unit's position to current tile
	glm::vec3 t = m_currentTile->getTransform().getTranslation();//get tile's translation
	m_attachedObject->getTransform().place(t.x, t.y, t.z);//set unit object to that tile
	m_attachedObject->getTransform().move(m_offset.x, m_offset.y, m_offset.z);//move unit upward
}

bool unit::UnitMove::hasUpdate() const
{
	return true;
}

void unit::UnitMove::update()
{
	if (set)
	{
		setTile(BoardManager::getInstance()->getTile(m_tileX,m_tileZ));
		set = false;
	}

	if (m_currentTile != m_lastTile)
	{
		float velocity = kitten::K_Time::getInstance()->getDeltaTime() * m_speed * 60.0f;//delta time * speed * 60fps
		
		if (distanceX == 0)//if unit has same x value as target tile
		{
			if (distanceZ > 0)//move in positive direction
			{
				if (distanceZ > velocity)//not close
				{
					m_attachedObject->getTransform().move(0.0f, 0.0f, velocity);
					distanceZ -= velocity;
				}
				else//vecy close, 
				{
					m_attachedObject->getTransform().move(0.0f, 0.0f, distanceZ);
					distanceZ = 0;
				}
			}
			if (distanceZ < 0)
			{
				if (distanceZ < -velocity)
				{
					m_attachedObject->getTransform().move(0.0f, 0.0f, -velocity);
					distanceZ += velocity;
				}
				else
				{
					m_attachedObject->getTransform().move(0.0f, 0.0f, distanceZ);
					distanceZ = 0;
				}
			}
			if (distanceZ == 0)//unit is at target tile
			{
				m_lastTile = m_currentTile;//set current tile as last
				reset();
			}
		}
		else//not have same x value
		{
			if (distanceX > 0)
			{
				if (distanceX > velocity)
				{
					m_attachedObject->getTransform().move(velocity, 0.0f, 0.0f);
					distanceX -= velocity;
				}
				else
				{
					m_attachedObject->getTransform().move(distanceX, 0.0f, 0.0f);
					distanceX = 0;
				}
			}
			if (distanceX < 0)
			{
				if (distanceX < -velocity)
				{
					m_attachedObject->getTransform().move(-velocity, 0.0f, 0.0f);
					distanceX += velocity;
				}
				else
				{
					m_attachedObject->getTransform().move(distanceX, 0.0f, 0.0f);
					distanceX = 0;
				}
			}
		}
	}
}
