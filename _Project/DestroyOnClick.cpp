#include "DestroyOnClick.h"
#include "kitten\K_GameObjectManager.h"

DestroyOnClick::DestroyOnClick()
{

}

DestroyOnClick::~DestroyOnClick()
{

}

void DestroyOnClick::onClick()
{
	kitten::K_GameObjectManager::getInstance()->destroyGameObject(m_attachedObject);
}