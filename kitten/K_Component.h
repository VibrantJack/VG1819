#pragma once
#include "Transform.h"
#include "K_GameObject.h"
#include "kibble/json/jsonextra.hpp"

namespace kitten
{
	class K_ComponentManager;
	class K_GameObject;

	class K_Component
	{
		friend class K_ComponentManager;
		friend class K_GameObject;
	protected:
		K_Component();
		K_Component(nlohmann::json&);
		virtual ~K_Component();

		K_GameObject* m_attachedObject;
		bool m_hasStarted = false;

		bool m_isEnabled = true;

		virtual void onDisabled();
		virtual void onEnabled();
	public:
		virtual bool hasUpdate() const;

		virtual void start();
		virtual void update();

		K_GameObject& getGameObject() { return *m_attachedObject; }
		//For convenience
		inline Transform& getTransform() const
		{
			return m_attachedObject->getTransform();
		}

		bool isEnabled() const;
		void setEnabled(bool p_enabled);
	};
}