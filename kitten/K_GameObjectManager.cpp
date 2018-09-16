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
		m_toDelete.push_back(p_toDestroy);
		--m_totalObjects;
	}

	void K_GameObjectManager::deleteQueuedObjects()
	{
		for (auto it = m_toDelete.begin(); it != m_toDelete.end(); ++it)
		{
			delete *it;
			it = m_toDelete.erase(it);	
		}
	}
}