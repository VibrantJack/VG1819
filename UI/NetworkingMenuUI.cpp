#include "NetworkingMenuUI.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_ComponentManager.h"

#include "kitten/mouse picking/ClickableUI.h"
#include "kitten/mouse picking/ClickableFrame.h"

#include "ui/NetworkHostButton.h"

namespace userinterface
{
	NetworkingMenuUI::NetworkingMenuUI(const char* p_pathToTex) : UIFrame(p_pathToTex)
	{

	}

	NetworkingMenuUI::~NetworkingMenuUI()
	{

	}

	void NetworkingMenuUI::init()
	{
		kitten::K_GameObject* connectButton = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		connectButton->getTransform().scale2D(170, 100);
		connectButton->getTransform().place2D(555, 310);

		K_Component* buttonObj = kitten::K_ComponentManager::getInstance()->createComponent("ButtonFrame");
		connectButton->addComponent(buttonObj);

		K_Component* buttonCF = kitten::K_ComponentManager::getInstance()->createComponent("ClickableFrame");
		K_Component* clickUI = kitten::K_ComponentManager::getInstance()->createComponent("NetworkHostButton");
		connectButton->addComponent(buttonCF);
		connectButton->addComponent(clickUI);

		kitten::ClickableFrame* cfCasted = static_cast<kitten::ClickableFrame*>(buttonCF);
		kitten::ClickableUI* cUI = static_cast<kitten::ClickableUI*>(clickUI);
		cfCasted->addCLickable(cUI);

		buttonCF->start();
		clickUI->start();
	}
}