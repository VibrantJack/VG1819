#include "NetworkingMenuUI.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_ComponentManager.h"

#include "kitten/mouse picking/ClickableUI.h"
#include "kitten/mouse picking/ClickableFrame.h"
#include "UI\UIObject.h"

#include "NetworkHostButton.h"
#include "NetworkJoinButton.h"

namespace userinterface
{
	NetworkingMenuUI::NetworkingMenuUI()
	{
		
	}

	NetworkingMenuUI::~NetworkingMenuUI()
	{

	}

	// Change to K_Component start()
	void NetworkingMenuUI::start()
	{
		kitten::K_ComponentManager* compMan = kitten::K_ComponentManager::getInstance();
		assert(compMan != nullptr);

		kitten::Transform* parent = &m_attachedObject->getTransform();

		// Create ClickableUI for JoinButton
		kitten::K_GameObject* joinButton = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		joinButton->getTransform().scale2D(170, 100);
		joinButton->getTransform().place2D(555, 185);
		joinButton->addComponent(compMan->createComponent("ClickableFrame"));
		joinButton->addComponent(compMan->createComponent("NetworkJoinButton")); // ClickableUI Component
		joinButton->getTransform().setParent(parent);

		// Create ClickableUI for HostButton
		kitten::K_GameObject* hostButton = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		hostButton->getTransform().scale2D(170, 100);
		hostButton->getTransform().place2D(555, 395);
		hostButton->addComponent(compMan->createComponent("ClickableFrame"));
		hostButton->addComponent(compMan->createComponent("NetworkHostButton")); // ClickableUI Component		
		hostButton->getTransform().setParent(parent);
	}
}