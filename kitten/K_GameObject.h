#pragma once

#include <typeindex>
#include <unordered_map>

#include "Transform.h"

namespace kitten
{
	class K_Component;

	class K_GameObject
	{
		friend class K_GameObjectManager;
	private:
		std::unordered_map<std::type_index, K_Component*> m_components;
		int m_objectIndex;

		Transform* m_transform;

		K_GameObject();
		~K_GameObject();
	public:
		//Constructor and destructor in GameObjectManager
		bool addComponent(K_Component* p_toAdd);
		void removeComponent(K_Component* p_toRemove);

		template <class T> //@TODO: Fix LNK 2019 when putting this in K_GameObject.cpp
		T* getComponent();

		Transform& getTransform() { return *m_transform; };
	};
	
	//This works, see K_GameObject.cpp for non-working
	template<class T>
	inline T * K_GameObject::getComponent()
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