#pragma once

#include <list>
#include <cassert>
#include "kibble/ComponentDataParser.hpp"

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
		std::list<K_Component*> m_toStart;
		std::list<K_Component*> m_toDelete;

		void removeFromStart(const K_Component* p_toRemove);
	public:
		
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new K_ComponentManager(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
		static K_ComponentManager * getInstance() { return sm_instance; };

		//@TODO: Implement Kibble creating comopnents here.
		//@Saleh you can change this function (createComponent) to take whatever parameters
		//you want, as long as Kibble on a whole works and it isn't too saddening
		K_Component* createComponent(const std::string& p_componentName);
		K_Component* createComponent(kibble::ComponentDataParser* data);
		bool destroyComponent(K_Component* p_toDestroy);

		void addToUpdate(K_Component* p_toUpdate);
		bool removeFromUpdate(const K_Component* p_toRemove);

		void updateComponents();
	};
}