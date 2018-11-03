#include "ui/HandFrame.h"
#include "glm/glm.hpp"
#include "kitten/K_GameObject.h"
#include "UIObject.h"
#include "kitten/Transform.h"

namespace userinterface
{
	HandFrame::HandFrame(const char* p_pathToTex) : UIFrame(p_pathToTex)
	{
		m_totalCards = 0;
	}

	HandFrame::~HandFrame()
	{

	}

	void HandFrame::addCardToEnd(UIObject* p_cardToAdd)
	{
		m_innerObjects.push_back(p_cardToAdd);
		m_totalCards++;
		reorderAllCards();
	}

	//TODO: Assign parent frame when object is added
	void HandFrame::addCardToFront(UIObject* p_cardToAdd)
	{
		m_innerObjects.push_front(p_cardToAdd);
		m_totalCards++;
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
		m_totalCards--;
		reorderAllCards();
	}

	void HandFrame::reorderAllCards()
	{
		kitten::Transform T = getTransform();
		glm::vec3 trans = T.getTranslation();
		float differ = 0.0f;
		auto end = m_innerObjects.end();
		for (auto it = m_innerObjects.begin(); it != end; ++it)
		{
			(*it)->getTransform().place2D(trans.x + differ, trans.y);
			differ += 0.11f;
		}
		differ = 0.0f;
	}
}