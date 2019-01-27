#pragma once
#include "kitten\K_Common.h"
#include "ui\UIElement.h"

namespace userinterface
{
	class SquareBorder : public UIElement
	{
	public:
		SquareBorder();
		~SquareBorder();
		void start() override;
	};
}

