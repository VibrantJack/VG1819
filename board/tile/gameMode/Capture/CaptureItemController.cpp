#include "CaptureItemController.h"
#include "kitten/K_Time.h"
CaptureItemController::CaptureItemController()
{
}

CaptureItemController::~CaptureItemController()
{
}

bool CaptureItemController::hasUpdate() const
{
	return true;
}

void CaptureItemController::update()
{
	//get position
	if (m_isUnit)
	{
		glm::vec3 pos = m_holder->getTransform().getTranslation();
		getTransform().place(pos.x + m_unitOffset.x, pos.y + m_unitOffset.y, pos.z + m_unitOffset.z);
	}

}

void CaptureItemController::setTileOffset(const glm::vec3 & p_pos)
{
	m_tileOffset = p_pos;
}

void CaptureItemController::setUnitOffset(const glm::vec3 & p_pos)
{
	m_unitOffset = p_pos;
}

void CaptureItemController::setParent(unit::Unit * p_info)
{
	//change holder
	m_holder = &p_info->getGameObject();

	//add this to target
	p_info->addItem(&getGameObject());

	m_isUnit = true;
}

void CaptureItemController::setParent(TileInfo * p_info)
{
	//change holder
	m_holder = &p_info->getGameObject();

	//add this to target
	p_info->addItem(&getGameObject());

	//set pos
	glm::vec3 pos = m_holder->getTransform().getTranslation();
	getTransform().place(pos.x + m_tileOffset.x, pos.y + m_tileOffset.y, pos.z + m_tileOffset.z);

	m_isUnit = false;
}

