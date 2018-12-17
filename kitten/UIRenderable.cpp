#include "UIRenderable.h"
#include "puppy\StaticRenderables.h"
#include "puppy\Renderer.h"

namespace kitten
{
	UIRenderable::UIRenderable()
	{
		
	}

	UIRenderable::~UIRenderable()
	{
		
	}

	void UIRenderable::addToStaticUIRender(const puppy::Texture* p_texNeeded, puppy::TexturedVertex p_data[], int p_numElements)
	{
		puppy::StaticRenderables::getInstance()->addToUIRender(this, p_texNeeded, p_data, p_numElements);
	}

	void UIRenderable::addToDynamicUIRender()
	{
		puppy::Renderer::getInstance()->addUIToRender(this);
	}

	void UIRenderable::removeFromStaticUIRender(const puppy::Texture* p_tex)
	{
		puppy::StaticRenderables::getInstance()->removeFromUIRender(this, p_tex);
	}

	void UIRenderable::removeFromDynamicUIRender()
	{
		puppy::Renderer::getInstance()->removeUIFromRender(this);
	}
}