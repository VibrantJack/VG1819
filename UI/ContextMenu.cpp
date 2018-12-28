#include "ContextMenu.h"
#include "kitten\InputManager.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_GameObjectManager.h"
#include <iostream>

namespace userinterface
{
	ContextMenu::ContextMenu(int p_padding, int p_margain, fillType p_ft) : UIElement("texture/ui/blankFrame.tga")
	{
		m_ft = p_ft;
		m_padding = p_padding;
		setPivotType(piv_TopLeft);
	}

	ContextMenu::ContextMenu() : UIElement("textures/ui/blankFrame.tga")
	{
		m_width = 100;
		m_height = 20;
		m_padding = 0;
	}

	ContextMenu::~ContextMenu()
	{
		
	}
	 
	void ContextMenu::start()
	{
		getTransform().scale2D(m_width, m_height);
		defineVerts();
		setEnabled(true);
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
		int offset = m_padding;
		int currentX = offset + pos.x;
		int currentY = offset + pos.y;
		m_width = m_padding * 2;
		m_height = m_padding * 2;
	
		for (Row* r : m_rows)
		{
			for (kitten::K_GameObject* GO : r->elements)
			{
				if (GO != nullptr)
				{
					GO->getTransform().place(currentX, currentY, 0.1f);
					if (m_ft == ft_Vertical || r->type == rt_OneElement)
					{
						currentY -= (r->height + r->contentMargin);
					}
					else if (r->type == rt_FillRow)
					{
						currentX += (r->width + r->contentMargin);
					}
					GO->setEnabled(true);
				}
			}
		}
		getTransform().scale2D(m_width, m_height);
	}
}