#pragma once

#include <list>
#include <cassert>
#include "kibble/ComponentDataParser.hpp"

namespace kitten
{
	class K_Instance;
	class K_Component;

	class K_ComponentManager
	{
		friend class K_Component;
		friend class K_Instance;
	private:
		static K_ComponentManager* sm_instance;
		K_ComponentManager();
		~K_ComponentManager();

		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new K_ComponentManager(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };

		void updateComponents();

		std::list<K_Component*> m_toUpdate;
		std::list<K_Component*> m_toStart;
		std::list<K_Component*> m_toDelete;

		std::list<K_Component*> m_toAddToUpdate;
		std::list<const K_Component*> m_toRemoveFromUpdate;

		void addToStart(K_Component* p_toStart);
		void removeFromStart(const K_Component* p_toRemove);
		void addToUpdate(K_Component* p_toUpdate);
		bool removeFromUpdate(const K_Component* p_toRemove);

		void queueRemovalFromUpdate(const K_Component* p_toRemove);
		void queueAddToUpdate(K_Component* p_toUpdate);

	public:
		static K_ComponentManager * getInstance() { return sm_instance; };

		K_Component* createComponent(const std::string& p_componentName);
		K_Component* createComponent(kibble::ComponentDataParser* data);

		bool destroyComponent(K_Component* p_toDestroy);
		void destroyComponentImmediate(K_Component* p_toDestroy);
	};
}