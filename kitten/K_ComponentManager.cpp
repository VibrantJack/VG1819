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
#include "_Project\DestroyOnClick.h"
#include "unit/unitComponent/UnitGraphic.h"
#include "_Project\UseAbilityWhenClicked.h"
#include "_Project\FPSCalc.h"
#include "puppy\Text\TextBox.h"
#include "unit/unitComponent/UnitMove.h"
#include "unit/unitComponent/UnitClickable.h"
//ui
#include "UI\CardUIO.h"
#include "UI\HandFrame.h"

#include "unit/InitiativeTracker/TrackerBlock.h"
#include "unit/InitiativeTracker/TrackerBlockClickable.h"
#include "unit/InitiativeTracker/TrackerPointer.h"
#include "unit/InitiativeTracker/PointerUI.h"
#include "kitten\mouse picking\ClickableFrame.h"
#include "components\PowerTracker.h"
#include "components\SelectAbility.h"
#include "networking\SpawnUnitOnKeyPress.h"
#include "networking\NetworkingConsoleMenu.h"
#include "kibble/json/Datatypes/ComponentDataType.hpp"

//board
#include "board/component/Highlighter.h"
#include "board/component/BoardCreator.h"
//clickable
#include "board/clickable/ManipulateTileOnClick.h"
#include "board/clickable/PrintWhenClicked.h"
#include "board/clickable/SendSelfOnClick.h"
//tile
#include "board/tile/TileInfo.h"
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
		} else if (p_componentName == "CubeRenderable")// Datadriven
		{
			comp = new CubeRenderable("textures/tiles/MISSING.tga");
		} else if (p_componentName == "QuadRenderable")// Datadriven
		{
			comp = new QuadRenderable("textures/tiles/Grassland.tga");
		} else if (p_componentName == "StaticQuadRenderable")// QuadRenderable Variant
		{
			comp = new QuadRenderable("textures/tiles/MISSING.tga", true);
		} else if (p_componentName == "Grassland")// datadriven
		{
			comp = new gameworld::GrasslandInfoComponent();
		} else if (p_componentName == "Frame")// Datadriven
		{
			comp = new userinterface::UIFrame("textures/ui/blankFrame.tga");
		} else if (p_componentName == "ClickableFrame")
		{
			comp = new kitten::ClickableFrame(glm::vec2(0, 0), glm::vec2(1, 1));
		} else if (p_componentName == "Hand")
		{
			comp = new userinterface::HandFrame("textures/ui/blankFrame.tga");
		} else if (p_componentName == "Card")
		{
			comp = new userinterface::CardUIO("textures/ui/cardBack.tga");
		}else if (p_componentName == "MoveByMouseRightClickDrag")// Datadriven
		{
			comp = new MoveByMouseRightClickDrag(0.005f);
		} else if (p_componentName == "ZoomByMouseWheel")// Datadriven
		{
			comp = new ZoomByMouseWheel(2.0f);
		} else if (p_componentName == "DebugPrintOnce") // Datadriven
		{
			comp = new DebugPrintOnce("Some Message, kinda useless until we can change this easily");
		} else if (p_componentName == "PrintWhenClicked")// Datadriven
		{
			comp = new PrintWhenClicked("I WAS CLICKED!!");
		} else if (p_componentName == "DestroyOnClick") // Datadriven
		{
			comp = new DestroyOnClick();
		} else if (p_componentName == "ClickableBox") // Datadriven
		{
			comp = new ClickableBox(glm::vec3(-0.5f, 0, -0.5f), glm::vec3(0.5f, 0, 0.5f));
		} else if (p_componentName == "ClickableBoxBox") // Datadriven
		{
			comp = new ClickableBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f));
		} else if (p_componentName == "ClickableBoxForPointUnit") // Datadriven
		{
			comp = new ClickableBox(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 2.0f, 0.0f));
		} else if (p_componentName == "ClickableBoxForCubeUnit") // Datadriven
		{
			comp = new ClickableBox(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.5f, 3.0f, 0.0f));
		} else if (p_componentName == "ClickableBoxForTrackerBlock") // Datadriven
		{
			comp = new ClickableBox(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		} else if (p_componentName == "UnitMove") // Datadriven
		{
			comp = new unit::UnitMove();
		} else if (p_componentName == "UnitClickable") // DataDriven
		{
			comp = new unit::UnitClickable();
		} else if (p_componentName == "UnitGraphic")//hard code, need special function for unit graphic, Data driven with these as defaults
		{
			comp = new unit::UnitGraphic(unit::point, "textures/unit/Default.tga");
		} else if (p_componentName == "ManipulateTileOnClick") // Datadriven
		{
			comp = new ManipulateTileOnClick();
		} else if (p_componentName == "UseAbilityWhenClicked")  // Datadriven
		{
			comp = new UseAbilityWhenClicked();
		} else if (p_componentName == "SendSelfOnClick") // DataDriven
		{
			comp = new SendSelfOnClick();
		} else if (p_componentName == "FPSCalc") // Datadriven
		{
			comp = new FPSCalc();
		} else if (p_componentName == "TextBox")  // Datadriven
		{
			comp = new puppy::TextBox(puppy::FontTable::getInstance()->getFont("../fonts/common_consolas.fnt"), "DEFAULT TEXT", 500, 500);
		} else if (p_componentName == "TextBoxAbilities")
		{
			comp = new puppy::TextBox(puppy::FontTable::getInstance()->getFont("../fonts/common_consolas.fnt"), "DEFAULT TEXT", 300, 500);
		} else if (p_componentName == "TrackerBlock") // Datadriven
		{
			comp = new unit::TrackerBlock();
		} else if (p_componentName == "TrackerBlockClickable") // Datadriven
		{
			comp = new unit::TrackerBlockClickable();
		} else if (p_componentName == "TrackerPointer") // Datadriven
		{
			comp = new unit::TrackerPointer();
		} else if (p_componentName == "PointerUI") // Datadriven
		{
			comp = new userinterface::PointerUI();
		} else if (p_componentName == "SelectAbility")
		{
			comp = new SelectAbility();
		} else if (p_componentName == "PowerTracker")
		{
			comp = new PowerTracker();
		}
		else if (p_componentName == "Highlighter")
		{
			comp = new Highlighter();
		}
		else if (p_componentName == "BoardCreator")
		{
			comp = new BoardCreator();
		}
		else if (p_componentName == "SpawnUnitOnKeyPress")
		{
			comp = new SpawnUnitOnKeyPress();
		}
		else if (p_componentName == "NetworkingConsoleMenu")
		{
			comp = new NetworkingConsoleMenu();
		}
		else
		{
			//Not found..
			assert(false);
			return nullptr;
		}

		m_toStart.insert(comp);

		//Successful
		return comp;
	}

	K_Component* K_ComponentManager::createComponent(nlohmann::json* p_jsonfile)
	{
		K_Component* comp = getRelatedComponentBy(p_jsonfile);
		if (comp == nullptr) return nullptr;

		m_toStart.insert(comp);

		//Successful
		return comp;
	}


	//bool mostly for debugging
	bool K_ComponentManager::destroyComponent(K_Component* p_toDestroy)
	{
		assert(p_toDestroy != nullptr);
		m_toDelete.insert(p_toDestroy);

		return true;
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

	void K_ComponentManager::addToUpdate(K_Component* p_toAdd)
	{
		m_toUpdate.insert(p_toAdd);
	}

	bool K_ComponentManager::removeFromUpdate(K_Component* p_toRemove)
	{
		//find in update list and remove
		m_toUpdate.erase(p_toRemove);

		return true;
	}

	void K_ComponentManager::addToStart(K_Component* p_toStart)
	{
		assert(!p_toStart->m_hasStarted);
		assert(m_toStart.find(p_toStart) == m_toStart.end());

		m_toStart.insert(p_toStart);
	}

	void K_ComponentManager::removeFromStart(K_Component* p_toRemove)
	{
		m_toStart.erase(p_toRemove);
	}

	void K_ComponentManager::queueAddToUpdate(K_Component* p_toAdd)
	{
		m_toAddToUpdate.push_back(p_toAdd);
	}

	void K_ComponentManager::queueRemovalFromUpdate(K_Component* p_toRemove)
	{
		m_toRemoveFromUpdate.push_back(p_toRemove);
	}

	void K_ComponentManager::updateComponents()
	{
		//Start components
		for (auto it = m_toStart.begin(); it != m_toStart.end(); it = m_toStart.erase(it))
		{
			(*it)->m_hasStarted = true;
			(*it)->start();
			if ((*it)->hasUpdate())
			{
				m_toUpdate.insert(*it);
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

		//Add queued components to update
		for (auto it = m_toAddToUpdate.begin(); it != m_toAddToUpdate.end(); it = m_toAddToUpdate.erase(it))
		{
			m_toUpdate.insert(*it);
		}

		//Update components
		auto updateEnd = m_toUpdate.cend();
		for (auto it = m_toUpdate.cbegin(); it != updateEnd; ++it)
		{
			(*it)->update();
		}

		//Remove queued components from update
		for (auto it = m_toRemoveFromUpdate.begin(); it != m_toRemoveFromUpdate.end(); it = m_toRemoveFromUpdate.erase(it))
		{
			removeFromUpdate(*it);
		}
	}
}