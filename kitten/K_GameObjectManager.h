#include <list>
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


		std::vector<K_GameObject*> m_gameObjects;
		int m_totalObjects = 0;
	public:
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new K_GameObjectManager(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
		static K_GameObjectManager* getInstance() { return sm_instance; };


		K_GameObject * createNewGameObject();
		void destroyGameObject(K_GameObject* p_toDestroy);
	};
}