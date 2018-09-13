#include "K_GameObjectManager.h"

namespace kitten
{
	K_GameObjectManager* K_GameObjectManager::sm_instance = nullptr;

	K_GameObjectManager::K_GameObjectManager()
	{

	}

	K_GameObjectManager::~K_GameObjectManager()
	{

	}

	K_GameObject* K_GameObjectManager::createNewGameObject()
	{
		K_GameObject* toReturn = new K_GameObject();
		
		toReturn->m_objectIndex = m_totalObjects++;
		m_gameObjects.push_back(toReturn);

		return toReturn;
	}

	void K_GameObjectManager::destroyGameObject(K_GameObject* p_toDestroy)
	{
		assert(p_toDestroy != nullptr);

		m_gameObjects.erase(m_gameObjects.begin() + p_toDestroy->m_objectIndex);

		delete(p_toDestroy);
	}
}