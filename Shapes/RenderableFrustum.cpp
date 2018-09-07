#include "RenderableFrustum.h"
#include "puppy\ShaderManager.h"

namespace shapes
{
	puppy::Texture* RenderableFrustum::sm_tex = nullptr;

	RenderableFrustum::RenderableFrustum()
	{
		m_vao = nullptr;
	}

	RenderableFrustum::~RenderableFrustum()
	{

	}

	void RenderableFrustum::setPoints(const glm::vec3& p_ftl, const glm::vec3& p_ftr, const glm::vec3& p_fbl, const glm::vec3& p_fbr, const glm::vec3& p_ntl,
		const glm::vec3& p_ntr, const glm::vec3& p_nbl, const glm::vec3& p_nbr)
	{
		//delete old vao
		if (m_vao != nullptr)
		{
			delete m_vao;
		}

		puppy::TexturedVertex verts[] = //Don't need uvs but it is ok
		{
			//Far rectangle
			p_ftl[0], p_ftl[1], p_ftl[2], 0,0,
			p_ftr[0], p_ftr[1], p_ftr[2], 0,0,
			
			p_ftr[0], p_ftr[1], p_ftr[2], 0,0,
			p_fbr[0], p_fbr[1], p_fbr[2], 0,0,
			
			p_fbr[0], p_fbr[1], p_fbr[2], 0,0,
			p_fbl[0], p_fbl[1], p_fbl[2], 0,0,
			
			p_fbl[0], p_fbl[1], p_fbl[2], 0,0,
			p_ftl[0], p_ftl[1], p_ftl[2], 0,0,
			
			//Close rectangle
			p_ntl[0], p_ntl[1], p_ntl[2], 0,0,
			p_ntr[0], p_ntr[1], p_ntr[2], 0,0,

			p_ntr[0], p_ntr[1], p_ntr[2], 0,0,
			p_nbr[0], p_nbr[1], p_nbr[2], 0,0,

			p_nbr[0], p_nbr[1], p_nbr[2], 0,0,
			p_nbl[0], p_nbl[1], p_nbl[2], 0,0,

			p_nbl[0], p_nbl[1], p_nbl[2], 0,0,
			p_ntl[0], p_ntl[1], p_ntl[2], 0,0,

			//Connecting lines
			p_nbl[0], p_nbl[1], p_nbl[2], 0,0,
			p_fbl[0], p_fbl[1], p_fbl[2], 0,0,

			p_nbr[0], p_nbr[1], p_nbr[2], 0,0,
			p_fbr[0], p_fbr[1], p_fbr[2], 0,0,

			p_ntl[0], p_ntl[1], p_ntl[2], 0,0,
			p_ftl[0], p_ftl[1], p_ftl[2], 0,0,

			p_ntr[0], p_ntr[1], p_ntr[2], 0,0,
			p_ftr[0], p_ftr[1], p_ftr[2], 0,0,
		};

		//create new vao
		m_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 24);

		if (sm_tex == nullptr)
		{
			sm_tex = new puppy::Texture("puppy/Textures/red.tga");
		}
	}

	void RenderableFrustum::update(float p_deltaTime)
	{
		//do nothing
	}

	void RenderableFrustum::render(const glm::mat4& p_viewProj)
	{
		if (m_vao != nullptr)
		{
			//Apply shader
			puppy::ShaderManager::applyShader(puppy::ShaderType::basic);

			//Apply uniforms
			GLint place = puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic)->getUniformPlace(WORLD_VIEW_PROJ_UNIFORM_NAME);
			glUniformMatrix4fv(place, 1, GL_FALSE, glm::value_ptr(p_viewProj));

			sm_tex->apply();

			//Render
			m_vao->drawArrays(GL_LINES);
		}
	}
}