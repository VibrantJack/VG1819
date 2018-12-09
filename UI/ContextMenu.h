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
			rt_ForceOverflow
		};

		//rendering stuff
		ContextMenu(int p_width, int p_height, int p_padding, int p_margain, fillType p_ft);
		ContextMenu();
		~ContextMenu();

		void start() override;
		void addRow(const rowType p_rt);
		bool addToRow(const int p_index, kitten::K_GameObject* p_GO); //must be a UIObject or Textbox
		bool addToEnd(kitten::K_GameObject* p_GO);

	protected:
		int m_margin, m_padding, m_width, m_height, m_longestInnerX, m_tallestInnerY;
		
		struct Row {
			rowType type;
			std::list<kitten::K_GameObject*> elements;
		};

		std::vector<Row> m_rows;
		fillType m_ft;
	};
}
