#include "K_GameObject.h"

namespace kitten
{
	K_GameObject::K_GameObject()
	{
		m_transform = new Transform();
	}

	K_GameObject::~K_GameObject()
	{
		delete m_transform;
	}

	bool K_GameObject::addComponent(K_Component* p_toAdd)
	{
		m_components[std::type_index(typeid(*p_toAdd))] = p_toAdd;
	}

	template <typename T>
	T* K_GameObject::getComponent()
	{
		if (m_components.count(std::type_index(typeid(T))) != 0)
		{
			return static_cast<T*>(m_components[std::type_index(typeid(T)];
		}
		else
		{
			return nullptr;
		}
	}
}