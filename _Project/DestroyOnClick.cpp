#include "DestroyOnClick.h"
#include "kitten\K_GameObjectManager.h"

DestroyOnClick::DestroyOnClick(const glm::vec3& p_minPoint, const glm::vec3& p_maxPoint) : Clickable(p_minPoint, p_maxPoint)
{

}

DestroyOnClick::~DestroyOnClick()
{

}

void DestroyOnClick::onClick()
{
	kitten::K_GameObjectManager::getInstance()->destroyGameObject(m_attachedObject);
}