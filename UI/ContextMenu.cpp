#include "ContextMenu.h"
#include "kitten\InputManager.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_GameObjectManager.h"
#include <iostream>

namespace userinterface
{
	ContextMenu::ContextMenu(int p_padding) : UIElement("texture/ui/blankFrame.tga")
	{
		m_padding = p_padding;
		m_height = m_padding * 2;
		m_width = m_padding * 2;
		setPivotType(piv_TopLeft);
		setTexBehaviour(tbh_Repeat);
	}

	ContextMenu::ContextMenu() : UIElement("textures/ui/blankFrame.tga")
	{
		m_padding = 0;
		m_height = 0;
		m_width = 0;
		setPivotType(piv_TopLeft);
		setTexBehaviour(tbh_Repeat);
	}

	ContextMenu::~ContextMenu()
	{
		
	}
	 
	void ContextMenu::start()
	{
		getTransform().scale2D(m_width, m_height);
	}

	ContextMenu::Row* ContextMenu::addRow( const rowType p_rt )
	{
		Row* r = new Row();
		r->type = p_rt;
		m_rows.push_back(r);
		return r;
	}

	void ContextMenu::arrange()
	{
		glm::vec3 pos = getTransform().getTranslation();
		int offsetX = pos.x + m_padding;
		int offsetY = pos.y - m_padding;
	
		for (Row* r : m_rows)
		{
			if (r->type == rt_OneElement) {

				offsetY -= r->margin;
				for (ctxElement em : r->elements)
				{
					if (em.GO != nullptr)
					{
						em.GO->getTransform().place2D(offsetX, offsetY);
						offsetY -= r->height;
						m_height += ((r->margin * 2) + r->height);
					}
					if (m_width < (r->width + 2 * m_padding))
					{
						m_width = (r->width + 2 * m_padding);
					}

				}
			}
			else if (r->type == rt_Overflow)
			{
				offsetX += r->margin;
				offsetY -= r->margin;
				m_height += ((r->margin * 2) + r->height);

				for (ctxElement em : r->elements)
				{
					if (em.GO != nullptr)
					{
						em.GO->getTransform().place2D(offsetX, offsetY);
						if (!em.isText)
						{
							glm::vec2 scale2d = em.GO->getTransform().getScale2D();
							offsetX += r->margin + scale2d.x;
						}
						else {
							int width = em.GO->getComponent<puppy::TextBox>()->getBoxWidth();
							offsetX += r->margin + width;
						}
					}
				}
				offsetX = m_padding + pos.x;
			}
			else if (r->type == rt_Blank)
			{
				m_height += (r->height + (2 * r->margin));
			}
		}
		getTransform().scale2D(m_width, m_height + m_padding);

		defineVerts();
		setEnabled(true);
	}
}