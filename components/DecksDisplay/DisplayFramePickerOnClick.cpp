#include "DisplayFramePickerOnClick.h"
#include "components/DecksDisplayFrame.h"
#include "kibble/databank/databank.hpp"
#include "components/DeckInitializingComponent.h"

void DisplayFramePickerOnClick::onClick()
{
	m_parent->pickDisplayedObject(this->m_attachedObject);
}