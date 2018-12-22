#pragma once

#include "kitten\K_Component.h"
#include "ClickableBox.h"
#include <glm/glm.hpp>

namespace kitten
{
	class Clickable : public K_Component
	{
	protected:
		Clickable(bool p_enabledOnPause = false);
		ClickableBox* m_attachedBox;
		bool m_enabledOnPause;
	public:
		
		virtual ~Clickable();

		virtual void start() override; // You MUST call this method or add yourself as a ClickableBox when overriding this class

		virtual void onClick();
		virtual void onHoverStart();
		virtual void onHoverEnd();

		void setEnabledOnPause(bool p_enable) { m_enabledOnPause = p_enable; }
		bool isEnabledOnPause() { return m_enabledOnPause; }
	};
}