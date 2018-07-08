#include "K_ComponentManager.h"
#include "K_Component.h"

namespace kitten
{
	bool K_ComponentManager::createComponent()
	{
		K_Component* comp;

		//...

		if (comp->hasUpdate())
		{
			m_toUpdate.push_back(comp);
		}
	}

	bool K_ComponentManager::destroyComponent(K_Component* p_toDestroy)
	{

	}
}