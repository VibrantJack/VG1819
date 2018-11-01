#include "HandFrame.h"
#include "glm/glm.hpp"
#include "kitten/K_GameObject.h"
#include "UIObject.h"

namespace userinterface
{
	HandFrame::HandFrame(const char* p_pathToTex) : UIFrame(p_pathToTex)
	{

	}

	HandFrame::~HandFrame()
	{

	}

	void HandFrame::addCardToEnd(UIObject* p_cardToAdd)
	{
		m_innerObjects.push_back(p_cardToAdd);
		reorderAllCards();
	}

	void HandFrame::addCardToFront(UIObject* p_cardToAdd)
	{
		m_innerObjects.push_front(p_cardToAdd);
		reorderAllCards();
	}

	void HandFrame::removeCard(UIObject* p_cardToRemove)
	{
		auto end = m_innerObjects.end();
		for (auto it = m_innerObjects.begin(); it != end; ++it)
		{
			if (*it = p_cardToRemove)
			{
				m_innerObjects.erase(it);
			}
		}
		reorderAllCards();
	}

	void HandFrame::reorderAllCards()
	{
		auto end = m_innerObjects.end();
		for (auto it = m_innerObjects.begin(); it != end; ++it)
		{
			(*it)->getTransform();
		}

	}
}