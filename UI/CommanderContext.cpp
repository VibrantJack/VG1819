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

		setEnabled(false);

		defineVerts();
	}
}
