#pragma once
#include "puppy\P_Common.h"
#include "puppy\VertexEnvironment.h"
#include "puppy\Material.h"

namespace puppy
{
	class P_Sprite
	{
	public:
		P_Sprite()
		virtual ~P_Sprite();
		void render(const glm::mat4& p_mProj) override;
		void setTexture(const char* p_pathToTex);

	private:
		puppy::Material* m_mat;
		puppy::Texture* m_tex;
		
		static puppy:VertexEnvironment* sm_vao;
		static int sm_instances;
	};
}