#include "K_Renderable.h"
#include "puppy\Renderer.h"
#include "puppy\StaticRenderables.h"

namespace kitten
{
	K_Renderable::K_Renderable()
	{
		
	}

	K_Renderable::K_Renderable(nlohmann::json & p_json) : K_Component(p_json)
	{
	}

	K_Renderable::~K_Renderable()
	{
		
	}

	
}