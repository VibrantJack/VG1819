#include "PromptPopUpDeclineOnClick.h"
#include "components/PromptPopUp.h"

void PromptPopUpDeclineOnClick::onClick()
{
	PromptPopUp::getActiveInstance()->triggerDecline();
}
