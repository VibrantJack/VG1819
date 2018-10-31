#include "Renderable.h"
#include "puppy\Renderer.h"
#include "puppy\StaticRenderables.h"

namespace kitten
{
	Renderable::Renderable()
	{
		
	}

	Renderable::~Renderable()
	{
		
	}

	void Renderable::addToStaticRender(const puppy::Texture* p_texNeeded, puppy::TexturedVertex p_data[], int p_numElements)
	{
		puppy::StaticRenderables::getInstance()->addToRender(this, p_texNeeded, p_data, p_numElements);
	}

	void Renderable::addToDynamicRender()
	{
		puppy::Renderer::getInstance()->addToRender(this);
	}

	void Renderable::removeFromStaticRender(const puppy::Texture* p_tex)
	{
		puppy::StaticRenderables::getInstance()->removeFromRender(this, p_tex);
	}

	void Renderable::removeFromDynamicRender()
	{
		puppy::Renderer::getInstance()->removeFromRender(this);
	}
}