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
		kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Client_Commander_Loaded, this);
	}


	void CommanderContext::start()
	{
		kitten::EventManager::getInstance()->addListener(
			kitten::Event::EventType::Client_Commander_Loaded,
			this,
			std::bind(&CommanderContext::commanderLoadListener, this, std::placeholders::_1, std::placeholders::_2));
		//default	
		attachCommander(kibble::getUnitInstanceFromId(13));
	}

	void CommanderContext::commanderLoadListener(kitten::Event::EventType p_type, kitten::Event* p_event)
	{
		attachCommander(p_event->getGameObj(COMMANDER_GO_KEY)->getComponent<unit::Unit>());
	}

	void CommanderContext::attachCommander(unit::Unit* p_unit)
	{
		m_attachedCommander = p_unit;

		//screen position stuff
		input::InputManager* inMan = input::InputManager::getInstance();
		//game object positions

		//TODO
		//I want to be able to datadrive values like this
		int winX, winY;
		winY = inMan->getWindowHeight();
		winX = inMan->getWindowWidth();
		//put it on the screen

		kitten::K_GameObject* portrait = kibble::getGameObjectDataParserInstance()->getGameObject("ui/commander_portrait.txt");
		userinterface::UIElement* portraitComp = portrait->getComponent<userinterface::UIElement>();
		portraitComp->setTexture(m_attachedCommander->getPortraitTexturePath().c_str());
		portrait->getTransform().place2D(0.0f, winY);

		//TO DO, DATADRIVE THIS POSITIONAL DATA.
		getTransform().place(100.0f, winY, -0.05);
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

		ctxElement nmEm;
		nmEm.isText = true;
		nmEm.GO = GO_name;

		//new row
		Row* r = addRow(rt_OneElement);
		//PLEASE NOTE. YOU MUST DEFINE THESE VARIABLES.
		r->height = nameComp->getBoxHeight() + 25;
		r->width = winX;
		r->margin = rowMargin;
		r->elements.push_back(nmEm);


		Row* row2 = addRow(rt_Overflow);
		kitten::K_GameObject* hpIcon = kibble::getGameObjectDataParserInstance()->getGameObject("UI/Icon.txt");
		userinterface::UIElement* hpComp = hpIcon->getComponent<userinterface::UIElement>();
		hpComp->setTexture("textures/ui/icons/stat_icons/stat_icons/hp.png");

		ctxElement hpEm;
		hpEm.GO = hpIcon;

		row2->height = 15;
		row2->elements.push_back(hpEm);

		kitten::K_GameObject* hpText = kibble::getGameObjectDataParserInstance()->getGameObject("context_number_3digits.txt");
		puppy::TextBox* hptxtComp = hpText->getComponent<puppy::TextBox>();
		hptxtComp->setText(std::to_string(m_attachedCommander->m_attributes["hp"]));

		ctxElement hptxtEm;
		hptxtEm.GO = hpText;
		hptxtEm.isText = true;

		row2->elements.push_back(hptxtEm);

		kitten::K_GameObject* spIcon = kibble::getGameObjectDataParserInstance()->getGameObject("UI/Icon.txt");
		userinterface::UIElement* spComp = spIcon->getComponent<userinterface::UIElement>();
		spComp->setTexture("textures/ui/icons/stat_icons/stat_icons/movement.png");

		ctxElement spEm;
		spEm.GO = spIcon;

		row2->elements.push_back(spEm);

		kitten::K_GameObject* spText = kibble::getGameObjectDataParserInstance()->getGameObject("context_number_3digits.txt");
		puppy::TextBox* sptxtComp = spText->getComponent<puppy::TextBox>();
		sptxtComp->setText(std::to_string(m_attachedCommander->m_attributes["mv"]));

		ctxElement sptxtEm;
		sptxtEm.GO = spText;
		sptxtEm.isText = true;

		row2->elements.push_back(sptxtEm);

		kitten::K_GameObject* inIcon = kibble::getGameObjectDataParserInstance()->getGameObject("UI/Icon.txt");
		userinterface::UIElement* inComp = inIcon->getComponent<userinterface::UIElement>();
		inComp->setTexture("textures/ui/icons/stat_icons/stat_icons/initiative.png");

		ctxElement inEm;
		inEm.GO = inIcon;

		row2->elements.push_back(inEm);

		kitten::K_GameObject* inText = kibble::getGameObjectDataParserInstance()->getGameObject("context_number_3digits.txt");
		puppy::TextBox* intxtComp = inText->getComponent<puppy::TextBox>();
		intxtComp->setText(std::to_string(m_attachedCommander->m_attributes["in"]));

		ctxElement intxtEm;
		intxtEm.GO = inText;
		intxtEm.isText = true;

		row2->elements.push_back(intxtEm);


		arrange();
	}
}
