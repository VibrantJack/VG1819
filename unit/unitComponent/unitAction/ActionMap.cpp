#include "ActionMap.h"
#include "ActionButtonStore.h"
#include "board/tile/TileInfo.h"

unit::ActionMap::ActionMap()
{
	m_funcMap["Turn End"] = &ActionMap::end;
	m_funcMap["Move"] = &ActionMap::move;
	m_funcMap["Join"] = &ActionMap::join;
	m_funcMap["For test: Level Up"] = &ActionMap::lvUp;
	m_funcMap["For test: Destroy"] = &ActionMap::destory;
	m_funcMap["For test: Set DP"] = &ActionMap::setDP;
	m_funcMap["Action"] = &ActionMap::action;
}

unit::ActionMap::~ActionMap()
{
}

void unit::ActionMap::act(ActionSelect * p_s)
{
	std::string action = p_s->m_action;

	if (action == "NONE")
		return;

	auto found = m_funcMap.find(action);
	if (found != m_funcMap.end())
	{
		(this->*(found->second))(p_s);//command on funcmap
	}
	else
	{
		p_s->m_unit->useAbility(action);//ability
		p_s->m_storage->hide();
	}
}

void unit::ActionMap::end(ActionSelect* p_s)
{
	p_s->m_unit->playerSkipTurn();
	p_s->m_storage->hide();
}

void unit::ActionMap::move(ActionSelect* p_s)
{
	p_s->m_unit->move();
	p_s->m_storage->hide();
}

void unit::ActionMap::join(ActionSelect* p_s)
{
	p_s->m_unit->join();
	p_s->m_storage->hide();
}

void unit::ActionMap::action(ActionSelect* p_s)
{
	if (p_s->m_actionShow)
	{
		p_s->m_storage->hideAction();
		p_s->m_actionShow = false;
	}
	else
	{
		p_s->m_storage->displayAction(p_s->m_attachedObject);
		p_s->m_actionShow = true;
	}
}

void unit::ActionMap::useAbility(ActionSelect* p_s)
{
	p_s->m_unit->useAbility(p_s->m_action);
	p_s->m_storage->hide();
}

void unit::ActionMap::lvUp(ActionSelect* p_s)
{
	p_s->m_unit->levelup();
	p_s->m_storage->hide();
}

void unit::ActionMap::destory(ActionSelect* p_s)
{
	p_s->m_unit->destroy();
	p_s->m_storage->hide();
}

void unit::ActionMap::setDP(ActionSelect* p_s)
{
	p_s->m_unit->getTile()->getComponent<TileInfo>()->setDemonicPresence(true);
	p_s->m_storage->hide();
}