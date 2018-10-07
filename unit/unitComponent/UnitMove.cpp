#include "UnitMove.h"
#include "unit/Unit.h"
#include <iostream>
#include <cmath>

unit::UnitMove::UnitMove()
{
}

unit::UnitMove::~UnitMove()
{
}

void unit::UnitMove::registerListener()
{
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Tile_Clicked_For_Unit_Move,
		this,
		std::bind(&UnitMove::listenEvent, this, std::placeholders::_1, std::placeholders::_2));
}

void unit::UnitMove::deregisterListener()
{
	kitten::EventManager::getInstance()->queueRemoveListener(kitten::Event::Tile_Clicked_For_Unit_Move, this);
}

void unit::UnitMove::listenEvent(kitten::Event::EventType p_type, kitten::Event * p_data)
{
	if (p_type == kitten::Event::Tile_Clicked_For_Unit_Move)
	{
		if (p_data->getGameObj("tileObj"))
		{
			move(p_data->getGameObj("tileObj"));
			deregisterListener();
		}
	}
}

void unit::UnitMove::attempToMove()
{
	std::cout << "Ready To Move" << std::endl;
	//when first click, this class will register event that require player to click a tile
	registerListener();
}

void unit::UnitMove::move(kitten::K_GameObject * p_targetTile)
{
	m_lastTile = m_currentTile;//set current to last
	m_currentTile = p_targetTile;//set target to current

	//set distance
	distanceX = m_currentTile->getTransform().getTranslation().x - m_lastTile->getTransform().getTranslation().x;
	distanceZ = m_currentTile->getTransform().getTranslation().z - m_lastTile->getTransform().getTranslation().z;

	//tell object move is done
	m_attachedObject->getComponent<unit::Unit>()->moveDone();
}

void unit::UnitMove::setTile(kitten::K_GameObject * p_targetTile)
{
	m_currentTile = p_targetTile;
	m_lastTile = p_targetTile;
	reset();
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
