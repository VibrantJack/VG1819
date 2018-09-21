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

	void K_Component::onAttached()
	{
		//Empty to not force override
	}

	void K_Component::update()
	{
		// If you aren't here by choice,
		// then you set hasUpdate() to true in a component,
		// but did not override your update!
		assert(false);
	}

	Transform& K_Component::getTransform() const
	{
		return m_attachedObject->getTransform();
	}
}