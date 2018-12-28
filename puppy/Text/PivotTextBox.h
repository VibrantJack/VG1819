#pragma once
#include "puppy\Text\TextBox.h"
#include "UI\UIElement.h"

namespace puppy
{ 
	class UIElement;
	class PivotTextBox :
		public TextBox
	{
	public:
		PivotTextBox(Font* p_fontToUse, const std::string& p_text, float p_boxWidth, float p_boxHeight, userinterface::UIElement::pivotType m_piv, bool p_is3D = false);
		~PivotTextBox();

	private:
		userinterface::UIElement::pivotType m_piv;
		void constructQuad(int p_charId, int p_xPos, int p_yPos, TexturedVertex p_toSet[]) override;
	};


};

