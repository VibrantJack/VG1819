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

	void UIRenderable::addToStaticRender(const puppy::Texture* p_texNeeded, puppy::TexturedVertex p_data[], int p_numElements)
	{
		puppy::StaticRenderables::getInstance()->addToUIRender(this, p_texNeeded, p_data, p_numElements);
	}

	void UIRenderable::addToDynamicRender()
	{
		puppy::Renderer::getInstance()->addUIToRender(this);
	}

	void UIRenderable::removeFromStaticRender(const puppy::Texture* p_tex)
	{
		puppy::StaticRenderables::getInstance()->removeFromUIRender(this, p_tex);
	}

	void UIRenderable::removeFromDynamicRender()
	{
		puppy::Renderer::getInstance()->removeUIFromRender(this);
	}
}