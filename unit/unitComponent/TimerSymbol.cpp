#include "TimerSymbol.h"

unit::TimerSymbol::TimerSymbol():
	m_timeTex(std::vector<std::string>(11)),
	m_quad(nullptr)
{
}

unit::TimerSymbol::~TimerSymbol()
{
}

void unit::TimerSymbol::addTexture(int p_num, const std::string & p_texPath)
{
	m_timeTex[p_num] = p_texPath;
}

void unit::TimerSymbol::changeTexture(int p_num)
{
	if (m_quad == nullptr)
		m_tex = m_timeTex[p_num];
	else
		m_quad->setTexture(m_timeTex[p_num].c_str());
}

void unit::TimerSymbol::start()
{
	m_quad = m_attachedObject->getComponent<kitten::SimpleQuadRenderable>();
	m_quad->setTexture(m_tex.c_str());
}
