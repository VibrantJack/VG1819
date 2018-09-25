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
		//Singleton stuff
		StaticRenderables();
		virtual ~StaticRenderables();
		static StaticRenderables* sm_instance;

	
		std::map<Texture*, VertexEnvironment*> m_toRender;
		std::map<GLuint, std::pair<std::map<const void*, std::vector<TexturedVertex>>, bool>> m_texturedData;
		std::map<GLuint, Texture*> m_idToTex;
		/*
			Helper method to construct TexturedVertex's into
			one draw call
		*/
		void constructRenderable(GLuint p_where);
	public:
		//Singleton stuff
		static StaticRenderables* getInstance() { return sm_instance; };
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new StaticRenderables(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete sm_instance; sm_instance = nullptr; };

		/*
		addToRender() takes the texture needed to render the object and the 
		vertex data needed.  Assumes the vertex data has already been transformed
		into world space. This data is then later combined into a single draw call.
		*/
		void addToRender(const void* p_owner,const Texture* p_texNeeded, TexturedVertex p_data[], int p_numElements);
		void removeFromRender(const void* p_owner, const Texture* p_tex);

		void render(const glm::mat4& p_viewProj);

		void clearAllData();

		//Method for things wanting to be in world space
		static void putInWorldSpace(TexturedVertex p_toTransform[], int p_numElements, const glm::mat4& p_worldMat);
	};
}