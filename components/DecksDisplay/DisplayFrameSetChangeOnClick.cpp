#include "DisplayFrameSetChangeOnClick.h"
#include "components/DecksDisplayFrame.h"

void DisplayFrameSetChangeOnClick::onClick()
{
	if(m_parent != nullptr)
		m_parent->offsetCurrentSet(this->m_offset);
}