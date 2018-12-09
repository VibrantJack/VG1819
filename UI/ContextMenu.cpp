#include "ContextMenu.h"
#include "kitten\InputManager.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_GameObjectManager.h"
#include <iostream>

namespace userinterface
{
	ContextMenu::ContextMenu(int p_width, int p_height, int p_padding, int p_margain, fillType p_ft) : UIElement("texture/ui/blankFrame.tga")
	{
		m_ft = p_ft;
		m_width = p_width;
		m_height = p_height;
		m_padding = p_padding;
		m_margin = p_margain;
	}

	ContextMenu::ContextMenu() : UIElement("textures/ui/blankFrame.tga")
	{
		m_width = 100;
		m_height = 20;
		m_padding = 0;
		m_margin = 0;
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

	void ContextMenu::addRow( const rowType p_rt )
	{
		Row r;
		r.type = p_rt;
	}

	bool ContextMenu::addToRow(const int p_index, kitten::K_GameObject* p_GO)
	{
		try {
			m_rows.at(p_index).elements.push_back(p_GO);
		}
		catch (const std::out_of_range& error) {
			std::cerr << "Row Does Not Exist - OutOfBoundsException: " << error.what() << '\n';
			return false;
		}
		return true;
	}

	bool ContextMenu::addToEnd(kitten::K_GameObject* p_GO)
	{
		Row r = m_rows.at(m_rows.size() - 1);
		if (r.type == rt_OneElement || m_ft == ft_Vertical)
		{
			addRow(rt_ForceOverflow);
			r = m_rows.at(m_rows.size() - 1);
			r.elements.push_back(p_GO);
		}
		else {
			r.elements.push_back(p_GO);
		}
	}

	/* TODO 
			add configuration method for positioning all of the elements in the context menu to be rendered properly.
	*/
}