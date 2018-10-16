#include "K_RenderableSprite.h"

namespace kitten
{
	puppy::VertexEnvironment* K_RenderableSprite::sm_vao = nullptr;
	int K_RenderableSprite::sm_instances = 0;

	K_RenderableSprite::K_RenderableSprite(const char* p_pathToTex)
	{
		m_mat = new puppy::Material(puppy::ShaderType::sprite);
		if (p_pathToTex == nullptr)
		{
			m_mat->setTexture("textures\tiles\MISSING.tga");
		}
		else 
		{
			m_mat->setTexture(p_pathToTex);
		}

		if (sm_instances < 1)
		{
			puppy::TexturedVertex verts[] =
			{
				{ 0.0f, 0.0f,	0.0f, 0.0f },
				{ 1.0f, 0.0f,	1.0f, 0.0f },
				{ 1.0f, 1.0f,	1.0f, 1.0f },

				{ 1.0f, 1.0f,	1.0f, 1.0f },
				{ 0.0f, 1.0f,	0.0f, 1.0f },
				{ 0.0f, 0.0f,	0.0f, 0.0f }
			};
			sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::sprite), 6);
		}
		++sm_instances;
	}

	K_RenderableSprite::~K_RenderableSprite()
	{
		delete m_mat;
		if (--sm_instances == 0)
		{
			delete sm_vao;
		}
	}

	void K_RenderableSprite::setTexture(const char* p_pathToTex)
	{
		m_mat->setTexture(p_pathToTex);
	}

	void K_RenderableSprite::render(const glm::mat4& p_viewProj)
	{
		m_mat->apply();

		glm::mat4 wvp = p_viewProj * getTransform().getWorldTransform();
		m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

		sm_vao->drawArrays(GL_TRIANGLES);
	}
}