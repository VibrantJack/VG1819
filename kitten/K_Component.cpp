#include "K_Component.h"
#include "K_GameObject.h"
#include "K_ComponentManager.h"

namespace kitten
{
	K_Component::K_Component()
	{

	}

	K_Component::~K_Component()
	{
		
	}

	bool K_Component::hasUpdate() const
	{
		return false;
	}


	Transform& K_Component::getTransform() const
	{
		return m_attachedObject->getTransform();
	}

	bool K_Component::isEnabled() const
	{
		return m_isEnabled;
	}

	void K_Component::setEnabled(bool p_enabled)
	{
		if (m_isEnabled && !p_enabled)
		{
			m_isEnabled = false;

			if (!m_hasStarted)
			{
				K_ComponentManager::getInstance()->removeFromStart(this);
			}
			else if (hasUpdate())
			{
				K_ComponentManager::getInstance()->queueRemovalFromUpdate(this);
			}

			onDisabled();
		}
		else if (!m_isEnabled && p_enabled)
		{
			m_isEnabled = true;

			if (!m_hasStarted)
			{
				K_ComponentManager::getInstance()->addToStart(this);
			}
			else
			{
				if (hasUpdate())
				{
					K_ComponentManager::getInstance()->queueAddToUpdate(this);
				}
			}
			
			onEnabled();
		}
	}

	void K_Component::start()
	{
		//Empty to not force override
	}

	void K_Component::onDisabled()
	{
		//Intentionally blank
	}

	void K_Component::onEnabled()
	{
		//Intentionally blank
	}
	
	void K_Component::update()
	{
		// If you aren't here by choice,
		// then you set hasUpdate() to true in a component,
		// but did not override your update!
		assert(false);
	}
}