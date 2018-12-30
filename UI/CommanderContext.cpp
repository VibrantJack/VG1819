#include "CommanderContext.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_GameObject.h"
#include "puppy\Text\Font.h"
#include "puppy\Text\FontTable.h"
#include "puppy\Text\TextBox.h"
#include "puppy\Text\TextTable.h"
#include "puppy\Text\PivotTextBox.h"
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

		getTransform().place(50, posY2, -0.05);
		setPivotType(piv_TopLeft);
		setTexBehaviour(tbh_Repeat);

		m_padding = 10;
		static int contextWidth = 200;
		static int rowMargin = 50;

		defineVerts();

		kitten::K_GameObjectManager* GOMan = kitten::K_GameObjectManager::getInstance();
		kitten::K_ComponentManager* CompMan = kitten::K_ComponentManager::getInstance();

		kitten::K_GameObject* GO_name = kibble::getGameObjectDataParserInstance()->getGameObject("commander_name.txt");
		puppy::TextBox* nameComp = GO_name->getComponent<puppy::TextBox>();
		nameComp->setText("Commander");
		nameComp->setEnabled(true);
		glm::vec2 scale = GO_name->getTransform().getScale2D();

		Row* r = addRow(rt_OneElement);
		//PLEASE NOTE. YOU MUST DEFINE THESE VARIABLES.
		r->height = 60;
		r->width = contextWidth;
		r->margin = 0;
		r->elements.push_back(GO_name);

		r = addRow(rt_Overflow);
		kitten::K_GameObject* GO_stats = kibble::getGameObjectDataParserInstance()->getGameObject("context_textbox.txt");
		puppy::TextBox* statsComp = GO_stats->getComponent<puppy::TextBox>();
		statsComp->setText("HP: x ");
		statsComp->setEnabled(true);
		glm::vec2 scale = GO_name->getTransform().getScale2D();

		r = addRow(rt_OneElement);
		//PLEASE NOTE. YOU MUST DEFINE THESE VARIABLES.
		r->height = 60;
		r->width = contextWidth;
		r->margin = 0;
		r->elements.push_back(GO_stats);

		kitten::K_GameObject* GO_flair = kibble::getGameObjectDataParserInstance()->getGameObject("context_textbox.txt");
		puppy::TextBox* flairComp = GO_flair->getComponent<puppy::TextBox>();
		int flairHeight = flairComp->getBoxHeight();
		int flairWidth = flairComp->getBoxWidth();
		flairComp->setBoxBounds(flairWidth, flairHeight);
		flairComp->setText("Ability: asdasdasdasd");
		flairComp->setEnabled(true);
		glm::vec2 scale = GO_name->getTransform().getScale2D();

		Row* r = addRow(rt_OneElement);
		//PLEASE NOTE. YOU MUST DEFINE THESE VARIABLES.
		r->height = flairHeight;
		r->width = flairWidth;
		r->margin = 0;
		r->elements.push_back(GO_flair);

		arrange();
	}
}
