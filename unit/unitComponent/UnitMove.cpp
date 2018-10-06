#include "UnitMove.h"
#include <iostream>

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
	glm::vec3 t = p_targetTile->getTransform().getTranslation();//get tile's translation
	m_attachedObject->getTransform().place(t.x, t.y, t.z);//set unit object to that tile
	m_attachedObject->getTransform().move(m_offset.x, m_offset.y, m_offset.z);//move unit upward
}
