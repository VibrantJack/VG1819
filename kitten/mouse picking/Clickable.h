#pragma once

#include "kitten\K_Component.h"
#include "ClickableBox.h"
#include <glm/glm.hpp>

namespace kitten
{
	class Clickable : public K_Component
	{
	protected:
		Clickable();
		ClickableBox* m_attachedBox;
	public:
		
		virtual ~Clickable();

		virtual void start() override; // You MUST call this method or add yourself as a ClickableBox when overriding this class

		virtual void onClick();
		virtual void onHoverStart();
		virtual void onHoverEnd();
	};
}