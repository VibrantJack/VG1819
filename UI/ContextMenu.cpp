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
		sm_instances++;
		getTransform().scale2D(m_width, m_height);
		setEnabled(true);
	}

	ContextMenu::Row ContextMenu::addRow( const rowType p_rt )
	{
		Row r;
		r.type = p_rt;
		m_rows.push_back(r);
		arrange();
		return r;
	}

	bool ContextMenu::addToEnd(const kitten::K_GameObject* p_GO)
	{
		
	}  


	void ContextMenu::arrange()
	{
		int offset = m_padding;
		int currentX = offset;
		int currentY = -offset;
		getTransform().scale2D(m_padding * 2, m_padding * 2);
	
		for (Row r : m_rows)
		{
			for (kitten::K_GameObject* GO : r.elements)
			{
				GO->getComponent<UIElement>()->setPivotType(UIElement::piv_TopLeft);
				if (GO != nullptr)
				{
					GO->getTransform().place2D(currentX, currentY);
					if (m_ft == ft_Vertical || r.type == rt_OneElement)
					{
						currentY -= (r.height - r.contentMargin);
					}
					else if (r.type == rt_FillRow)
					{
						currentX += (r.width + r.contentMargin);
					}
				}
			}
		}
	}
}