#pragma once

#include <string>
#include "kitten/mouse picking/Clickable.h"

namespace unit
{
	class TrackerBlockClickable : public kitten::Clickable
	{
	public:
		TrackerBlockClickable();
		virtual ~TrackerBlockClickable();

		virtual void onClick() override;
		virtual void onHoverStart() override;
		virtual void onHoverEnd() override;
	};
}