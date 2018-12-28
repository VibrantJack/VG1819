#include "CommanderContext.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_GameObject.h"
#include "puppy\Text\Font.h"
#include "puppy\Text\FontTable.h"
#include "puppy\Text\TextBox.h"
#include "puppy\Text\TextTable.h"
#include "kibble\kibble.hpp"
#include "kitten\InputManager.h"


namespace userinterface
{
	CommanderContext::CommanderContext(): ContextMenu()
	{
		
	}

	CommanderContext::~CommanderContext()
	{
	}

	void CommanderContext::start()
	{
		input::InputManager* inMan = input::InputManager::getInstance();
		int posX, posY;
		posY = inMan->getWindowHeight();
		int posY2 = posY - 50;
		getTransform().place2D(50, posY2);
		getTransform().scale2D(200, 100);
		setPivotType(piv_TopLeft);
		setTexBehaviour(tbh_Repeat);
		m_padding = 10;

		defineVerts();

		kitten::K_GameObjectManager* GOMan = kitten::K_GameObjectManager::getInstance();
		kitten::K_ComponentManager* CompMan = kitten::K_ComponentManager::getInstance();

		kitten::K_GameObject* GO_name = kibble::getGameObjectDataParserInstance()->getGameObject("context_textbox.txt");
		puppy::TextBox* nameComp = GO_name->getComponent<puppy::TextBox>();
		nameComp->setText("Temp");
		nameComp->setEnabled(true);

		Row* r = addRow(rt_OneElement);
		r->elements.push_back(GO_name);

		arrange();
	}
}
