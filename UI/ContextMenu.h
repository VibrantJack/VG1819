#pragma once
#include "UIElement.h"
#include "kitten\K_GameObject.h"
#include <vector>


namespace userinterface
{
	class ContextMenu : public UIElement
	{
	public:

		enum rowType {
			rt_OneElement,
			rt_Overflow,
		};

		//rendering stuff
		ContextMenu(int p_padding);
		ContextMenu();
		~ContextMenu();

	protected:
		int m_padding, m_width, m_height;

		struct Row {
			rowType type;
			std::list<kitten::K_GameObject*> elements;
			int margin, width, height;
		};

		//all rows in the context
		std::vector<Row*> m_rows;

		void start() override;
		Row* addRow(const rowType p_rt);
		void arrange();
	};
}
