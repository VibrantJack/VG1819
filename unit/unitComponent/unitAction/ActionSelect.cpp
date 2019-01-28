#include "ActionSelect.h"
#include "kitten/K_GameObjectManager.h"
#include "kitten/K_ComponentManager.h"
#include "ActionButtonStore.h"
#include "board/tile/TileInfo.h"
#include <iostream>

unit::ActionSelect::ActionSelect(const std::pair<int, int> p_to, const std::pair<int, int> p_co)
	:m_action("NONE"),
	m_unit(nullptr),
	m_text(nullptr),
	m_cdtext(nullptr),
	m_txtOffset(p_to),
	m_cdOffset(p_co),
	m_active(true)
{
}

unit::ActionSelect::~ActionSelect()
{
}

void unit::ActionSelect::start()
{
	m_text = kitten::K_GameObjectManager::getInstance()->createNewGameObject();

	kitten::K_ComponentManager* comMan = kitten::K_ComponentManager::getInstance();
	puppy::TextBox* textbox = static_cast<puppy::TextBox*>(comMan->createComponent("TextBox"));
	m_text->addComponent(textbox);

	//make text object be child of frame object
	m_text->getTransform().setParent(&getTransform());
	m_text->getTransform().setIgnoreParent(false);

	//m_text->getTransform().place(0, 0, -0.1);
	m_text->getTransform().move(m_txtOffset.first, m_txtOffset.second, m_textZ);

	//set property
	textbox->setColor(1, 1, 1);
	textbox->setText(m_action);

	//---------------------------

	//cd text
	m_cdtext = kitten::K_GameObjectManager::getInstance()->createNewGameObject();

	puppy::TextBox* cdtextbox = static_cast<puppy::TextBox*>(comMan->createComponent("TextBox"));
	m_cdtext->addComponent(cdtextbox);

	//make text object be child of frame object
	m_cdtext->getTransform().setParent(&getTransform());
	m_cdtext->getTransform().setIgnoreParent(false);

	//m_text->getTransform().place(0, 0, -0.1);
	m_cdtext->getTransform().move(m_cdOffset.first, m_cdOffset.second, m_textZ);

	//set property
	cdtextbox->setColor(1, 1, 1);
	if (m_cd > 0)
		cdtextbox->setText("CD:" + std::to_string(m_cd));
	else
		cdtextbox->setText("");

	ClickableUI::start();
}

void unit::ActionSelect::setUnit(Unit * p_u)
{
	m_unit = p_u;
}

void unit::ActionSelect::setAction(const std::string & p_a, int p_cd)
{
	m_cd = p_cd;
	m_action = p_a;
		
	if(m_text != nullptr)
		m_text->getComponent<puppy::TextBox>()->setText(m_action);

	if (m_cdtext != nullptr)
	{
		if (m_cd > 0)
			m_cdtext->getComponent<puppy::TextBox>()->setText("CD:" + std::to_string(m_cd));
		else
			m_cdtext->getComponent<puppy::TextBox>()->setText("");
	}
}

void unit::ActionSelect::act()
{
	assert(m_action != "NONE");
	assert(m_unit != nullptr);

	std::cout << "select " << m_action << std::endl;

	if (m_action == "Turn End")
	{
		m_unit->playerSkipTurn();
	}
	else if (m_action == "Move")
	{
		m_unit->move();
	}
	else if (m_action == "ManipulateTile")
	{
		m_unit->manipulateTile();
	}
//	else if (m_action == "Summon")
//	{
//		m_unit->summonUnit();
//	}
	else if (m_action == "Join")
	{
		m_unit->join();
	}
	else if (m_action == "For test: Level Up")
	{
		m_unit->levelup();
		std::cout << "current lv is " << m_unit->m_attributes["lv"] << std::endl;
	}
	else if (m_action == "For test: Destroy")
	{
		m_unit->destroy();
		std::cout << "Unit Destroyed" << std::endl;
	}
	else if (m_action == "For test: Set DP")
	{
		m_unit->getTile()->getComponent<TileInfo>()->setDemonicPresence(true);
	}
	else
	{
		m_unit->useAbility(m_action);
	}
}

void unit::ActionSelect::onClick()
{
	if (m_cd > 0 || !m_active)
		return;

	act();
	m_storage->hide();
}

void unit::ActionSelect::onDisabled()
{
	m_text->getComponent<puppy::TextBox>()->setText("NONE");
	m_cdtext->getComponent<puppy::TextBox>()->setText("");
	m_active = true;
}
