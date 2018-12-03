#include "DecksDisplayPickerOnClick.h"
#include "components/DecksDisplayFrame.h"

void DecksDisplayPickerOnClick::onClick()
{
	DecksDisplayFrame::getActiveInstance()->pickDisplayedDeck(this->m_attachedObject);
}