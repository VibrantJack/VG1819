#pragma once
#include "UI/ClickableButton.h"
namespace userinterface
{

	class DeactivatableClickableButton : public userinterface::ClickableButton
	{
	protected:
		UIObject* m_uiObject;

		std::string m_regularTexture;
		std::string m_highlightedTexture;
		std::string m_inactiveTexture;

		bool m_active;

	public:
		DeactivatableClickableButton(bool p_enabledOnPause = false);
		~DeactivatableClickableButton();

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