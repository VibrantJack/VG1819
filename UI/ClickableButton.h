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
		std::string m_inactiveTexture;

		bool m_active;

	public:
		ClickableButton(bool p_enabledOnPause = false);
		~ClickableButton();

		virtual void start() override; // Call ClickableButton::start() if you override this!

		virtual void onDisabled() override;

		virtual void onHoverStart() override;
		virtual void onHoverEnd() override;
		virtual void onPause() override;

		void setRegularTexture(const std::string& p_tex) { m_regularTexture = p_tex; }
		void setHighlightedTexture(const std::string& p_tex) { m_highlightedTexture = p_tex; }
		void setInactiveTexture(const std::string& p_tex) { m_inactiveTexture = p_tex; }
		void setActive(bool p_a);
	};

}
