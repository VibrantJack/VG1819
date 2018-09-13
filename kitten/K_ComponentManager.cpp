#include "K_ComponentManager.h"
#include "K_Component.h"

#include "Camera.h"
#include "CubeRenderable.h"

namespace kitten
{
	K_ComponentManager* K_ComponentManager::sm_instance = nullptr;

	K_ComponentManager::K_ComponentManager()
	{

	}

	K_ComponentManager::~K_ComponentManager()
	{

	}

	//Temporary unitl Kibble is ready
	K_Component* K_ComponentManager::createComponent(const std::string& p_componentName)
	{
		K_Component* comp;

		//Kibble version -1.0
		if (p_componentName == "Camera")
		{
			comp = new Camera();
		}
		else if (p_componentName == "CubeRenderable")
		{
			comp = new CubeRenderable("textures/crap/cartoon_cobble.tga");
		}
		else
		{
			//Not found..
			return nullptr;
		}

		if (comp->hasUpdate())
		{
			m_toUpdate.push_back(comp);
		}
		
		//Successful
		return comp;
	}

	//bool mostly for debugging
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