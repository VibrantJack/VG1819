#pragma once
#include <list>
#include <unordered_map>
#include <cassert>
#include <unordered_set>

#include "K_GameObject.h"

namespace kitten
{
	class K_Instance;
	class Transform;

	class K_GameObjectManager
	{
		friend class K_Instance;
		friend class Transform;
	private:
		static K_GameObjectManager* sm_instance;
		K_GameObjectManager();
		~K_GameObjectManager();

		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new K_GameObjectManager(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };

		std::unordered_map<int, K_GameObject*> m_gameObjects;
		std::list<K_GameObject*> m_toDelete;
		std::unordered_set<K_GameObject*> m_toSurvive;

		int m_createdObjects = 0;

		void deleteQueuedObjects();
		void deleteGameObject(K_GameObject* p_toDelete);

		void removeGameObjectFromList(K_GameObject* p_toRemove); //called by transform when it has its parent set
		void addGameObjectToList(K_GameObject* p_toAdd); //called by transform when it has its parent removed

	public:
		static K_GameObjectManager* getInstance() { return sm_instance; };

		K_GameObject * createNewGameObject();
		K_GameObject * createNewGameObject(const std::string& filename);

		void destroyGameObject(K_GameObject* p_toDestroy);
		void destroyGameObjectWithChild(K_GameObject* p_toDestroy);

		void destroyAllGameObjects();
		void destroySceneGameObjects();

		void flagGameObjectToSurvive(K_GameObject* p_toSurvive);
	};
}