#include "UIFrame.h"
#include "puppy\Renderer.h"
#include "puppy\StaticRenderables.h"
#include <iostream>


//austin's UI frame

namespace userinterface
{

	UIFrame::UIFrame(const char* p_pathToTex) : UIElement(p_pathToTex) //default params
	{

	}

	UIFrame::UIFrame(const char* p_pathToTex, pivotType p_pivot, textureBehaviour p_texBehaviour) : UIElement(p_pathToTex, p_pivot, p_texBehaviour)
	{

	}

	UIFrame::UIFrame(nlohmann::json & p_json) : userinterface::UIElement(p_json)
	{
	}

	UIFrame::~UIFrame()
	{
		
	}

	void UIFrame::addToFrame(UIObject* p_ouiToAdd)
	{
		m_innerObjects.push_back(p_ouiToAdd);
	}

	void UIFrame::removeFromFrame(UIObject* p_ouiToRemove)
	{
		auto end = m_innerObjects.end();
		for (auto it = m_innerObjects.begin(); it != end; ++it)
		{
			if (*it == p_ouiToRemove)
			{
				m_innerObjects.erase(it);
				return;
			}
		}
	}

	void UIFrame::onDisabled()
	{
		UIElement::onDisabled();
		setInnerObjectsEnabled(false);
	}

	void UIFrame::onEnabled()
	{
		UIElement::onEnabled();
		setInnerObjectsEnabled(true);
	}

	void UIFrame::setInnerObjectsEnabled(bool p_enabled)
	{
		auto end = m_innerObjects.end();
		for (auto it = m_innerObjects.begin(); it != end; ++it)
		{
			(*it)->setEnabled(p_enabled);
		}
	}
}

