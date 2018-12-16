#pragma once

#include "kitten\mouse picking\ClickableUI.h"
#include "UI\UIObject.h"

namespace userinterface
{

	class ClickableButton : public kitten::ClickableUI
	{
	protected:
		UIObject* m_uiObject;

		std::string m_regularTexture;
		std::string m_highlightedTexture;

	public:
		ClickableButton();
		~ClickableButton();

		virtual void start() override;

		virtual void onDisabled() override;

		virtual void onHoverStart() override;
		virtual void onHoverEnd() override;

		void setRegularTexture(const std::string& p_tex) { m_regularTexture = p_tex; }
		void setHighlightedTexture(const std::string& p_tex) { m_highlightedTexture = p_tex; }
	};

}
