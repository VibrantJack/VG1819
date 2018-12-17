/*
@Rock
This class handles button texture in world space
basically same as clickablebutton except this is extended from clickable
*/

#pragma once

#include "kitten/QuadRenderable.h"
#include "kitten\mouse picking\Clickable.h"
#include "UI\UIObject.h"
#include "ActionSelect.h"

namespace unit
{
	class ActionButton : public kitten::Clickable
	{
	protected:
		kitten::QuadRenderable* m_render;
		ActionSelect* m_select;

		std::string m_regularTexture;
		std::string m_highlightedTexture;

	public:
		ActionButton();
		~ActionButton();

		virtual void start() override;

		virtual void onDisabled() override;

		void onClick() override;
		virtual void onHoverStart() override;
		virtual void onHoverEnd() override;

		void setRegularTexture(const std::string& p_tex) { m_regularTexture = p_tex; }
		void setHighlightedTexture(const std::string& p_tex) { m_highlightedTexture = p_tex; }
	};

}
