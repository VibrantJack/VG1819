#pragma once
//-----------------------------------------------------------------------------
// File:			Renderer.h
// Original Author:	Callum MacKenzie
//
// Classes to render things.
// They should register themselves
// And any children they have
// They should not call render on their children.
//
// Right now the render calls are sorted
// by coordbuffers and textures
// Could this be improved..? UV buffers
// are all unique : Could make Tex scale a Uniform?
//-----------------------------------------------------------------------------

#include "P_Common.h"
#include "Renderable.h"

#include <map>
#include <string>


namespace puppy
{
	
	//This could be a singleton instead of all static
	class Renderer
	{
	private:
		static std::multimap<const std::pair<const std::string*, const GLuint*>, Renderable*> sm_toRender;
	public:
		static void addToRender(Renderable* p_toAdd);
		static void removeFromRender(Renderable* p_toRemove);

		static void removeAll();

		static void renderAll(const glm::mat4& p_viewProj); //Could take camera position and view direction to macro cull
								//Not a lot of work already being done on CPU thread right now I think ?
	};
}