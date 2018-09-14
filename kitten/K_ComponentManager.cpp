#include "K_ComponentManager.h"
#include "K_Component.h"

#include "Camera.h"
#include "CubeRenderable.h"
#include "_Project\MoveByMouseRightClickDrag.h"
#include "_Project\ZoomByMouseWheel.h"

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
		else if (p_componentName == "MoveByMouseRightClickDrag")
		{
			comp = new MoveByMouseRightClickDrag(0.005f);
		}
		else if (p_componentName == "ZoomByMouseWheel")
		{
			comp = new ZoomByMouseWheel(2.0f);
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
				if (removeFromUpdate(p_toDestroy))
				{
					delete p_toDestroy;
					return true;
				}

				delete p_toDestroy;
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	//@TODO: Optimize adding and removing of components to update!
	void K_ComponentManager::addToUpdate(K_Component* p_toAdd)
	{
		m_toUpdate.push_back(p_toAdd);
	}

	bool K_ComponentManager::removeFromUpdate(const K_Component* p_toRemove)
	{
		//find in update list and remove
		for (auto it = m_toUpdate.begin(); it != m_toUpdate.end(); ++it)
		{
			if (*it == p_toRemove)
			{
				m_toUpdate.erase(it);
				return true;
			}
		}

		return false;
	}

	void K_ComponentManager::updateComponents()
	{
		for (auto it = m_toUpdate.begin(); it != m_toUpdate.end(); ++it)
		{
			(*it)->update();
		}
	}
}