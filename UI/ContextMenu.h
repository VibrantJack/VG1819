#pragma once
#include "UIElement.h"
#include "kitten\K_GameObject.h"
#include "puppy\Text\TextBox.h"
#include <vector>


namespace userinterface
{
	class ContextMenu : public UIElement
	{
	public:

		enum rowType {
			rt_OneElement,
			rt_Overflow,
			rt_Blank,
		};

		//rendering stuff
		ContextMenu(int p_padding);
		ContextMenu();
		~ContextMenu();

	protected:
		int m_padding, m_width, m_height;

		struct ctxElement {
			bool isText = false;
			kitten::K_GameObject* GO;
		};

		struct Row {
			rowType type;
			std::list<ctxElement> elements;
			int margin, width, height;
		};

		//all rows in the context
		std::vector<Row*> m_rows;

		void start() override;
		Row* addRow(const rowType p_rt);
		void arrange();
	};
}
