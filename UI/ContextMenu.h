#pragma once
#include "UIElement.h"

namespace userinterface
{
	class ContextMenu : public UIElement
	{
	public:

		enum widthType {
			wt_Static,
			wt_WrapContent
		};

		enum heightType {
			ht_Static,
			ht_WrapContent
		};

		enum fillType {
			ft_List,
			ft_HorizontalList,
		};

		//rendering stuff
		ContextMenu(int p_width, int p_height, int p_padding, int p_margain, widthType p_wt, heightType p_ht, fillType p_ft);
		ContextMenu();
		~ContextMenu();
		void start() override;
		void setWidthType(widthType p_wt);
		void setHeightType(heightType p_ht);
		void setFillType(fillType p_ft);

	protected:
		int m_margin, m_padding, m_width, m_height, m_longestInnerX, m_tallestInnerY;
		widthType m_wt;
		heightType m_ht;
		fillType m_ft;
	};
}
