#include "K_ComponentManager.h"
#include "K_Component.h"
#include "K_GameObject.h"

#include "Camera.h"
#include "CubeRenderable.h"
#include "_Project\MoveByMouseRightClickDrag.h"
#include "_Project\ZoomByMouseWheel.h"
#include "_Project\DebugPrintOnce.h"
#include "gameworld\GrassLandInfoComponent.h"
#include "_Project\PrintWhenClicked.h"
#include "unit/unitComponent/UnitGraphic.h"

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
			comp = new CubeRenderable("textures/tiles/MISSING.tga");
		}
		else if (p_componentName == "Grassland")
		{
			comp = new gameworld::GrasslandInfoComponent();
		}
		else if (p_componentName == "MoveByMouseRightClickDrag")
		{
			comp = new MoveByMouseRightClickDrag(0.005f);
		}
		else if (p_componentName == "ZoomByMouseWheel")
		{
			comp = new ZoomByMouseWheel(2.0f);
		}
		else if (p_componentName == "DebugPrintOnce")
		{
			comp = new DebugPrintOnce("Some Message, kinda useless until we can change this easily");
		}
		else if (p_componentName == "PrintWhenClicked")
		{
			comp = new PrintWhenClicked(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), "I WAS CLICKED!!");
		}
		else if (p_componentName == "UnitGraphic")
		{
			comp = new unit::UnitGraphic(unit::point,"texture/placeholder.tga");
		}
		else
		{
			//Not found..
			assert(false);
			return nullptr;
		}

		if (comp->hasUpdate())
		{
			m_toUpdate.push_back(comp);
		}


		//Successful
		return comp;
	}

	K_Component* K_ComponentManager::createComponent(kibble::ComponentDataParser* data)
	{
		K_Component* comp = data->getComponentInternally();
		if (comp == nullptr) return nullptr;

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
			m_toDelete.push_back(p_toDestroy);
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

		for (auto it = m_toDelete.begin(); it != m_toDelete.end(); it = m_toDelete.erase(it))
		{
			if ((*it)->hasUpdate()) //&& isActive
			{
				removeFromUpdate(*it);
				(*it)->m_attachedObject->removeComponent(*it);
			}
			
			delete (*it);
			
		}
	}
}