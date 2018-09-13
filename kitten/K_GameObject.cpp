#include "K_GameObject.h"
#include "K_Component.h"
#include "K_ComponentManager.h"

namespace kitten
{
	K_GameObject::K_GameObject()
	{
		m_transform = new Transform();
	}

	K_GameObject::~K_GameObject()
	{
		delete m_transform;

		//Delete attached components
		for (auto it = m_components.begin(); it != m_components.end(); ++it)
		{
			if (!K_ComponentManager::getInstance()->destroyComponent(it->second))
			{
				assert(false);
			}
		}
	}

	//@TODO: return false if already has component of type or do something like
	bool K_GameObject::addComponent(K_Component* p_toAdd)
	{
		m_components[std::type_index(typeid(*p_toAdd))] = p_toAdd;
		p_toAdd->m_attachedObject = this;
		return true;
	}

	template <typename T>
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
}