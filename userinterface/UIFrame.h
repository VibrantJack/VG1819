#pragma once
#include "kitten\UIRenderable.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"

namespace userinterface 
{
	class UIFrame : public kitten::UIRenderable
	{
	public:
		UIFrame() {};
		UIFrame(const char* p_pathToTex);
		~UIFrame();
		void start();
		void render(const glm::mat4& p_ortho);
		void setTexture(const char* p_pathToTex);
		
	private:
		puppy::Material* m_mat;
		puppy::Texture* m_tex;
		
		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;
	};
}
