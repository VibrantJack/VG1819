#include "K_GameObject.h"
#include "K_Component.h"
#include "K_ComponentManager.h"

#include <iostream>

namespace kitten
{
	K_GameObject::K_GameObject()
	{
		m_transform = new Transform(*this);
	}

	K_GameObject::~K_GameObject()
	{
		K_ComponentManager* compMan = K_ComponentManager::getInstance();

		//Delete attached components
		auto it = m_components.begin();
		while (it != m_components.end())
		{
			K_ComponentManager::getInstance()->destroyComponentImmediate(it->second);
			it = m_components.begin();
		}

		delete m_transform;
	}

	bool K_GameObject::addComponent(K_Component* p_toAdd)
	{
		if (m_components.count(std::type_index(typeid(*p_toAdd))) > 0)
		{
			return false;
		}
		//m_components[std::type_index(typeid(*p_toAdd))] = p_toAdd;

		m_components.insert(std::make_pair(std::type_index(typeid(*p_toAdd)), p_toAdd));

		p_toAdd->m_attachedObject = this;

		return true;
	}

	void K_GameObject::removeComponent(K_Component* p_toRemove)
	{
		if (m_components.count(std::type_index(typeid(*p_toRemove))) == 0)
		{
			for (auto it = m_components.begin(); it != m_components.end(); ++it)
			{
				if ((*it).second == p_toRemove)
				{
					assert(false);
				}
			}
			assert(false);
		}
		m_components.erase(std::type_index(typeid(*p_toRemove)));
	}

	//This does not work, LNK 2019
	/*
	template <class T>
	T* K_GameObject::getComponent()
	{
		if (m_components.count(std::type_index(typeid(T))) != 0)
		{
			return static_cast<T*>(m_components[std::type_index(typeid(T))]);
		}
		else
		{
			return nullptr;
		}
	}
	*/
}