#include "K_ComponentManager.h"
#include "K_Component.h"
#include "K_GameObject.h"

#include "Camera.h"
#include "CubeRenderable.h"
#include "QuadRenderable.h"
#include "_Project\MoveByMouseRightClickDrag.h"
#include "_Project\ZoomByMouseWheel.h"
#include "_Project\DebugPrintOnce.h"
#include "gameworld\GrassLandInfoComponent.h"
#include "_Project\PrintWhenClicked.h"
#include "_Project\DestroyOnClick.h"
#include "unit/unitComponent/UnitGraphic.h"
#include "_Project\BoardCreator.h"
#include "_Project\ManipulateTileOnClick.h"
#include "_Project\UseAbilityWhenClicked.h"
#include "_Project\FPSCalc.h"
#include "puppy\Text\TextBox.h"
#include "unit/unitComponent/UnitMove.h"
#include "unit/unitComponent/UnitClickable.h"
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
		if (p_componentName == "Camera")// Datadriven
		{
			comp = new Camera();
		}
		else if (p_componentName == "CubeRenderable")// Datadriven
		{
			comp = new CubeRenderable("textures/tiles/MISSING.tga");
		}
		else if (p_componentName == "QuadRenderable")// Datadriven
		{
			comp = new QuadRenderable("textures/tiles/Grassland.tga");
		}
		else if (p_componentName == "StaticQuadRenderable")// QuadRenderable Variant
		{
			comp = new QuadRenderable("textures/tiles/MISSING.tga", true);
		}
		else if (p_componentName == "Grassland")// datadriven
		{
			comp = new gameworld::GrasslandInfoComponent();
		}
		else if (p_componentName == "MoveByMouseRightClickDrag")// Datadriven
		{
			comp = new MoveByMouseRightClickDrag(0.005f);
		}
		else if (p_componentName == "ZoomByMouseWheel")// Datadriven
		{
			comp = new ZoomByMouseWheel(2.0f);
		}
		else if (p_componentName == "DebugPrintOnce") // Datadriven
		{
			comp = new DebugPrintOnce("Some Message, kinda useless until we can change this easily");
		}
		else if (p_componentName == "PrintWhenClicked")// Datadriven
		{
			comp = new PrintWhenClicked("I WAS CLICKED!!");
		}
		else if (p_componentName == "DestroyOnClick") // Datadriven
		{
			comp = new DestroyOnClick();
		}
		else if (p_componentName == "ClickableBox")
		{
			comp = new ClickableBox(glm::vec3(-0.5f, 0, -0.5f), glm::vec3(0.5f, 0, 0.5f));
		}
		else if (p_componentName == "ClickableBoxBox")
		{
			comp = new ClickableBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f));
		}
		else if (p_componentName == "ClickableBoxForPointUnit")
		{
			comp = new ClickableBox(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 2.0f, 0.0f));
		}
		else if (p_componentName == "ClickableBoxForCubeUnit")
		{
			comp = new ClickableBox(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.5f, 3.0f, 0.0f));
		}
		else if (p_componentName == "UnitMove")
		{
			comp = new unit::UnitMove();
		}
		else if (p_componentName == "UnitClickable")
		{
			comp = new unit::UnitClickable();
		}
		else if (p_componentName == "UnitGraphic")//hard code, need special function for unit graphic
		{
			comp = new unit::UnitGraphic(unit::point, "textures/unit/Default.tga");
		}
		else if (p_componentName == "BoardCreator")
		{
			comp = new BoardCreator();
		}
		else if (p_componentName == "ManipulateTileOnClick")
		{
			comp = new ManipulateTileOnClick();
		}
		else if (p_componentName == "UseAbilityWhenClicked")
		{
			comp = new UseAbilityWhenClicked();
		}
		else if (p_componentName == "FPSCalc")
		{
			comp = new FPSCalc();
		}
		else if (p_componentName == "TextBox")
		{
			comp = new puppy::TextBox(puppy::FontTable::getInstance()->getFont("../fonts/common_consolas.fnt"), "DEFAULT TEXT", 500, 500);
		}
		else
		{
			//Not found..
			assert(false);
			return nullptr;
		}

		m_toStart.push_back(comp);

		//Successful
		return comp;
	}

	K_Component* K_ComponentManager::createComponent(kibble::ComponentDataParser* data)
	{
		K_Component* comp = data->getComponentInternally();
		if (comp == nullptr) return nullptr;

		m_toStart.push_back(comp);

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

	void K_ComponentManager::destroyComponentImmediate(K_Component* p_toDestroy)
	{
		if (p_toDestroy->hasUpdate()) //&& isActive
		{
			removeFromUpdate(p_toDestroy);
		}

		if (!p_toDestroy->m_hasStarted)
		{
			removeFromStart(p_toDestroy);
		}

		p_toDestroy->m_attachedObject->removeComponent(p_toDestroy);

		delete (p_toDestroy);
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

	void K_ComponentManager::removeFromStart(const K_Component* p_toRemove)
	{
		for (auto it = m_toStart.begin(); it != m_toStart.cend(); ++it)
		{
			if (*it == p_toRemove)
			{
				m_toStart.erase(it);
				return;
			}
		}
	}

	void K_ComponentManager::updateComponents()
	{
		//Start components
		for (auto it = m_toStart.begin(); it != m_toStart.end(); it = m_toStart.erase(it))
		{
			(*it)->start();
			(*it)->m_hasStarted = true;
			if ((*it)->hasUpdate())
			{
				m_toUpdate.push_back(*it);
			}
		}

		//Delete queued deletions
		for (auto it = m_toDelete.begin(); it != m_toDelete.end(); it = m_toDelete.erase(it))
		{
			if ((*it)->hasUpdate()) //&& isActive
			{
				removeFromUpdate(*it);
			}

			if (!(*it)->m_hasStarted)
			{
				removeFromStart(*it);
			}

			(*it)->m_attachedObject->removeComponent(*it);

			delete (*it);

		}

		//Update components
		for (auto it = m_toUpdate.begin(); it != m_toUpdate.end(); ++it)
		{
			(*it)->update();
		}
	}
}