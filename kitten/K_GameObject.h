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

		bool m_isEnabled;

		K_GameObject();
		~K_GameObject();
	public:
		//Constructor and destructor in GameObjectManager
		bool addComponent(K_Component* p_toAdd);
		void removeComponent(K_Component* p_toRemove);

		template <class T>
		T* getComponent();

		Transform& getTransform() { return *m_transform; };

		bool isEnabled() const;
		void setEnabled(bool p_enabled);
	};
	
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