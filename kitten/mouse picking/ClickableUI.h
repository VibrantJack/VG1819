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
	public:
		ClickableUI();
		~ClickableUI();

		virtual void start() override; // You MUST call this method or add yourself as a ClickableBox when overriding this class

		virtual void onClick();
		virtual void onHoverStart();
		virtual void onHoverEnd();
	};
}
