#pragma once

#include "kitten\K_Component.h"
#include "ClickableFrame.h"
#include <glm\glm.hpp>

namespace kitten
{
	class ClickableUI : public K_Component
	{		
	protected:
		ClickableFrame* m_attachedFrame;
		bool m_enabledOnPause;
	public:
		ClickableUI(nlohmann::json& p_json);
		ClickableUI(bool p_enabledOnPause = false);
		~ClickableUI();

		virtual void start() override; // You MUST call this method or add yourself as a ClickableBox when overriding this class

		virtual void onClick();
		virtual void onHoverStart();
		virtual void onHoverEnd();
		virtual void release();

		virtual void onPause();
		virtual void onUnpause();
		void setEnabledOnPause(bool p_enable) { m_enabledOnPause = p_enable; }
		bool isEnabledOnPause() { return m_enabledOnPause; }
	};
}
