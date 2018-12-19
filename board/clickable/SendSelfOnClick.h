#pragma once

#include <string>
#include "kitten/mouse picking/Clickable.h"
#include "kitten\event_system\EventManager.h"

class SendSelfOnClick : public kitten::Clickable
{
private:
	bool m_isDisabled;
public:
	SendSelfOnClick();
	virtual ~SendSelfOnClick();

	//virtual void start() override;
	virtual void onClick() override;
	virtual void onHoverStart() override;
	virtual void onHoverEnd() override;

	void pausedListener(kitten::Event::EventType p_type, kitten::Event* p_data);
};
