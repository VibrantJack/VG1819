#pragma once

#include "Transform.h"

namespace kitten
{
	class K_ComponentManager;
	class K_GameObject;

	class K_Component
	{
		friend class K_ComponentManager;

	protected:
		K_Component();
		virtual ~K_Component();
		
		K_GameObject* m_attachedObject;
	public:
		virtual const bool hasUpdate() const { return false; }
		virtual void update();

		K_GameObject& getGameObject() { return *m_attachedObject; };
		//For convenience
		Transform& getTransform();
	};
}