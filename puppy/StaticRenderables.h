#pragma once

#include "P_Common.h"
#include "Texture.h"
#include "VertexEnvironment.h"

#include <map>
#include <vector>

namespace puppy
{

	/*
		@TODO: add support for vertex's with normals
	*/
	class StaticRenderables
	{
	private:
		std::map<const Texture*, std::vector<TexturedVertex>> m_texturedData;
		std::map<const Texture*, VertexEnvironment*> m_toRender;
		std::map<const Texture*, int> m_vertexCount; //sacrificing space for speed to save number of vertices in a buffer
		std::map<const Texture*, bool> m_texturedDataIsDirty;

		/*
			Helper method to construct TexturedVertex's into
			one draw call
		*/
		void constructRenderable(const Texture* p_where);
	public:
		/*
		addToRender() takes the texture needed to render the object and the 
		vertex data needed.  Assumes the vertex data has already been transformed
		into world space. This data is then later combined into a single draw call.
		*/
		void addToRender(const Texture* p_texNeeded, TexturedVertex p_data[]);
		void render(const glm::mat4& p_viewProj);
	};
}