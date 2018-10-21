#include <iostream>
#include "PrintWhenClicked.h"
#include "board/tile/TileInfo.h"
#include "kitten/K_GameObject.h"

PrintWhenClicked::PrintWhenClicked(const std::string& p_message) :  m_message(p_message)
{

}

PrintWhenClicked::~PrintWhenClicked()
{

}

void PrintWhenClicked::setMessage(const std::string& p_message)
{
	m_message = p_message;
}

void PrintWhenClicked::onClick()
{
	TileInfo* info = m_attachedObject->getComponent<TileInfo>();
	if (info != nullptr)
	{
		std::cout << "Tile " << info->getPosX() << ", " << info->getPosY() << " highlighted by: "
			<< info->getHighlightedBy() << ", owned by: " << info->getOwnerId() << std::endl;
	}
	else
	{
		std::cout << m_message << std::endl;
	}
}

void PrintWhenClicked::onHoverStart()
{
	std::cout << "Started hovering!! (" << m_message << ")" << std::endl;
}

void PrintWhenClicked::onHoverEnd()
{
	std::cout << "Stopped hovering!! (" << m_message << ")" << std::endl;
}