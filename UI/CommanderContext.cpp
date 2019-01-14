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

		//TODO
		//I want to be able to datadrive values like this
		int winX, winY;
		winY = inMan->getWindowHeight();
		winX = inMan->getWindowWidth();
		//put it on the screen

		//TO DO, DATADRIVE THIS POSITIONAL DATA.
		getTransform().place(0.0f, winY, -0.05);
		setPivotType(piv_TopLeft);
		setTexBehaviour(tbh_Repeat);

		//TO DO, DATADRIVE THE PADDING FOR CHANGING OUTSIDE OF CODE
		m_padding = 15;
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
		r->height = nameComp->getBoxHeight() + 25;
		r->width = winX;
		r->margin = rowMargin;
		r->elements.push_back(GO_name);


		Row* row2 = addRow(rt_Overflow);
		kitten::K_GameObject* hpIcon = kibble::getGameObjectDataParserInstance()->getGameObject("UI/Icon.txt");
		userinterface::UIElement* hpComp = hpIcon->getComponent<userinterface::UIElement>();
		hpComp->setTexture("textures/ui/icons/stat_icons/stat_icons/hp.png");

		row2->height = 25;
		row2->elements.push_back(hpIcon);

		kitten::K_GameObject* hpText = kibble::getGameObjectDataParserInstance()->getGameObject("context_textbox.txt");
		puppy::TextBox* hptxtComp = hpText->getComponent<puppy::TextBox>();
		hptxtComp->setText(std::to_string(m_attachedCommander->m_attributes["hp"]));

		row2->elements.push_back(hpText);

		kitten::K_GameObject* spIcon = kibble::getGameObjectDataParserInstance()->getGameObject("UI/Icon.txt");
		userinterface::UIElement* spComp = spIcon->getComponent<userinterface::UIElement>();
		spComp->setTexture("textures/ui/icons/stat_icons/stat_icons/movement.png");

		row2->elements.push_back(spIcon);

		kitten::K_GameObject* spText = kibble::getGameObjectDataParserInstance()->getGameObject("context_textbox.txt");
		puppy::TextBox* sptxtComp = spText->getComponent<puppy::TextBox>();
		sptxtComp->setText(std::to_string(m_attachedCommander->m_attributes["mv"]));

		row2->elements.push_back(spText);

		

		arrange();
	}
}
