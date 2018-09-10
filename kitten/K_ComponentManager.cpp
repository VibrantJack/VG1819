#include "K_ComponentManager.h"
#include "K_Component.h"

namespace kitten
{
	K_ComponentManager* K_ComponentManager::sm_instance = nullptr;

	K_ComponentManager::K_ComponentManager()
	{

	}

	K_ComponentManager::~K_ComponentManager()
	{

	}

	bool K_ComponentManager::createComponent()
	{
		K_Component* comp;

		//...

		if (comp->hasUpdate())
		{
			m_toUpdate.push_back(comp);
		}
		
		//Successful
		return true;
	}

	bool K_ComponentManager::destroyComponent(K_Component* p_toDestroy)
	{
		if (p_toDestroy != nullptr)
		{
			if (p_toDestroy->hasUpdate()) // && isActive
			{
				//find in update list and remove
				for (auto it = m_toUpdate.begin(); it != m_toUpdate.end(); ++it)
				{
					if (*it == p_toDestroy)
					{
						m_toUpdate.erase(it);
						delete p_toDestroy;
						return true;
					}
				}

				return false;
			}

			delete p_toDestroy;
			return true;
		}
		else
		{
			return false;
		}
	}

	void K_ComponentManager::updateComponents()
	{

	}
}