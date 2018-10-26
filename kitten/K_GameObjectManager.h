#pragma once
#include <list>
#include <unordered_map>
#include <cassert>

#include "K_GameObject.h"

namespace kitten
{
	class K_Instance;

	class K_GameObjectManager
	{
		friend class K_Instance;
	private:
		static K_GameObjectManager* sm_instance;
		K_GameObjectManager();
		~K_GameObjectManager();

		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new K_GameObjectManager(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };

		std::unordered_map<int, K_GameObject*> m_gameObjects;
		std::list<K_GameObject*> m_toDelete;

		int m_totalObjects = 0;

		void deleteQueuedObjects();
	public:
		static K_GameObjectManager* getInstance() { return sm_instance; };

		K_GameObject * createNewGameObject();
		K_GameObject * createNewGameObject(const std::string& filename);

		void destroyGameObject(K_GameObject* p_toDestroy);

		void destroyAllGameObjects();
	};
}