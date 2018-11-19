#include "NetworkingMenuUI.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_ComponentManager.h"

#include "kitten/mouse picking/ClickableUI.h"
#include "kitten/mouse picking/ClickableFrame.h"

#include "NetworkHostButton.h"
#include "NetworkJoinButton.h"

namespace userinterface
{
	NetworkingMenuUI::NetworkingMenuUI(const char* p_pathToTex) : UIFrame(p_pathToTex)
	{

	}

	NetworkingMenuUI::~NetworkingMenuUI()
	{

	}

	// Change to K_Component start()
	void NetworkingMenuUI::start()
	{
		kitten::Transform* parent = &m_attachedObject->getTransform();

		// Creating Host Button
		kitten::K_GameObject* connectButton = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		connectButton->getTransform().setParent(parent);
		connectButton->getTransform().scale2D(170, 100);
		connectButton->getTransform().place2D(420, 310);

		K_Component* buttonObj = kitten::K_ComponentManager::getInstance()->createComponent("Frame"); // UIFrame : UIElement
		userinterface::UIFrame* buttonFrame = static_cast<userinterface::UIFrame*>(buttonObj);
		buttonFrame->setTexture("textures/ui/host_button.tga");
		connectButton->addComponent(buttonObj);


		K_Component* buttonCF = kitten::K_ComponentManager::getInstance()->createComponent("ClickableFrame"); // ClickableFrame : K_Component
		K_Component* clickUI = kitten::K_ComponentManager::getInstance()->createComponent("NetworkHostButton"); // ClickableUI : K_Component
		connectButton->addComponent(buttonCF);
		connectButton->addComponent(clickUI);

		kitten::ClickableFrame* cfCasted = static_cast<kitten::ClickableFrame*>(buttonCF);
		kitten::ClickableUI* cUI = static_cast<kitten::ClickableUI*>(clickUI);
		cfCasted->addCLickable(cUI);
		// End creating Host Button

		// Creating Join Game Button
		kitten::K_GameObject* joinButton = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		joinButton->getTransform().setParent(parent);
		joinButton->getTransform().scale2D(170, 100);
		joinButton->getTransform().place2D(690, 310);

		K_Component* joinButtonObj = kitten::K_ComponentManager::getInstance()->createComponent("Frame"); // UIFrame : UIElement
		userinterface::UIFrame* joinButtonFrame = static_cast<userinterface::UIFrame*>(joinButtonObj);
		joinButtonFrame->setTexture("textures/ui/join_button.tga");
		joinButton->addComponent(joinButtonObj);


		//K_Component* joinButtonCF = kitten::K_ComponentManager::getInstance()->createComponent("ClickableFrame"); // ClickableFrame : K_Component
		//K_Component* joinClickUI = kitten::K_ComponentManager::getInstance()->createComponent("NetworkJoinButton"); // ClickableUI : K_Component
		//joinButton->addComponent(joinButtonCF);
		//joinButton->addComponent(joinClickUI);

		//kitten::ClickableFrame* jcfCasted = static_cast<kitten::ClickableFrame*>(joinButtonCF);
		//NetworkJoinButton* joinButtonComponent = static_cast<NetworkJoinButton*>(joinClickUI);
		//jcfCasted->addCLickable(joinButtonComponent);

		kitten::ClickableFrame* jcfCasted = static_cast<kitten::ClickableFrame*>(kitten::K_ComponentManager::getInstance()->createComponent("ClickableFrame"));
		NetworkJoinButton* joinButtonComponent = static_cast<NetworkJoinButton*>(kitten::K_ComponentManager::getInstance()->createComponent("NetworkJoinButton"));
		jcfCasted->addCLickable(joinButtonComponent);

		joinButton->addComponent(jcfCasted);
		joinButton->addComponent(joinButtonComponent);
		// End creating Join Game Button
	}

	void NetworkingMenuUI::addButton(ClickableUI* p_button)
	{

	}
}