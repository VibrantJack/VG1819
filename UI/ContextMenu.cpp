#include "ContextMenu.h"
#include "kitten\InputManager.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_GameObjectManager.h"

namespace userinterface
{
	ContextMenu::ContextMenu(int p_width, int p_height, int p_padding, int p_margain, widthType p_wt, heightType p_ht, fillType p_ft) : UIElement("texture/ui/blankFrame.tga")
	{
		m_wt = p_wt;
		m_ht = p_ht;
		m_ft = p_ft;
		m_width = p_width;
		m_height = p_height;
		m_padding = p_padding;
		m_margin = p_margain;
	}

	ContextMenu::ContextMenu() : UIElement("textures/ui/blankFrame.tga")
	{
		m_wt = wt_WrapContent;
		m_ht = ht_WrapContent;
		m_ft = ft_List;
		m_width = 100;
		m_height = 10;
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

	void ContextMenu::setWidthType(widthType p_wt)
	{
		m_wt = p_wt;
	}
	void ContextMenu::setHeightType(heightType p_ht)
	{
		m_ht = p_ht;
	}
	void ContextMenu::setFillType(fillType p_ft)
	{
		m_ft = p_ft;
	}

}