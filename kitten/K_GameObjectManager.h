#pragma once
#include <vector>
#include <map>
#include <cassert>

#include "K_GameObject.h"

namespace kitten
{
	class K_GameObjectManager
	{
	private:
		static K_GameObjectManager* sm_instance;
		K_GameObjectManager();
		~K_GameObjectManager();


		std::map<int, K_GameObject*> m_gameObjects;
		std::vector<K_GameObject*> m_toDelete;

		int m_totalObjects = 0;
	public:
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new K_GameObjectManager(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
		static K_GameObjectManager* getInstance() { return sm_instance; };


		K_GameObject * createNewGameObject();
		K_GameObject * createNewGameObject(const std::string& filename);
		void destroyGameObject(K_GameObject* p_toDestroy);

		void deleteQueuedObjects();

		void destroyAllGameObjects();
	};
}