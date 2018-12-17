#include "ActionButtonStore.h"
#include "kitten/K_GameObjectManager.h"
#include "kitten/InputManager.h"
unit::ActionButtonStore::ActionButtonStore()
{
}

unit::ActionButtonStore::~ActionButtonStore()
{
}

void unit::ActionButtonStore::display(Unit * p_u)
{
	//set unit
	m_unit = p_u;

	//get start position
	m_lastX = input::InputManager::getInstance()->getMouseXPos();
	m_lastY = input::InputManager::getInstance()->getMouseYOpenGLPos();

	//start of list
	m_index = 0;

	//move
	if (m_unit->m_attributes["base_mv"] > 0)
		setButton("Move");

	//normal ability
	for (auto it : p_u->m_ADList)
	{
		setButton(it.first);
	}

	//join
	//commander action
	if (p_u->isCommander())
	{
		setButton("ManipulateTile");
		setButton("Summon");
	}
	else
	{
		bool canJoin = true;
		for (std::string it : m_unit->m_tags)//strucutre can't join to another unit
		{
			if (it == STRUCTURE)
			{
				canJoin = false;
				break;
			}
		}
		if (canJoin)
			setButton("Join");
	}
	
	setButton("Turn End");

	/*
	//for test
	addAbility("For test: Level Up");
	addAbility("For test: Destroy");*/
}

void unit::ActionButtonStore::hide()
{
	for (int i = 0; i < m_buttonList.size(); i++)
	{
		m_buttonList[i]->setEnabled(false);
	}
}

void unit::ActionButtonStore::createNewButton()
{
	kitten::K_GameObject* ab = kitten::K_GameObjectManager::getInstance()->createNewGameObject("unit_action_button.json");
	ab->getComponent<ActionSelect>()->setStorage(this);
	ab->setEnabled(false);
	m_buttonList.push_back(ab);
}

void unit::ActionButtonStore::setButton(const std::string & p_msg)
{
	kitten::K_GameObject* go;
	if (m_index >= m_buttonList.size())//create new button if not enough
		createNewButton();
	go = m_buttonList[m_index];

	m_lastY = m_lastY + go->getTransform().getScale2D().y;
	go->getTransform().place2D(m_lastX, m_lastY);

	ActionSelect* a = go->getComponent<ActionSelect>();
	a->setAction(p_msg);
	a->setUnit(m_unit);

	go->setEnabled(true);

	m_index++;
}
