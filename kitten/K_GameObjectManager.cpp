#include "K_GameObjectManager.h"
#include "kibble/kibble.hpp"

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

		toReturn->m_objectIndex = m_createdObjects;
		m_gameObjects.insert(std::make_pair(m_createdObjects,toReturn));

		m_createdObjects++;

		return toReturn;
	}

	K_GameObject* K_GameObjectManager::createNewGameObject(const std::string& p_filename)
	{
		kibble::GameObjectDataParser* parser = kibble::getGameObjectDataParserInstance();
		return parser->getGameObject(p_filename);
	}

	void K_GameObjectManager::removeGameObjectFromList(K_GameObject* p_toRemove)
	{
		if (p_toRemove->m_survivesSceneChange)
		{
			m_toSurvive.erase(p_toRemove);
		}
		else
		{
			m_gameObjects.erase(p_toRemove->m_objectIndex);
		}
	}

	void K_GameObjectManager::addGameObjectToList(K_GameObject* p_toAdd)
	{
		if (p_toAdd->m_survivesSceneChange)
		{
			m_toSurvive.insert(p_toAdd);
		}
		else
		{
			m_gameObjects.insert(std::make_pair(p_toAdd->m_objectIndex, p_toAdd));
		}
	}

	void K_GameObjectManager::destroyGameObject(K_GameObject* p_toDestroy)
	{
		assert(p_toDestroy != nullptr);

		m_toDelete.push_back(p_toDestroy);
	}

	void K_GameObjectManager::deleteQueuedObjects()
	{
		for (auto it = m_toDelete.begin(); it != m_toDelete.end(); ++it)
		{
			auto gameObject = (*it);

			if (!gameObject->getTransform().getParent())
			{
				m_gameObjects.erase(gameObject->m_objectIndex);
			}
			
			deleteGameObject(gameObject);
		}

		m_toDelete.clear();
	}

	void K_GameObjectManager::destroyAllGameObjects()
	{
		deleteQueuedObjects();

		auto end = m_gameObjects.end();
		for (auto it = m_gameObjects.begin(); it != end; ++it)
		{
			deleteGameObject((*it).second);
		}
		m_gameObjects.clear();

		auto survivEnd = m_toSurvive.end();
		for (auto it = m_toSurvive.cbegin(); it != survivEnd; ++it)
		{
			deleteGameObject(*it);
		}
		m_toSurvive.clear();
	}

	void K_GameObjectManager::destroySceneGameObjects() 
	{
		deleteQueuedObjects();

		auto end = m_gameObjects.end();
		for (auto it = m_gameObjects.begin(); it != end; ++it)
		{
			deleteGameObject((*it).second);
		}
		m_gameObjects.clear();	
	}

	void K_GameObjectManager::deleteGameObject(K_GameObject* p_toDelete)
	{
		auto list = p_toDelete->getTransform().getChildren();
		for (int i = 0; i < list.size(); i++)
		{
			deleteGameObject(&list[i]->getAttachedGameObject());
		}

		delete p_toDelete;
	}

	void K_GameObjectManager::flagGameObjectToSurvive(K_GameObject* p_toSurvive)
	{
		p_toSurvive->m_survivesSceneChange = true;

		m_toSurvive.insert(p_toSurvive);
		m_gameObjects.erase(m_gameObjects.find(p_toSurvive->m_objectIndex));
	}
}