#pragma once
#include "UIElement.h"
#include "kitten\K_GameObject.h"
#include <vector>


namespace userinterface
{
	class ContextMenu : public UIElement
	{
	public:

		enum fillType {
			ft_Vertical,
			ft_Horizontal,
			ft_Both
		};

		enum rowType {
			rt_OneElement,
			rt_FillRow,
			rt_Overflow,
		};

		//rendering stuff
		ContextMenu(int p_padding, int p_margain, fillType p_ft);
		ContextMenu();
		~ContextMenu();

	protected:
		int m_padding, m_width, m_height, m_longestInnerX, m_tallestInnerY;

		struct Row {
			rowType type;
			std::list<kitten::K_GameObject*> elements;
			int contentMargin, padding, width, height;
		};

		std::vector<Row*> m_rows;
		fillType m_ft;

		void start() override;
		Row* addRow(const rowType p_rt);
		void arrange();
	};
}
