#include "PromptPopUpSuccessOnClick.h"
#include "components/PromptPopUp.h"

void PromptPopUpSuccessOnClick::onClick()
{
	PromptPopUp::getActiveInstance()->triggerSuccess();
}
