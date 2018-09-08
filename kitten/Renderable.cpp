#include "Renderable.h"
#include "puppy\Renderer.h"

namespace kitten
{
	Renderable::Renderable()
	{
		puppy::Renderer::getInstance()->addToRender(this);
	}

	Renderable::~Renderable()
	{
		puppy::Renderer::getInstance()->removeFromRender(this);
	}
}