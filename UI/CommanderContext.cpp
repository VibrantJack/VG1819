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
#include "unit\Unit.h"
#include "kibble\databank\databank.hpp"
#include "ability\AbilityManager.h"
#include <string>
#include <map>



namespace userinterface
{
	//TO DO
	/*
		I need to make this support images more elegantly. I suppose just tossing in a blank frame would work
	*/
	CommanderContext::CommanderContext(): ContextMenu()
	{
		
	}

	CommanderContext::~CommanderContext()
	{
		for (Row* r : m_rows)
		{
			delete r;
		}
	}

	void CommanderContext::attachCommander(unit::Unit* p_unit)
	{
		m_attachedCommander = p_unit;
	}

	void CommanderContext::start()
	{
		//commander in context
		m_attachedCommander = kibble::getUnitFromId(13);
		//screen position stuff
		input::InputManager* inMan = input::InputManager::getInstance();
		//game object positions

		int posX, posY;
		posY = inMan->getWindowHeight();
		int posY2 = posY - 50; //posy2 is the true y coord
		//put it on the screen

		//TO DO, DATADRIVE THIS POSITIONAL DATA.
		getTransform().place(25, posY2, -0.05);
		setPivotType(piv_TopLeft);
		setTexBehaviour(tbh_Repeat);

		//TO DO, DATADRIVE THE PADDING FOR CHANGING OUTSIDE OF CODE
		m_padding = 10;
		static int rowMargin = 5;

		defineVerts();

		//make a GO based on the json textbox data ->
		kitten::K_GameObject* GO_name = kibble::getGameObjectDataParserInstance()->getGameObject("commander_name.txt");
		puppy::TextBox* nameComp = GO_name->getComponent<puppy::TextBox>();
		nameComp->setText(m_attachedCommander->m_name);
		nameComp->setEnabled(true);

		//new row
		Row* r = addRow(rt_OneElement);
		//PLEASE NOTE. YOU MUST DEFINE THESE VARIABLES.
		r->height = nameComp->getBoxHeight();
		r->width = nameComp->getBoxWidth();
		r->margin = rowMargin;
		r->elements.push_back(GO_name);

		//get attributes to show
		//TO DO, MAKE THIS MORE ATTRACTIVE
		int curAtr = 0;
		std::string curAtrStr = "";
		std::string statLine = "| ";
		for (auto atr : m_attachedCommander->m_attributes)
		{
			curAtr = atr.second;
			curAtrStr = atr.first;
			statLine += (curAtrStr + "-" + std::to_string(curAtr) + " | ");
		}

		r = addRow(rt_Overflow);
		kitten::K_GameObject* GO_stats = kibble::getGameObjectDataParserInstance()->getGameObject("context_textbox.txt");
		puppy::TextBox* statsComp = GO_stats->getComponent<puppy::TextBox>();
		statsComp->setText(statLine);
		statsComp->setEnabled(true);

		//PLEASE NOTE. YOU MUST DEFINE THESE VARIABLES.
		r->height = statsComp->getBoxHeight();
		r->width = statsComp->getBoxWidth();
		r->margin = rowMargin;
		r->elements.push_back(GO_stats);

		arrange();
	}
}
