#include "Renderer.h"

#include <algorithm>
#include <iostream>

namespace puppy
{
	std::multimap<const std::pair<const std::string*, const GLuint*>, Renderable*> Renderer::sm_toRender;

	//public static
	void Renderer::addToRender(Renderable* p_toAdd) 
	{	
		Renderer::sm_toRender.insert(std::make_pair(std::make_pair(p_toAdd->getTag(), p_toAdd->getTex()), p_toAdd));
	}

	//public static 
	void Renderer::removeFromRender(Renderable* p_toRemove) 
	{
		//Search for the object in the map
		std::multimap<const std::pair<const std::string*, const GLuint*>, Renderable*>::iterator pos;

		for (pos = Renderer::sm_toRender.begin(); pos != Renderer::sm_toRender.end(); ++pos)
		{
			if (pos->second == p_toRemove)
			{
				Renderer::sm_toRender.erase(pos);
				return;
			}
		}
	}

	//public static
	void Renderer::renderAll(const glm::mat4& p_viewProj)
	{
		std::multimap<const std::pair<const std::string*, const GLuint*>, Renderable*>::iterator it;

		for (it = Renderer::sm_toRender.begin(); it != Renderer::sm_toRender.end(); ++it)
		{
			it->second->render(p_viewProj);
		}
	}

	//public static
	void Renderer::removeAll()
	{
		sm_toRender.clear();
	}
}