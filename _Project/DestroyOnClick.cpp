#include "DestroyOnClick.h"
#include "kitten\K_GameObjectManager.h"

DestroyOnClick::DestroyOnClick(nlohmann::json & p_json) : kitten::Clickable(p_json)
{
}

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