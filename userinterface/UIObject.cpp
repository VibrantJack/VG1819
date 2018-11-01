#include "UIObject.h"
#include "puppy\Renderer.h"
#include "puppy\StaticRenderables.h"

namespace userinterface
{
	UIObject::UIObject(const char* p_pathToTex) : UIElement(p_pathToTex) 
	{
		//no extra stuff yet
	};

	UIObject::UIObject(const char* p_pathToTex, pivotType p_pivot, textureBehaviour p_texBahaviour) : UIElement(p_pathToTex, p_pivot, p_texBahaviour)
	{
		//no extra stuff yet
	};

	UIObject::~UIObject()
	{

	}

	UIFrame* UIObject::getParentFrame()
	{
		return m_parentFrame;
	}

	void UIObject::onDisabled()
	{
		removeFromDynamicRender();
	}

	void UIObject::onEnabled()
	{
		addToDynamicRender();
	}
}