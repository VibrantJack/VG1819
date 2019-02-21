#include "TileInfoDisplayOnKeyPress.h"
#include "kitten\K_GameObject.h"

TileInfoDisplayOnKeyPress::TileInfoDisplayOnKeyPress(char p_key) : m_key(p_key)
{

}

TileInfoDisplayOnKeyPress::TileInfoDisplayOnKeyPress(nlohmann::json & p_json) : kitten::K_Component(p_json)
{
	if (JSONHAS("key")) m_key = LOOKUPCHAR("key");
}

TileInfoDisplayOnKeyPress::~TileInfoDisplayOnKeyPress()
{

}

void TileInfoDisplayOnKeyPress::start()
{
	m_inputMan = input::InputManager::getInstance();
	assert(m_inputMan != nullptr);

	m_tileInfoDisplay = m_attachedObject->getComponent<puppy::TextBox>();
	assert(m_tileInfoDisplay != nullptr);
}

void TileInfoDisplayOnKeyPress::update()
{
	if (m_inputMan->keyDown(m_key) && !m_inputMan->keyDownLast(m_key))
	{
		m_tileInfoDisplay->setEnabled(!m_tileInfoDisplay->isEnabled());
	}
}