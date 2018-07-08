#pragma once

#include <list>
#include <cassert>

namespace kitten
{
	class K_Component;

	class K_ComponentManager
	{
	private:
		static K_ComponentManager* sm_instance;
		K_ComponentManager();
		~K_ComponentManager();

		std::list<K_Component*> m_toUpdate;
	public:
		
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new K_ComponentManager(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
		static K_ComponentManager * getInstance() { return sm_instance; };


		bool createComponent();
		bool destroyComponent(K_Component* p_toDestroy);

		void updateComponents();
	};
}