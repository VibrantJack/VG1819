#include "DecksDisplaySetChangeOnClick.h"
#include "components/DecksDisplayFrame.h"

void DecksDisplaySetChangeOnClick::onClick()
{
	if(DecksDisplayFrame::getActiveInstance() != nullptr)
		DecksDisplayFrame::getActiveInstance()->offsetCurrentSet(this->m_offset);
}