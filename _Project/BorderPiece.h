#pragma once
#include "UI\UIElement.h"
namespace userinterface
{
	class BorderPiece : public UIElement
	{
	public:
		
		~BorderPiece();

		enum BorderPlacement
		{
			bp_Top,
			bp_Right,
			bp_Bot,
			bp_Left,
			bp_TopLeft,
			bp_TopRight,
			bp_BotRight,
			bp_BotLeft
		};

		BorderPiece(BorderPlacement p_bp);

	protected:
		void defineVerts() override;
		BorderPlacement m_borderPlacement;
	};
}

