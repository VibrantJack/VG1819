#include "ActionButtonStore.h"
#include "kitten/K_GameObjectManager.h"
#include "kitten/InputManager.h"
#include "UI/ClickableButton.h"

unit::ActionButtonStore::ActionButtonStore()
{
	m_show = false;
	m_buttonScaleX = 0;
	m_buttonScaleY = 0;
}

unit::ActionButtonStore::~ActionButtonStore()
{
}

void unit::ActionButtonStore::display(Unit * p_u)
{
	//set unit
	m_unit = p_u;

	//get start position
	input::InputManager* im = input::InputManager::getInstance();
	m_lastX = im->getMouseXPos();
	m_lastY = im->getMouseYOpenGLPos();
	//get window size
	int winX = im->getWindowWidth();
	int winY = im->getWindowHeight();
	int centerX = winX / 2;
	int centerY = winY / 2;
	//get button scale
	if (m_buttonScaleX <= 0 || m_buttonScaleY <= 0)
	{
		getButtonScale();
	}
	assert(m_buttonScaleX > 0 && m_buttonScaleY > 0);
	//change x position
	if (m_lastX > centerX)
		m_lastX = m_lastX - m_buttonScaleX;


	//start of list
	m_index = 0;

	//move
	if (m_unit->m_attributes["base_mv"] > 0)
		setButton("Move");

	//normal ability
	setAbility();

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
		{
			setButton("Join");

			//for test
			setButton("For test: Level Up");
		}
	}
	
	setButton("Turn End");

	setButton("For test: Destroy");

	m_show = true;

	//change y position
	if (im->getMouseYOpenGLPos() < centerY)
	{
		int delta = m_index * m_buttonScaleY;
		for (int i = 0; i < m_index; i++)
		{
			m_buttonList[i]->getTransform().move2D(0,delta);
		}
	}
}

void unit::ActionButtonStore::hide()
{
	if (m_show)
	{
		for (int i = 0; i < m_buttonList.size(); i++)
		{
			m_buttonList[i]->setEnabled(false);
		}
		m_show = false;
	}
	
}

void unit::ActionButtonStore::createNewButton()
{
	kitten::K_GameObject* ab = kitten::K_GameObjectManager::getInstance()->createNewGameObject("unit_action_button.json");
	ab->getComponent<ActionSelect>()->setStorage(this);
	//ab->setEnabled(false);
	m_buttonList.push_back(ab);
}

void unit::ActionButtonStore::setButton(const std::string & p_msg, int p_cd)
{
	kitten::K_GameObject* go;
	if (m_index >= m_buttonList.size())//create new button if not enough
		createNewButton();
	go = m_buttonList[m_index];

	m_lastY = m_lastY - go->getTransform().getScale2D().y;

	go->getTransform().place2D(m_lastX, m_lastY);

	ActionSelect* a = go->getComponent<ActionSelect>();
	a->setAction(p_msg, p_cd);
	a->setUnit(m_unit);

	if (p_cd > 0)
	{
		userinterface::ClickableButton* cb = go->getComponent<userinterface::ClickableButton>();
		cb->setActive(false);
	}

	go->setEnabled(true);

	m_index++;
}

void unit::ActionButtonStore::getButtonScale()
{
	if (m_buttonList.size() == 0)//no button exist
	{
		createNewButton();
	}

	kitten::K_GameObject* ab = m_buttonList[0];
	auto scale = ab->getTransform().getScale2D();

	m_buttonScaleX = scale.x;
	m_buttonScaleY = scale.y;
}

void unit::ActionButtonStore::setAbility()
{
	int lv = m_unit->m_attributes[UNIT_LV];
	for (auto it : m_unit->m_ADList)
	{
		if (it.second->m_intValue[UNIT_LV] <= lv)//check level
		{//check cooldown
			int cd = m_unit->checkCD(it.first);
			setButton(it.first,cd);
		}
	}
}
