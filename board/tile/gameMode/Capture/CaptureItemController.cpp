#include "CaptureItemController.h"

CaptureItemController::CaptureItemController():
	m_rotate(false)
{
}

CaptureItemController::~CaptureItemController()
{
}

bool CaptureItemController::hasUpdate() const
{
	return m_rotate;
}

void CaptureItemController::update()
{
	getTransform().rotateRelative(glm::vec3(0, m_rotateSpeed, 0));
}

void CaptureItemController::setRotateSpeed(float p_s)
{
	//set speed
	m_rotateSpeed = p_s;
	
	//will rotate
	m_rotate = true;
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
	//add this to target
	p_info->addItem(&getGameObject());

	//change pos
	getTransform().place(m_unitOffset.x, m_unitOffset.y, m_unitOffset.z);

	//get game object
	privateSetParent(&p_info->getGameObject());
}

void CaptureItemController::setParent(TileInfo * p_info)
{
	//add this to target
	p_info->addItem(&getGameObject());

	//change pos
	getTransform().place(m_tileOffset.x, m_tileOffset.y, m_tileOffset.z);

	//get game object
	privateSetParent(&p_info->getGameObject());
}

void CaptureItemController::privateSetParent(kitten::K_GameObject * p_go)
{
	this->getTransform().setParent(&p_go->getTransform());
	this->getTransform().setIgnoreParent(false);
}
